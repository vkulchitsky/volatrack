/*!
    Concentration methods
    @file concentration.hpp
    @author Vladimir A Kulchitsky
    @version 1.0 11/24/2020
*/

#ifndef CONCENTRATION_HPP
#define CONCENTRATION_HPP

#include "data.hpp"

namespace volatrack
{
namespace concentration
{

struct DotRadConc
{
    DotRadConc(real c, SurfPoint p, real r)
        : concentration(c)
        , point(p)
        , radius(r)
    {}

    real concentration;
    SurfPoint point;
    real radius;
};

class Concentrations : std::vector<DotRadConc>
{
    /*!
     * \brief Constructor.
     * \param dimension of point grid for knowing concentrations on sphere
     */
    Concentrations(Size gridDimension);

    /*!
     * \brief calculate concentrations for volatiles on a sphere
     * \param data
     * \param isphere
     */
    void calculate(const Data& data, Index isphere);
};


}
}



#endif // CONCENTRATION_HPP
