#include "projectcontroller.hpp"
#include "defs.hpp"

#include <algorithm>

#include <QJsonDocument>
#include <QFile>
#include <QDir>

using namespace volatrack;

ProjectController::ProjectController()
{

}

void ProjectController::setFiles(const QStringList &&files)
{
    m_files = std::move(files);
    readFiles();
}

Data ProjectController::getData(Index i)
{
    Data data;
    data.loadFromJson(m_jsons[i]);
    return data;
}

void ProjectController::readFiles()
{
    m_jsons.clear();

    for (auto& path : m_files)
    {
        m_jsons.push_back(readPath(path));
    }

    std::sort(m_jsons.begin(), m_jsons.end(), [](const QJsonObject& first,
              const QJsonObject& second)
    {
        return (first[FILE_INFO][INFO_SLIDE].toInt()
                < second[FILE_INFO][INFO_SLIDE].toInt());
    });
}

QJsonObject ProjectController::readPath(const QString &path)
{
    QFile file(path);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        return {};
    }

    QByteArray bytes = file.readAll();
    auto doc = QJsonDocument::fromJson(bytes);
    file.close();

    return doc.object();
}

ProjectController::ProjectController(const QString &name,
                                     const QString &targetDir)
    : m_name(name)
    , m_targetDir(targetDir)
{
    readFiles();
}

void ProjectController::saveToJsonFile(const Data &data)
{
    auto resObj = data.saveToJson();

    Index frame = static_cast<Index>(data.time.t / data.time.dtSave);

    QJsonObject infoObj;
    QJsonValue fv(static_cast<int>(frame));

    infoObj.insert(INFO_SLIDE, fv);
    resObj.insert(FILE_INFO, infoObj);

    auto json = QJsonDocument{resObj}.toJson();

    QString s = !m_targetDir.isEmpty() ? m_targetDir : QDir::homePath();

    QDir dir(s);
    dir.mkdir(m_name);

    QFile file(s + "/" + m_name + "/" + m_name + QString::number(frame)
               + ".json");
    file.open(QIODevice::WriteOnly);
    file.write(json);
    file.close();
}
