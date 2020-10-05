#ifndef DATA_H
#define DATA_H

#include "volatile.hpp"

namespace volatrack
{

class Data : CanIO
{
public:
    Data();
    Data(const Spheres&& spheres, const Volatiles&& vols);

    Spheres spheres() const;
    Volatiles volatiles() const;

    void pushSphere(const Sphere& sphere);
    void pushVolatile(const Volatile& vol);

    QJsonObject saveToJson() override;
    void loadFromJson(const QJsonObject &jo) override;

    // load to file

private:
    Spheres m_spheres;
    Volatiles m_volatiles;
};

}

#endif // DATA_H
