#ifndef LZ_IMAGEPATTERN_H
#define LZ_IMAGEPATTERN_H

#include "pattern.h"

namespace Lz {

class ImagePattern : public Lz::Pattern
{
public:
    ImagePattern(const QJsonObject& config);
    static bool checkConfig(const QJsonObject& config);
};

} // namespace Lz

#endif // LZ_IMAGEPATTERN_H
