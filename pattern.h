#ifndef LZ_PATTERN_H
#define LZ_PATTERN_H

#include <QJsonObject>
#include <QStringList>

namespace Lz {

class RenderedPattern;

class Pattern
{
public:
    Pattern(const QJsonObject& config);
    virtual ~Pattern();

    static Pattern* construct(const QJsonObject& config);

    virtual RenderedPattern* render(const QJsonObject& info) = 0;

    QStringList fields();

private:
    QStringList m_fields;
};

} // namespace Lz

#endif // LZ_PATTERN_H
