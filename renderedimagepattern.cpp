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
    if(!field)
    {
        qDebug() << "Field " << name << "not found";
        return;
    }
    for(auto instance : field->instances)
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
            /* render a single line */
            painter.drawText(line.x, line.y + (line.h + h)/2, text);
        }
    }
     qDebug() << "Field " << name << "rendered as " << value;
}

bool Lz::RenderedImagePattern::isCorrect()
{
    /* Image is loaded aaand that's all, it seems.  */
    return !m_image.isNull();
}

QPair<QFont, QStringList> Lz::RenderedImagePattern::howToRender(const ImageField::Instance& fieldInstance, QString text)
{
    for(int size = 12; size >= 8; size -= 2)
    {
        QStringList result;
        result.clear();
        QFont font("Helvetica", size);
        QFontMetrics fm(font);
        if(checkLine(text, fm, fieldInstance.first().w, fieldInstance.first().h))
        {
            result.append(text);
            return QPair<QFont, QStringList>(font, result);
        }
        else if(fieldInstance.size() != 1)
        {
            QString test, resultLine;
            auto words = text.split(" ");
            auto i = 0;
            while(words.size() != 0 && i < fieldInstance.size())
            {
                int w = fieldInstance.at(i).w;
                int h = fieldInstance.at(i).h;
                test = test.isEmpty() ? words.first() : test + " " + words.first();
                if(checkLine(test, fm, w, h))
                {
                    resultLine = test;
                    words.pop_front();
                }
                else
                {
                    result.push_back(resultLine);
                    resultLine.clear();
                    test.clear();
                    i++;
                }
            }
            if(!resultLine.isEmpty() && words.size() == 0)
            {
                result.push_back(resultLine);
            }
            if(words.size() == 0)
            {
                return QPair<QFont, QStringList>(font, result);
            }
        }
    }
    return QPair<QFont, QStringList>();
}

bool Lz::RenderedImagePattern::checkLine(const QString& line, const QFontMetrics& fm, int w, int h)
{
    int fw = fm.width(line);
    int fh = fm.height();

    return (w >= fw && h >= fh);
}
