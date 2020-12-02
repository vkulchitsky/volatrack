/*!
  Structure for 4 by 4 matrix, because Qt's is not so great
  @file mat4.hpp
  @author Vladimir A Kulchitsky
  @version 1.0 12/2/2020
*/

#ifndef MAT4_H
#define MAT4_H

#include "types.hpp"

namespace volatrack
{

class mat4
{

public:

    mat4(const vec4& left, const vec4& mLeft, const vec4& mRight,
         const vec4& right);

    mat4 operator+(const mat4& other) const;
    mat4 operator-(const mat4& other) const;
    vec4 operator*(const vec4& original) const;
    mat4 operator*(const mat4& other) const;

    vec4 topRow() const;
    vec4 midTopRow() const;
    vec4 midBottomRow() const;
    vec4 bottomRow() const;

    static mat4 identity();

    vec4 leftColumn;
    vec4 midLeftColumn;
    vec4 midRightColumn;
    vec4 rightColumn;
};

}

#endif // MAT4_H
