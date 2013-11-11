#ifndef LZ_IMAGEPATTERN_H
#define LZ_IMAGEPATTERN_H

#include <QHash>

#include "pattern.h"
#include "imagefield.h"

namespace Lz {

class ImagePattern : public Lz::Pattern
{
public:
    ImagePattern(const QJsonObject& config);
    static bool checkConfig(const QJsonObject& config);

    virtual RenderedPattern* render(const QJsonObject& request);
    ImageField* field(const QString& name);

    QString path();
private:
    QString m_path;
    QHash<QString, ImageField*> m_imageFields;
};

} // namespace Lz

#endif // LZ_IMAGEPATTERN_H
