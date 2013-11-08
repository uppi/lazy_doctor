#ifndef LZ_IMAGEFIELD_H
#define LZ_IMAGEFIELD_H

#include <QList>
#include <QJsonObject>
#include <QJsonArray>

namespace Lz {


struct ImageField
{
    struct Line
    {
        Line(QJsonObject line);
        int x, y, h, w;
    };

    typedef QList<Line> Instance;

    ImageField(QJsonObject singleLine);
    ImageField(QJsonArray fullConfig);

    static bool checkSingleLine(QJsonObject singleLine);
    static bool checkFullConfig(QJsonArray fullConfig);

    QList<Instance> instances;
};

} // namespace Lz

#endif // LZ_FIELD_H
