#ifndef LZ_PATTERN_H
#define LZ_PATTERN_H

#include <QJsonObject>

namespace Lz {

class Pattern
{
public:
    Pattern();
    virtual ~Pattern();

    static bool checkConfig(const QJsonObject& config);

    static Pattern* construct(const QJsonObject& config);
};

} // namespace Lz

#endif // LZ_PATTERN_H
