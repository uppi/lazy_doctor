#ifndef LZ_IMAGEPATTERNEDITOR_H
#define LZ_IMAGEPATTERNEDITOR_H

#include <QLabel>

namespace Lz {

class ImagePattern;
class RenderedImagePattern;

class ImagePatternEditor : public QLabel
{
    Q_OBJECT
public:
    explicit ImagePatternEditor(Lz::ImagePattern* pattern, QWidget *parent = 0);

signals:

public slots:

private:
    Lz::ImagePattern * m_pattern;
    Lz::RenderedImagePattern * m_renderedPattern;

};

} // namespace Lz

#endif // LZ_IMAGEPATTERNEDITOR_H
