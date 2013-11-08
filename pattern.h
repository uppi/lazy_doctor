#ifndef LZ_PATTERN_H
#define LZ_PATTERN_H

#include <QJsonObject>

namespace Lz {

class RenderedPattern;

class Pattern
{
public:
    Pattern();
    virtual ~Pattern();

    static bool checkConfig(const QJsonObject& config);

    static Pattern* construct(const QJsonObject& config);

    virtual RenderedPattern* render(const QJsonObject& info) = 0;
};

} // namespace Lz

#endif // LZ_PATTERN_H
