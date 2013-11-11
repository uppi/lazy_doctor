#include "imagefield.h"

Lz::ImageField::Line::Line(QJsonObject line)
{
    if(checkSingleLine(line))
    {
        x = line.value("x").toDouble();
        y = line.value("y").toDouble();
        h = line.value("h").toDouble();
        w = line.value("w").toDouble();
    }
    else x = y = h = w = 0;
}

Lz::ImageField::ImageField(QJsonArray fullConfig)
{
    if(checkFullConfig(fullConfig))
    {
        for(auto instance : fullConfig)
        {
            instances.append(Instance());
            for(auto line : instance.toArray())
            {
                instances.last().append(Line(line.toObject()));
            }
        }
    }
}

Lz::ImageField::ImageField(QJsonObject singleLine)
{
    if(checkSingleLine(singleLine))
    {
        instances.append(Instance());
        instances.first().append(Line(singleLine));
    }
}

bool Lz::ImageField::checkSingleLine(QJsonObject singleLine)
{
    return (singleLine.contains("x") && singleLine.value("x").isDouble() &&
    singleLine.contains("y") && singleLine.value("y").isDouble() &&
    singleLine.contains("h") && singleLine.value("h").isDouble() &&
    singleLine.contains("w") && singleLine.value("w").isDouble());
}

bool Lz::ImageField::checkFullConfig(QJsonArray fullConfig)
{
    for(auto instance : fullConfig)
    {
        if(instance.isArray())
        {
            for(auto line : instance.toArray())
            {
                if(!line.isObject() && !checkSingleLine(line.toObject())) return false;
            }
        }
    }
    return true;
}
