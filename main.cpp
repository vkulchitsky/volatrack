#include "architecture/mainmodel.hpp"

#include <iostream>

#include <QVector>
#include <QJsonObject>
#include <QJsonDocument>
#include <QDebug>
#include <QDir>

using namespace volatrack;

int main()
{
    MainModel model;
    model.runFromJson("/home/vloot/8sph.json");
    return 0;
}
