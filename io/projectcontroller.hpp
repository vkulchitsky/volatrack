/*!
  Ability to save data into files and control the project
  @file projectcontroller.hpp
  @author Vladimir A Kulchitsky
  @version 1.0 10/06/2020
*/

#ifndef PROJECTCONTROLLER_H
#define PROJECTCONTROLLER_H

#include "physics/engine/engine.hpp"
#include "physics/data/data.hpp"

namespace volatrack {


/*!
 * \brief Controller for saving data into files
 */
class ProjectController
{
public:
    ProjectController();

    /*!
     * \brief save data to json file
     * \param data
     */
    void saveToJson(const Data& data);
};

}

#endif // PROJECTCONTROLLER_H