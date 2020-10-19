/*!
    Data structure for material
    @file material.hpp
    @author Vladimir A Kulchitsky
    @version 1.0 10/05/2020
*/

#ifndef MATERIAL_H
#define MATERIAL_H

#include "constants.hpp"

namespace volatrack {


/*!
 * \brief Material of a sphere - expected to be lunar regolith
 */
struct Material : public CanIO
{
    Material();

    /*!
     * \brief save to json format
     * \return json object in Qt form representing the material
     */
    QJsonObject saveToJson() const override;

    /*!
     * \brief load from json format
     * \param json object in Qt form representing the material
     */
    void loadFromJson(const QJsonObject &jo) override;

    real rho;        //!< density, kg/m^3
    real G;          //!< shear modulus, Pa
    real nu;         //!< poisson coef., 1
    real gamma;      //!< surface energy, J/m^2
    real CR0;        //!< standard restitution, 1
    real vR0;        //!< standard impact velocity, m/s
    real alpha_t;    //!< tangent elastic reduction, 1
    real mu;         //!< friction coefficient
    real rMu;        //!< rolling dry friction coef.
    real rNu;        //!< rolling visc. friction coef.
    real rK;         //!< rolling dry torque growth factor
    real rTh;        //!< rolling visc. torque growth factor
    real visc;       //!< viscosity coefficient for tangential force
    real viscg;      //!< viscosity growth factor

    std::string name;    //!< material name
};

const Material lunarRegolith;

}

#endif // MATERIAL_H
