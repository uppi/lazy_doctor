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
    static bool checkLine(const QString& line, const QFontMetrics& fm, int w, int h);

private:
    QPair<QFont, QStringList> howToRender(const ImageField::Instance& fieldInstance, QString text);

    ImagePattern* m_pattern;
    QImage m_image;
};

} // namespace Lz

#endif // LZ_RENDEREDIMAGEPATTERN_H
