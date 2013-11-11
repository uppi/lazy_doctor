#include <QDebug>
#include <QLabel>
#include <QPainter>
#include <QPair>
#include "imagefield.h"
#include "renderedimagepattern.h"


Lz::RenderedImagePattern::RenderedImagePattern(ImagePattern* pattern) : m_pattern(pattern), m_image(m_pattern->path())
{

}

void Lz::RenderedImagePattern::print()
{
    qDebug() << "I am printed!";

    QLabel* label = new QLabel;
    label->setPixmap(QPixmap::fromImage(m_image));
    label->show();
}

void Lz::RenderedImagePattern::saveAsFile(const QString& path)
{
    qDebug() << "I am saved as file here: " << path;
}

void Lz::RenderedImagePattern::renderField(const QString& name, const QString& value)
{
    QPainter painter;
    painter.begin(&m_image);

    painter.setCompositionMode(QPainter::CompositionMode_Source);

    qDebug() << "Field " << name << "rendered as " << value;

    auto field = m_pattern->field(name);
    foreach(auto instance, field->instances)
    {
        /* render a single instance */
        auto fontAndText = howToRender(instance, value);
        painter.setFont(fontAndText.first);
        QFontMetrics fm(fontAndText.first);
        int h = fm.height();
        for(int i = 0; i < fontAndText.second.size(); i++)
        {
            auto line = instance.at(i);
            auto text = fontAndText.second.at(i);
            int w = fm.width(text);
            /* render a single line */
            painter.drawText(line.x + line.w/2 - w/2, line.y + (line.h + h)/2, fontAndText.second.at(i));
        }
    }
}

bool Lz::RenderedImagePattern::isCorrect()
{
    /* Image is loaded aaand that's all, it seems.  */
    return !m_image.isNull();
}

QPair<QFont, QStringList> Lz::RenderedImagePattern::howToRender(const ImageField::Instance& fieldInstance, QString text)
{
    QStringList result;

    for(int size = 32; size >= 8; size -= 2)
    {
        result.clear();
        QFont font("Helvetica", size);
        QFontMetrics fm(font);
        int w = fm.width(text);
        int h = fm.height();

        if(fieldInstance.first().w >= w && fieldInstance.first().h >= h)
        {
            result.append(text);
            return QPair<QFont, QStringList>(font, result);
        }
    }

    /* We don't handle multiple lines now*/
    //QStringList words = text.split(" ");
    return QPair<QFont, QStringList>();
}
