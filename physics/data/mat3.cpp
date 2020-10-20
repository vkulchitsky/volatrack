#include "mat3.hpp"

using namespace volatrack;

mat3::mat3(const vec3 &left, const vec3 middle, const vec3 &right)
    : leftColumn(left)
    , middleColumn(middle)
    , rightColumn(right)
{

}

real mat3::determinant()
{
    return leftColumn.x() * middleColumn.y() * rightColumn.z()
            + middleColumn.x() * rightColumn.y() * leftColumn.z()
            + rightColumn.x() * leftColumn.y() * middleColumn.z()
            - rightColumn.x() * middleColumn.y() * leftColumn.z()
            - middleColumn.x() * leftColumn.y() * rightColumn.z()
            - leftColumn.x() * rightColumn.y() * middleColumn.z();
}

vec3 mat3::topRow()
{
    return {leftColumn.x(), middleColumn.x(), rightColumn.x()};
}

vec3 mat3::middleRow()
{
    return {leftColumn.y(), middleColumn.y(), rightColumn.y()};
}

vec3 mat3::bottomRow()
{
    return {leftColumn.z(), middleColumn.z(), rightColumn.z()};
}

mat3 mat3::operator+(const mat3 &other)
{
    return
    {
        leftColumn + other.leftColumn,
        middleColumn + other.middleColumn,
        rightColumn + other.rightColumn
    };
}

mat3 mat3::operator-(const mat3 &other)
{
    return
    {
        leftColumn - other.leftColumn,
        middleColumn - other.middleColumn,
        rightColumn - other.rightColumn
    };
}

vec3 mat3::operator*(const vec3 &original)
{
    return
    {
        vec3::dotProduct(topRow(), original),
        vec3::dotProduct(middleRow(), original),
        vec3::dotProduct(bottomRow(), original)
    };
}

mat3 mat3::operator*(const mat3 &other)
{
    return
    {
        *this * other.leftColumn,
        *this * other.middleColumn,
        *this * other.rightColumn
    };
}
