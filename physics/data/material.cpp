#include "material.h"

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

QJsonObject Material::saveToJson()
{
    QJsonObject res;
    res.insert("rho", rho);
    res.insert("G", G);
    res.insert("nu", nu);
    res.insert("gamma", gamma);
    res.insert("CR0", CR0);
    res.insert("vR0", vR0);
    res.insert("alpha_t", alpha_t);
    res.insert("mu", mu);
    res.insert("rMu", rMu);
    res.insert("rNu", rNu);
    res.insert("rK", rK);
    res.insert("rTh", rTh);
    res.insert("visc", visc);
    res.insert("viscg", viscg);
    res.insert("name", QString::fromStdString(name));

    return res;
}

void Material::loadFromJson(const QJsonObject &jo)
{
    //
}
