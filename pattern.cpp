#include <QJsonObject>
#include "pattern.h"
#include "imagepattern.h"

Lz::Pattern::Pattern(const QJsonObject& config)
{
    /* ILB.  */
    if(config.contains("fields"))
    {
        auto fields = config.value("fields");
        if(fields.isObject())
        {
            m_fields = fields.toObject().keys();
        }
    }
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

QStringList Lz::Pattern::fields()
{
    return m_fields;
}
