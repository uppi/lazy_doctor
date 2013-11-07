#include "pattern.h"
#include "imagepattern.h"

Lz::Pattern::Pattern()
{
    /* ILB.  */
}

Lz::Pattern::~Pattern()
{
    /* ILB.  */
}

Lz::Pattern* Lz::Pattern::construct(const QJsonObject& config)
{
    if(!config.contains("type"))
    {
        return 0;
    }
    if(config.value("type").toString() == "image")
    {
        if(ImagePattern::checkConfig(config))
        {
            return new ImagePattern(config);
        }
    }
    return 0;
}
