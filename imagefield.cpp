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
    /* Not implemented yet.  */
    Q_UNUSED(fullConfig);
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
    /* Not implemented yet.  */
    Q_UNUSED(fullConfig);
    return false;
}
