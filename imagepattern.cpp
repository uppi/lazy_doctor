#include "imagepattern.h"

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
