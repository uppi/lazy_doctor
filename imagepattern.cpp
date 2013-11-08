#include <QImage>
#include "imagepattern.h"
#include "renderedimagepattern.h"

Lz::ImagePattern::ImagePattern(const QJsonObject& config)
{
    if(checkConfig(config))
    {

    }
}

bool Lz::ImagePattern::checkConfig(const QJsonObject& config)
{
    if(!config.contains("type") || !config.value("type").isString()) return false;
    if(!config.contains("path") || !config.value("path").isString()) return false;

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
