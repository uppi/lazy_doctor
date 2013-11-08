#ifndef LZ_CORE_H
#define LZ_CORE_H

#include <QObject>
#include <QJsonObject>

namespace Lz {

class PatternStorage;

class Core : public QObject
{
    Q_OBJECT
public:
    Core(QObject* parent = 0);

    bool render(const QJsonObject& request);

    bool init(const QJsonObject& patternConfig);
    bool init(const QString& fileName);

    PatternStorage* patternStorage();

private:
    PatternStorage* m_patternStorage;
};

} // namespace Lz

#endif // LZ_CORE_H
