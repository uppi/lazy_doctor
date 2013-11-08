#ifndef LZ_RENDEREDIMAGEPATTERN_H
#define LZ_RENDEREDIMAGEPATTERN_H

#include <QImage>
#include <QJsonObject>
#include "imagepattern.h"
#include "renderedpattern.h"

namespace Lz {

class RenderedImagePattern : public Lz::RenderedPattern
{
public:
    RenderedImagePattern(ImagePattern* pattern);

    virtual void print();
    virtual void saveAsFile(const QString& path);
    virtual void renderField(const QString& name, const QString& value);

    bool isCorrect();

private:
    ImagePattern* m_pattern;
    QImage m_image;
};

} // namespace Lz

#endif // LZ_RENDEREDIMAGEPATTERN_H
