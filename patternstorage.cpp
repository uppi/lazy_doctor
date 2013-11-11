#include "pattern.h"
#include "patternstorage.h"

Lz::PatternStorage::PatternStorage(QObject* parent) : QObject(parent)
{

}

Lz::PatternStorage::~PatternStorage()
{
    for(auto iter = m_patterns.constBegin(); iter != m_patterns.constEnd(); iter++)
    {
        delete iter.value();
    }
    m_patterns.clear();
}

QHash<QString, Lz::Pattern*> Lz::PatternStorage::patterns() const
{
    return m_patterns;
}

bool Lz::PatternStorage::loadPattern(QString name, Pattern* pattern)
{
    if(checkKey(name))
    {
        if(checkPattern(pattern))
        {
            m_patterns.insert(name, pattern);
            return true;
        }
        else
        {
            /* Report error. Later.  */
            return false;
        }
    }
    else
    {
        /* Report error. Later.  */
        return false;
    }
}

bool Lz::PatternStorage::loadPatterns(const QJsonObject& config)
{
    for(auto iter = config.constBegin(); iter != config.constEnd(); iter++)
    {
        auto value = iter.value();
        if(value.isObject())
        {
            Pattern* pattern = Pattern::construct(value.toObject());
            if(!loadPattern(iter.key(), pattern))
            {
                delete pattern;
            }
        }
        else
        {
            /* Report error. Later.  */
        }
    }
    emit patternsUpdated();
    return true;
}

bool Lz::PatternStorage::checkKey(QString key) const
{
    /* Maybe later.  */
    return !m_patterns.contains(key);
}


bool Lz::PatternStorage::checkPattern(Pattern* pattern) const
{
    return pattern != 0;
}


Lz::Pattern* Lz::PatternStorage::pattern(const QString& name)
{
    if(m_patterns.contains(name)) return m_patterns[name];
    else return 0;
}
