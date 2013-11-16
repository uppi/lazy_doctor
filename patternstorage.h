#ifndef LZ_PATTERNSTORAGE_H
#define LZ_PATTERNSTORAGE_H

#include <QHash>
#include <QUrl>
#include <QJsonObject>
#include <QObject>

namespace Lz {

/*  Forward declaration.  */
class Pattern;

class PatternStorage : public QObject
{
    Q_OBJECT
public:
    explicit PatternStorage(QObject* parent = 0);
    ~PatternStorage();

    QHash<QString, Pattern*> patterns() const;

    Pattern* pattern(const QString& name);

    bool loadPattern(QString name, Pattern* pattern);
    bool loadPatterns(const QJsonObject& config);

    bool checkKey(QString key) const;
    bool checkPattern(Pattern* pattern) const;

    QStringList fields() const;

signals:
    void patternsUpdated();

private:
    QHash<QString, Pattern*> m_patterns;
};

} // namespace Lz

#endif // LZ_PATTERNSTORAGE_H
