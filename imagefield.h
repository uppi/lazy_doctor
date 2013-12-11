#ifndef LZ_IMAGEFIELD_H
#define LZ_IMAGEFIELD_H

#include <QList>
#include <QJsonObject>
#include <QJsonArray>

namespace Lz {

/**
 * @brief Multilined text field in the @a ImagePattern
 */
struct ImageField
{
    /**
     * @brief Single line in the @a ImageField
     */
    struct Line
    {
        Line(const QJsonObject& line);
        int x, y, h, w;
    };

    typedef QList<Line> Instance;

    /**
     * @brief Construct from simple config (i. e. config for a single line)
     * @param singleLine            Config as a json object : {x: int_val, y: int_val, h: height_int_val, w: width_int_val}
     */
    ImageField(const QJsonObject& singleLine);
    /**
     * @brief Construct from full config
     * @param fullConfig            Config as a json object (list of instances, each of these is an array of lines) :
     *                              [[singleLineConfig, singleLineConfig, ..], [singleLineConfig, singleLineConfig, ..],]
     */
    ImageField(const QJsonArray& fullConfig);

    static bool checkSingleLine(const QJsonObject& singleLine);
    static bool checkFullConfig(const QJsonArray& fullConfig);

    QList<Instance> instances;
};

} // namespace Lz

#endif // LZ_FIELD_H
