#include "renderedimagepattern.h"

Lz::RenderedImagePattern::RenderedImagePattern(ImagePattern* pattern) : m_pattern(pattern), m_image(m_pattern->path())
{

}

void Lz::RenderedImagePattern::print()
{

}

void Lz::RenderedImagePattern::saveAsFile(const QString& path)
{
    Q_UNUSED(path);
}

void Lz::RenderedImagePattern::renderField(const QString& name, const QString& value)
{
    Q_UNUSED(name);
    Q_UNUSED(value);
}

bool Lz::RenderedImagePattern::isCorrect()
{
    /* Image is loaded aaand that's all, it seems.  */
    return !m_image.isNull();
}
