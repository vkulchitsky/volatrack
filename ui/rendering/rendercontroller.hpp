/*!
  Rendering backend
  @file rendercontroller.hpp
  @author Vladimir A Kulchitsky
  @version 1.0 10/29/2020
*/

#ifndef RENDERCONTROLLER_HPP
#define RENDERCONTROLLER_HPP

#include "rendersphere.hpp"
#include "physics/data/data.hpp"

/*!
 * \brief Controls rendering.
 */
class RenderController
{
public:
    RenderController();

    QVector<RenderSphere> spheresFromData(const volatrack::Data& data);
};

#endif // RENDERCONTROLLER_HPP
