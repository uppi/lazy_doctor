#ifndef LZ_RENDEREDPATTERN_H
#define LZ_RENDEREDPATTERN_H

#include <QUrl>
#include <QString>
#include <QJsonObject>

namespace Lz {

class RenderedPattern
{
public:
    RenderedPattern();
    virtual ~RenderedPattern();

    void render(const QJsonObject& fields);

    virtual void renderField(const QString& name, const QString& value) = 0;
    virtual void print() = 0;
    virtual void saveAsFile(const QString& path) = 0;
};

} // namespace Lz

#endif // LZ_RENDEREDPATTERN_H
