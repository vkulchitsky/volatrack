#include "quat.hpp"

using namespace volatrack;

mat4 quat::rotMat()
{
    float xx{ 2 * x() * x() }, yy{ 2 * y() * y() }, zz{ 2 * z() * z() },
          xy{ 2 * x() * y() }, xz{ 2 * x() * z() }, yz{ 2 * y() * z() },
          xw{ 2 * x() * w() }, yw{ 2 * y() * w() }, zw{ 2 * z() * w() };

    return {{1 - (yy + zz),    xy - zw,     xz + yw,  0},
               {xy + zw,  1 - (xx + zz),    yz - xw,  0},
               {xz - yw,     yz + xw,  1 - (xx + yy), 0},
                   {0, 0, 0, 1}};
}
