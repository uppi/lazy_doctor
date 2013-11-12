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
        Line(const QJsonObject& line);
        int x, y, h, w;
    };

    typedef QList<Line> Instance;

    ImageField(const QJsonObject& singleLine);
    ImageField(const QJsonArray& fullConfig);

    static bool checkSingleLine(const QJsonObject& singleLine);
    static bool checkFullConfig(const QJsonArray& fullConfig);

    QList<Instance> instances;
};

} // namespace Lz

#endif // LZ_FIELD_H
