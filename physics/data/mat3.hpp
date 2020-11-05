/*!
  Structure for 3 by 3 matrix, because Qt's is not so great
  @file mat3.hpp
  @author Vladimir A Kulchitsky
  @version 1.0 10/20/2020
*/

#ifndef MAT3_H
#define MAT3_H

#include "types.hpp"

namespace volatrack
{

class mat3
{

public:

    mat3(const vec3& left, const vec3 middle, const vec3& right);

    real determinant();

    mat3 operator+(const mat3& other);
    mat3 operator-(const mat3& other);
    vec3 operator*(const vec3& original);
    mat3 operator*(const mat3& other);

    vec3 topRow();
    vec3 middleRow();
    vec3 bottomRow();

    static mat3 identity();

    vec3 leftColumn;
    vec3 middleColumn;
    vec3 rightColumn;
};

}

#endif // MAT3_H
