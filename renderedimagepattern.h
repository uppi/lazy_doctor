#ifndef LZ_RENDEREDIMAGEPATTERN_H
#define LZ_RENDEREDIMAGEPATTERN_H

#include <QImage>
#include <QJsonObject>
#include "imagepattern.h"
#include "renderedpattern.h"

namespace Lz {

/**
 * @brief @a ImagePattern filled with data.
 */
class RenderedImagePattern : public Lz::RenderedPattern
{
public:
    RenderedImagePattern(ImagePattern* pattern);

    virtual void print(QPrinter* printer) const;
    virtual void saveAsFile(const QString& path) const;
    virtual void renderField(const QString& name, const QString& value);

    bool isCorrect() const;

    const QImage& image() const;
private:
    static bool checkLine(const QString& line, const QFontMetrics& fm, int w, int h);

private:
    QPair<QFont, QStringList> howToRender(const ImageField::Instance& fieldInstance, QString text) const;

    ImagePattern* m_pattern;
    QImage m_image;
};

} // namespace Lz

#endif // LZ_RENDEREDIMAGEPATTERN_H
