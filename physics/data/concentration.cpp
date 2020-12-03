#include "concentration.hpp"
#include <iostream>

#include <random>

using namespace volatrack;
using namespace concentration;

Concentrations::Concentrations(Size gridDimension)
{
    auto points = SurfPoint::makeGrid(gridDimension);

    for (auto& pt : points)
    {
        real rad = 2 * cst::PI / gridDimension;
        DotRadConc drc(0, pt, rad);
        this->push_back(drc);
    }
}

void Concentrations::calculate(const Data &data, Index isphere)
{
    std::vector<real> volCounts(size());

    for (auto& vol : data.volatiles())
    {
        if (vol.isphere != isphere) continue;

        auto sphere = data.spheres()[isphere];
        auto sphR2 = sphere.R * sphere.R;

        for  (Index i = 0; i < size(); ++i)
        {
            auto& item = (*this)[i];
            auto rad2 = item.radius * item.radius;

            if ((vol.loc.rect() - item.point.rect()).lengthSquared()
                    * sphR2 < rad2)
            {
                volCounts[i]++;
            }
        }
    }

    for (Index i = 0; i < size(); ++i)
    {
        auto& item = (*this)[i];
        item.concentration = volCounts[i] / (cst::PI * item.radius * item.radius);
    }
}
