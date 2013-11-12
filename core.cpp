#include <QStringList>
#include <QJsonObject>
#include <QJsonArray>
#include <QDir>
#include <QJsonDocument>
#include <QFile>
#include <QByteArray>
#include <QDebug>

#include "patternstorage.h"
#include "presetstorage.h"
#include "pattern.h"
#include "renderedpattern.h"

#include "core.h"

Lz::Core::Core(QObject* parent) : QObject(parent), m_patternStorage(0)
{

}

bool Lz::Core::init(const QJsonObject& config)
{
    if(!config.contains("presets") || !config.value("presets").isObject() ||
       !config.contains("patterns") || !config.value("patterns").isObject())
    {
        return false;
    }
    auto patternConfig = config.value("patterns").toObject();
    auto presetConfig = config.value("presets").toObject();
    m_patternStorage = new PatternStorage(this);
    m_presetStorage = new PresetStorage(this);
    if(!m_patternStorage->loadPatterns(patternConfig))
        return false;
    if(!m_presetStorage->loadPresets(presetConfig))
        return false;
    return true;
}

bool Lz::Core::init(const QString& fileName)
{
    QFile file(fileName);
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    QString configBA = file.readAll();
    file.close();
    QJsonDocument doc = QJsonDocument::fromJson(configBA.toUtf8());
    qWarning() << doc;
    if(!doc.isObject())
    {
        /* report error. */
        return false;
    }
    auto dir = QDir(fileName);
    dir.cdUp();
    QDir::setCurrent(dir.path());

    return init(doc.object());
}

bool Lz::Core::render(const QJsonObject& request)
{
    qDebug() << "request: " << request;
    if(!request.contains("actions") || !request.value("actions").isObject())
    {
        /* report error */
        return false;
    }
    if(!request.contains("patterns") || !request.value("patterns").isArray())
    {
        /* report error */
        return false;
    }
    if(!request.contains("fields") || !request.value("fields").isObject())
    {
        /* report error */
        return false;
    }

    QJsonObject actions = request.value("actions").toObject();

    QString saveDirPath;
    bool printNeeded;

    if(actions.contains("save") && actions.value("save").isString())
    {
        saveDirPath = actions.value("save").toString();
        QDir saveDir(saveDirPath);
        if(!saveDir.exists())
        {
            /* later -- create, now - report error*/
            return false;
        }
    }
    if(actions.contains("print") && actions.value("print").isBool())
    {
        printNeeded = actions.value("print").toBool();
    }
    if(saveDirPath.isEmpty() && !printNeeded)
    {
        /* Nothing to do here.  */
        return true;
    }

    QStringList patterns;

    auto reqPatterns = request.value("patterns").toArray();

    foreach(auto p, reqPatterns) {
        if(!p.isString())
        {
            /* report error */
            return false;
        }
        else
        {
            patterns.append(p.toString());
        }
    }

    QJsonObject info = request.value("fields").toObject();

    foreach (auto patternName, patterns) {
        Pattern* pattern = m_patternStorage->pattern(patternName);
        if(pattern)
        {
            auto rendered = pattern->render(info);
            if(rendered)
            {
                if(printNeeded)
                {
                    rendered->print();
                }
                if(!saveDirPath.isEmpty())
                {
                    rendered->saveAsFile(QDir(saveDirPath).filePath(patternName));
                }
            }
        }
    }
    return true;
}

Lz::PatternStorage* Lz::Core::patternStorage()
{
    return m_patternStorage;
}

Lz::PresetStorage* Lz::Core::presetStorage()
{
    return m_presetStorage;
}

bool Lz::Core::saveToDb(const QJsonObject& request)
{
    Q_UNUSED(request);
    return true;
}

QJsonObject Lz::Core::loadFromDb(const QJsonObject& request)
{
    Q_UNUSED(request);
    return QJsonObject();
}
