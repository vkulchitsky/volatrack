#include "material.hpp"
#include "defs.hpp"

using namespace volatrack;

Material::Material()
    : rho(0)
    , G(0)
    , nu(0)
    , gamma(0)
    , CR0(0)
    , vR0(0)
    , alpha_t(0)
    , mu(0)
    , rMu{0}
    , rNu{0}
    , rK{0}
    , rTh{0}
    , visc{0}
    , viscg{0}
    , name("nothing")
{
}

QJsonObject Material::saveToJson() const
{
    QJsonObject res;
    res.insert(MAT_RHO, rho);
    res.insert(MAT_G, G);
    res.insert(MAT_NU, nu);
    res.insert(MAT_GAMMA, gamma);
    res.insert(MAT_CR0, CR0);
    res.insert(MAT_VRO, vR0);
    res.insert(MAT_ALPHA, alpha_t);
    res.insert(MAT_MU, mu);
    res.insert(MAT_RMU, rMu);
    res.insert(MAT_RNU, rNu);
    res.insert(MAT_RK, rK);
    res.insert(MAT_RTH, rTh);
    res.insert(MAT_VISC, visc);
    res.insert(MAT_VISCG, viscg);
    res.insert(MAT_NAME_F, QString::fromStdString(name));

    return res;
}

void Material::loadFromJson(const QJsonObject &jo)
{
    rho = jo[MAT_RHO].toDouble();
    G = jo[MAT_G].toDouble();
    nu = jo[MAT_NU].toDouble();
    gamma = jo[MAT_GAMMA].toDouble();
    CR0 = jo[MAT_CR0].toDouble();
    vR0 = jo[MAT_VRO].toDouble();
    alpha_t = jo[MAT_ALPHA].toDouble();
    mu = jo[MAT_MU].toDouble();
    rMu = jo[MAT_RMU].toDouble();
    rNu = jo[MAT_RNU].toDouble();
    rK = jo[MAT_RK].toDouble();
    rTh = jo[MAT_RTH].toDouble();
    visc = jo[MAT_VISC].toDouble();
    viscg = jo[MAT_VISCG].toDouble();
    name = jo[MAT_NAME_F].toString().toStdString();
}
