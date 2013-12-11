#ifndef LZ_IMAGEPATTERN_H
#define LZ_IMAGEPATTERN_H

#include <QHash>

#include "pattern.h"
#include "imagefield.h"

namespace Lz {

/**
 * @brief @a Pattern which consists of an image and a list of named text fields with coordinates (@a ImageField).
 */
class ImagePattern : public Lz::Pattern
{
public:
    /**
     * @brief Construct image pattern from config.
     * @param   config      Config as a json object: {type: "image", path: $path_to_image, fields: {$field1_name: $config, $field2_name: $config, ...}}
     *
     * @note    Config example can be found in data/sample_config.json as patterns.default value
     */
    ImagePattern(const QJsonObject& config);
    static bool checkConfig(const QJsonObject& config);

    virtual RenderedPattern* render(const QJsonObject& request);
    ImageField* field(const QString& name);

    /**
     * @brief Path to image file.
     * @return              Image file path.
     */
    QString path();
private:
    QString m_path;
    QHash<QString, ImageField*> m_imageFields;
};

} // namespace Lz

#endif // LZ_IMAGEPATTERN_H
