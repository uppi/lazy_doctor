#ifndef LZ_PATTERNSTORAGE_H
#define LZ_PATTERNSTORAGE_H

#include <QHash>
#include <QUrl>
#include <QJsonObject>

/*  Forward declaration.  */
class Pattern;

namespace Lz {

class PatternStorage
{
public:
    PatternStorage();
    ~PatternStorage();

    QHash<QString, Pattern*> patterns() const;
    bool loadPattern(QString name, Pattern* pattern);
    bool loadPatterns(const QJsonObject& config);

    bool checkKey(QString key) const;
    bool checkPattern(Pattern* pattern) const;

private:
    QHash<QString, Pattern*> m_patterns;
};

} // namespace Lz

#endif // LZ_PATTERNSTORAGE_H
