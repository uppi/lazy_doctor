#include <QStringList>
#include <QJsonObject>
#include <QJsonArray>
#include <QDir>
#include <QJsonDocument>
#include <QFile>
#include <QByteArray>
#include <QDebug>

#include "patternstorage.h"
#include "pattern.h"
#include "renderedpattern.h"

#include "core.h"

Lz::Core::Core(QObject* parent) : QObject(parent), m_patternStorage(0)
{

}

bool Lz::Core::init(const QJsonObject& patternConfig)
{
    m_patternStorage = new PatternStorage(this);
    if(!m_patternStorage->loadPatterns(patternConfig))
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
    return init(doc.object());
}

bool Lz::Core::render(const QJsonObject& request)
{
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
    if(!request.contains("info") || !request.value("info").isObject())
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

    QJsonObject info = request.value("info").toObject();

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
