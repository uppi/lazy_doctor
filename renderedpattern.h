#ifndef LZ_RENDEREDPATTERN_H
#define LZ_RENDEREDPATTERN_H

#include <QUrl>
#include <QString>
#include <QJsonObject>
#include <QPrinter>

namespace Lz {

/**
 * @brief An abstract parent for patterns filled with data.
 *  To be used while rendering text before printing and while editing patterns in GUI editor.
 */
class RenderedPattern
{
public:
    RenderedPattern();
    virtual ~RenderedPattern();

    void render(const QJsonObject& fields);

    virtual void renderField(const QString& name, const QString& value) = 0;
    virtual void print(QPrinter* printer) const = 0;
    virtual void saveAsFile(const QString& path) const = 0;
};

} // namespace Lz

#endif // LZ_RENDEREDPATTERN_H
