/*! \file */

#ifndef UNITTESTS_H
#define UNITTESTS_H

#include <map>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <functional>
#include <chrono>

#define PPH_DEFS_UNUSED11 [[gnu::unused]]

/*!
 * \cond
 *
 */
namespace Tests {

class Fail : public std::runtime_error
{
public:
    using std::runtime_error::runtime_error;
};

}
/*!
 * \endcond
 *
 */


/*!
 * \brief macro that checks for equality of two values in unit test
 * \relates unittesting.h
 * \param x value for which operation == with y is defined,
 * where x on left side
 * \param y value for which operation == with x is defined,
 * where y on right side
 */
#define ASSERT_EQUAL(x, y) \
{ \
    std::ostringstream os; \
    os << #x << " != " << #y << ", " << __FILE__ << ":" << __LINE__; \
    AssertTrue(((x) == (y)), os.str()); \
}

/*!
 * \brief Check if an expression is false
 */
#define ASSERT_TRUE(x, hint) AssertTrue((x), hint)

/*!
 * \brief Check if an expression is false
 */
#define ASSERT_FALSE(x, hint) ASSERT_TRUE(!(x), hint)

/*!
 * \brief Fail the test with the reason specified
 */
#define FAIL(reason) throw Tests::Fail(reason);

/*!
 * \brief Assert that an expression is true
 */
template<typename T>
void AssertTrue(const T& t, const std::string& hint)
{
  if(!bool(t))
  {
      std::ostringstream os;
      os << "Assertion failed: " << hint ;
      FAIL(os.str());
  }
}

/*!
 * \brief function that checks for equality of two values in unit test
 * \relates unittesting.h
 * \param x value for which operation == with y is defined,
 * where x on left side
 * \param y value for which operation == with x is defined,
 * where y on right side
 * \param hint message that will be printed if assertion is not equal
 */
template<class T, class U>
void AssertEqual(const T &t, const U &u, const std::string &hint)
{
    if(!(t == u))
    {
        std::ostringstream os;
        os << "Assertion failed: " ;
        os << t;
        os << " != " ;
        os << u;
        os << ", hint: " << hint;
        throw Tests::Fail(os.str());
    }
}

/*!
 * \brief macro that define code block that will be runned before test
 * \relates unittesting.h
 * \param n name of test
 */
#define BEFORE(n) \
    inline void n ## __BEFORE__(); \
    int n ## __BEFORE_CALLER__() \
    { \
        auto index = std::string(__FILE__).find_last_of("/\\") + 1; \
        auto fileName = std::string(__FILE__).substr(index); \
        Tests::TestRunner::instance().m_tests[std::string(#n) + " "+ \
    fileName].m_before = n ## __BEFORE__; \
        return 0; \
    } \
    static int n ## __BEFORE_CALL__ = n ## __BEFORE_CALLER__(); \
    inline void n ## __BEFORE__()

/*!
 * \brief macro that define test code block
 * \relates unittesting.h
 * \param n name of test
 */
#define TEST(n) \
    inline void n ## __TEST__(); \
    int n ## __TEST_CALLER__() \
    { \
        auto index = std::string(__FILE__).find_last_of("/\\") + 1; \
        auto fileName = std::string(__FILE__).substr(index); \
        Tests::TestRunner::instance().m_tests[std::string(#n) + " " + \
    fileName].m_test = n ## __TEST__; \
        return 0; \
    } \
    PPH_DEFS_UNUSED11                                       \
    static int n ## __TEST_CALL__ = n ## __TEST_CALLER__(); \
    inline void n ## __TEST__()

/*!
 * \brief macro that define code block that will be runned after test
 * \relates unittesting.h
 * \param n name of test
 */
#define AFTER(n) \
    inline void n ## __AFTER__(); \
    int n ## __AFTER_CALLER__() \
    { \
        auto index = std::string(__FILE__).find_last_of("/\\") + 1; \
        auto fileName = std::string(__FILE__).substr(index); \
        Tests::TestRunner::instance().m_tests[std::string(#n) + " " + \
    fileName].m_after = n ## __AFTER__; \
        return 0; \
    } \
    static int n ## __AFTER_CALL__ = n ## __AFTER_CALLER__(); \
    inline void n ## __AFTER__()

/*!
 * \brief macro that need to work library.
 * Includes main function.
 * Only one macro for test solution!
 * \relates unittesting.h
 */
#define INIT_TESTS() \
    int main() \
    { \
        Tests::TestRunner::instance().run(); \
    } \


/*!
 * \cond
 *
 */
namespace Tests {

using namespace std::chrono;

struct Test
{
    std::function<void(void)> m_before;
    std::function<void(void)> m_test;
    std::function<void(void)> m_after;

    std::string m_message;
    double m_duration;
    enum Status {SUCCESS, FAIL, ERROR} m_status;

};

class TestRunner {
public:
    static TestRunner &instance()
    {
        static TestRunner testRunner;
        return testRunner;
    }

    void run()
    {
        std::map<std::string, std::vector<std::pair<std::string, Test*>>>
                testsuites;
        std::vector<std::string> testsKeys;
        for(auto &test : m_tests)
        {
            testsKeys.push_back(test.first);
        }
        for(size_t i = 0; i < testsKeys.size(); i++)
        {
            auto index = testsKeys[i].find_first_of(' ');
            auto fileName = testsKeys[i].substr(index + 1);
            auto testName = testsKeys[i].substr(0, index);
            std::pair<std::string, Test*> testAndName;
            testAndName.first = testName;
            testAndName.second = &m_tests[testsKeys[i]];
            testsuites[fileName].push_back(testAndName);
        }

        auto start = high_resolution_clock::now();
        for(auto &testsuite : testsuites)
        {
            std::cout << "------------" << std::endl
                      << testsuite.first << std::endl
                      << "------------" << std::endl;
            auto all = 0;
            auto failed = 0;
            auto errors = 0;
            for(auto &test : testsuite.second)
            {
                all++;
                std::string current;
                try
                {
                    current = "before";
                    if(test.second->m_before && test.second->m_test)
                    {
                        test.second->m_before();
                    }

                    current = "test";
                    auto test_start = high_resolution_clock::now();
                    if(test.second->m_test)
                    {
                        test.second->m_test();
                    }
                    auto test_end = high_resolution_clock::now();
                    auto test_duration = duration_cast<seconds>
                            (test_end - test_start);
                    test.second->m_duration = test_duration.count();

                    current = "after";
                    if(test.second->m_after && test.second->m_test)
                    {
                        test.second->m_after();
                    }
                    test.second->m_status = Test::SUCCESS;
                }
                catch (Fail &e)
                {
                    test.second->m_status = Test::FAIL;
                    test.second->m_message = current + ": " + e.what();
                    failed++;
                }
                catch(std::exception &e)
                {
                    test.second->m_status = Test::ERROR;
                    test.second->m_message = current + ": " + e.what();
                    errors++;
                }
                catch(...)
                {
                    test.second->m_status = Test::ERROR;
                    test.second->m_message = current + ": "
                            + "Non std::exception exception";
                    errors++;
                }

                switch (test.second->m_status) {
                case Test::SUCCESS:
                    std::cout << "[OK] " + test.first << std::endl;
                    break;
                case Test::FAIL:
                    std::cerr << "[FAIL] " + test.first << std::endl
                              << test.second->m_message << std::endl;
                    break;
                case Test::ERROR:
                    std::cout.rdbuf(std::cerr.rdbuf());
                    std::cerr << "[ERROR] " + test.first << std::endl
                              << test.second->m_message << std::endl;
                    break;
                }


            }

            std::cout << "------------" << std::endl
                      << "All: " << all
                      << ", Failed: " << failed
                      << ", Errors: " << errors << std::endl
                      << "------------" << std::endl
                      << std::endl;

            m_all += all;
            m_failed += failed;
            m_errors += errors;
        }
        auto end = high_resolution_clock::now();

        auto duration = duration_cast<seconds>(end - start);
        m_duration = duration.count();

        createXML();
    }

    std::map<std::string, Test> m_tests;
private:
    double m_duration;
    int m_all{0};
    int m_failed{0};
    int m_errors{0};
    TestRunner() {}

    void createXML()
    {

        std::map<std::string, std::vector<std::pair<std::string, Test>>>
                testsuites;
        std::vector<std::string> testsKeys;
        for(auto &test : m_tests)
        {
            testsKeys.push_back(test.first);
        }
        for(size_t i = 0; i < testsKeys.size(); i++)
        {
            auto index = testsKeys[i].find_first_of(' ');
            auto fileName = testsKeys[i].substr(index + 1);
            auto testName = testsKeys[i].substr(0, index);
            std::pair<std::string, Test> testAndName;
            testAndName.first = testName;
            testAndName.second = m_tests[testsKeys[i]];
            testsuites[fileName].push_back(testAndName);
        }

        std::fstream file;
        file.open("report.xml", std::ios::out | std::ios::trunc);
        file << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
             << "<testsuites time=\"" << m_duration
             << "\" tests=\"" << m_all
             << "\" failures=\"" << m_failed
             << "\" errors=\"" << m_errors << "\">\n";
        for(auto &testsuite : testsuites)
        {
            auto duration = 0;
            auto all = 0;
            auto failed = 0;
            auto errors = 0;
            for(auto &testcase : testsuite.second)
            {
                duration += testcase.second.m_duration;
                all++;
                switch (testcase.second.m_status) {
                case Test::SUCCESS:
                    break;
                case Test::FAIL:
                    failed++;
                    break;
                case Test::ERROR:
                    errors++;
                    break;
                }
            }

            file << "<testsuite name=\"" << testsuite.first
                            << "\" time=\"" << duration
                            << "\" tests=\"" << all
                            << "\" failures=\"" << failed
                            << "\" errors=\"" << errors << "\">\n";

            for(auto &test : testsuite.second)
            {

                switch (test.second.m_status) {
                case Test::SUCCESS:
                    file << "<testcase name=\"" << test.first
                         << "\" time=\"" << test.second.m_duration << "\"/>\n";
                    break;
                case Test::FAIL:
                    file << "<testcase name=\"" << test.first
                         << "\" time=\"" << test.second.m_duration << "\">\n"
                         << "<failure type=\"FAIL\">"
                         << test.second.m_message
                         << "</failure>\n"
                         << "</testcase>\n";
                    break;
                case Test::ERROR:
                    file << "<testcase name=\"" << test.first
                         << "\" time=\"" << test.second.m_duration << "\">\n"
                         << "<error type=\"ERROR\">"
                         << test.second.m_message
                         << "</error>\n"
                         << "</testcase>\n";
                    break;
                }
            }

            file << "</testsuite>\n";
        }


        file << "</testsuites>";
        file.close();
    }
};

}
/*!
 * \endcond
 *
 */

#endif // UNITTESTS_H
