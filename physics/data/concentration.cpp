#include "concentration.hpp"

using namespace volatrack;
using namespace conectration;

void Concentrations::calculate(const Data &data, Index isphere)
{
    for (auto& item : *this)
    {
        auto rad2 = item.radius * item.radius;
        real volCount = 0;
        auto sphere = data.spheres()[isphere];
        auto sphR2 = sphere.R * sphere.R;

        for (auto& vol : data.volatiles())
        {
            if (vol.isphere != isphere) continue;

            if ((vol.loc.rect() - item.point.rect()).lengthSquared()
                    * sphR2 < rad2)
            {
                volCount++;
            }
        }

        item.conectration = volCount / (PI * rad2);
    }


}
