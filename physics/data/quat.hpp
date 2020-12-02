/*!
    Defining quaternion and inheriting 4D vector
    @file quat.hpp
    @author Vladimir A Kulchitsky
    @version 1.0 12/02/2020
*/

#ifndef QUAT_HPP
#define QUAT_HPP

#include "types.hpp"
#include "mat4.hpp"

namespace volatrack
{

using vec4 = QVector4D; // idk why i need this tbh

class quat : public vec4
{

public:

    quat();
    quat(const vec4& vec);
    quat(real w, real x, real y, real z);

    mat4 rotMat() const;
    quat inverse();
};

}

#endif // QUAT_HPP
