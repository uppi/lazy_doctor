#include <QImage>
#include <QDebug>
#include <QJsonObject>
#include <QJsonArray>
#include "imagepattern.h"
#include "renderedimagepattern.h"

Lz::ImagePattern::ImagePattern(const QJsonObject& config) : Pattern(config)
{
    if(checkConfig(config))
    {
        m_path = config.value("path").toString();
        QJsonObject fields = config.value("fields").toObject();
        foreach (auto key, fields.keys()) {
            auto val = fields.value(key);
            if(val.isObject())
            {
                m_imageFields[key] = new ImageField(val.toObject());
            }
            else if(val.isArray())
            {
                m_imageFields[key] = new ImageField(val.toArray());
            }
            else
            {
                qDebug() << "field " << key <<" is incorrect!";
            }
        }
    }
}

bool Lz::ImagePattern::checkConfig(const QJsonObject& config)
{
    if(!config.contains("type") || (config.value("type").toString("lol") != "image")) return false;
    if(!config.contains("path") || !config.value("path").isString()) return false;
    if(!config.contains("fields") || !config.value("fields").isObject()) return false;
    return true;
}


Lz::RenderedPattern* Lz::ImagePattern::render(const QJsonObject& request)
{
    auto result = new RenderedImagePattern(this);
    if(result->isCorrect())
        result->render(request);
    if(result->isCorrect())
        return result;
    delete result;
    return 0;
}

QString Lz::ImagePattern::path()
{
    return m_path;
}

Lz::ImageField* Lz::ImagePattern::field(const QString& name)
{
    return m_imageFields.contains(name) ? m_imageFields[name] : 0;
}
