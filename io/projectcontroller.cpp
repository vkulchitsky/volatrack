#include "projectcontroller.hpp"

#include <QJsonDocument>
#include <QFile>
#include <QDir>

using namespace volatrack;

ProjectController::ProjectController(const QString &name,
                                     const QString &sourceDir)
    : m_name(name)
    , m_sourceDir(sourceDir)
{}

void ProjectController::saveToJsonFile(const Data &data)
{
    auto json = QJsonDocument{data.saveToJson()}.toJson();

    Index frame = static_cast<Index>(data.time.t / data.time.dtSave);

    QString here = "../Volatrack/io";
    QString curr = QDir::currentPath();
    QString s = !m_sourceDir.isEmpty() ? m_sourceDir : here;

    QDir dir(s);
    dir.mkdir(m_name);

    QFile file(s + "/" + m_name + "/" + m_name + QString::number(frame)
               + ".json");
    file.open(QIODevice::WriteOnly);
    file.write(json);
    file.close();
}
