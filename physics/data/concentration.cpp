#include "concentration.hpp"

#include <random>

using namespace volatrack;
using namespace concentration;

Concentrations::Concentrations(Size gridDimension)
{
    auto points = SurfPoint::makeGrid(gridDimension);

    for (auto& pt : points)
    {
        real rad = 2 * PI / gridDimension;
        DotRadConc drc(0, pt, rad);
        this->push_back(drc);
    }
}

void Concentrations::calculate(const Data &data, Index isphere)
{
    // REWRITE THIS - HORRIBLE AND EXPENSIVE!!!

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

        item.concentration = volCount / (PI * rad2);
    }


}
