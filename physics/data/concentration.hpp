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
namespace conectration
{

struct DotRadConc
{
    real conectration;
    SurfPoint point;
    real radius;
};

class Concentrations : std::vector<DotRadConc>
{
    void calculate(const Data& data, Index isphere);
};


}
}



#endif // CONCENTRATION_HPP
