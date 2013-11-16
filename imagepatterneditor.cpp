#include <QPixmap>
#include "imagepattern.h"
#include "renderedimagepattern.h"
#include "imagepatterneditor.h"

Lz::ImagePatternEditor::ImagePatternEditor(ImagePattern* pattern, QWidget *parent) :
    QLabel(parent), m_pattern(pattern)
{
    m_renderedPattern = m_pattern ? new RenderedImagePattern(m_pattern) : 0;
    if(m_pattern)
    {
        setPixmap(QPixmap::fromImage(m_renderedPattern->image()).scaledToHeight(1024));
    }
}
