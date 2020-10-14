#include "material.hpp"

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
    rho = jo["rho"].toDouble();
    G = jo["G"].toDouble();
    nu = jo["nu"].toDouble();
    gamma = jo["gamma"].toDouble();
    CR0 = jo["CR0"].toDouble();
    vR0 = jo["vR0"].toDouble();
    alpha_t = jo["alpha_t"].toDouble();
    mu = jo["mu"].toDouble();
    rMu = jo["rMu"].toDouble();
    rNu = jo["rNu"].toDouble();
    rK = jo["rK"].toDouble();
    rTh = jo["rTh"].toDouble();
    visc = jo["visc"].toDouble();
    viscg = jo["viscg"].toDouble();
    name = jo["name"].toString().toStdString();
}
