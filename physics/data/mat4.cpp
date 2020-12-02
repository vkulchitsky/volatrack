#include "mat4.hpp"

using namespace volatrack;

mat4::mat4(const vec4 &left, const vec4& mLeft, const vec4 &mRight, const vec4 &right)
    : leftColumn(left)
    , midLeftColumn(mLeft)
    , midRightColumn(mRight)
    , rightColumn(right)
{

}

vec4 mat4::topRow() const
{
    return {leftColumn.x(), midLeftColumn.x(), midRightColumn.x(),
                rightColumn.x()};
}

vec4 mat4::midTopRow() const
{
    return {leftColumn.y(), midLeftColumn.y(), midRightColumn.y(),
                rightColumn.y()};
}

vec4 mat4::midBottomRow() const
{
    return {leftColumn.z(), midLeftColumn.z(), midRightColumn.z(),
                rightColumn.z()};
}

vec4 mat4::bottomRow() const
{
    return {leftColumn.w(), midLeftColumn.w(), midRightColumn.w(),
                rightColumn.w()};
}

mat4 mat4::identity()
{
    return {{1, 0, 0, 0}, {0, 1, 0, 0}, {0, 0, 1, 0}, {0, 0, 0, 1}};
}

mat4 mat4::operator+(const mat4 &other) const
{
    return
    {
        leftColumn + other.leftColumn,
        midLeftColumn + other.midLeftColumn,
        midRightColumn + other.midRightColumn,
        rightColumn + other.rightColumn
    };
}

mat4 mat4::operator-(const mat4 &other) const
{
    return
    {
        leftColumn - other.leftColumn,
        midLeftColumn - other.midLeftColumn,
        midRightColumn - other.midRightColumn,
        rightColumn - other.rightColumn
    };
}

vec4 mat4::operator*(const vec4 &original) const
{
    return
    {
        vec4::dotProduct(topRow(), original),
        vec4::dotProduct(midTopRow(), original),
        vec4::dotProduct(midBottomRow(), original),
        vec4::dotProduct(bottomRow(), original)
    };
}

mat4 mat4::operator*(const mat4 &other) const
{
    return
    {
        *this * other.leftColumn,
        *this * other.midLeftColumn,
        *this * other.midRightColumn,
        *this * other.rightColumn
    };
}
