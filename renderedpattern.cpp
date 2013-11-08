#include "renderedpattern.h"

Lz::RenderedPattern::RenderedPattern() {}
Lz::RenderedPattern::~RenderedPattern() {}

void Lz::RenderedPattern::render(const QJsonObject& fields)
{
    for(auto iter = fields.constBegin(); iter != fields.constEnd(); iter++)
    {
        if(iter.value().isString()) renderField(iter.key(), iter.value().toString());
    }
}
