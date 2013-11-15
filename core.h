#ifndef LZ_CORE_H
#define LZ_CORE_H

#include <QObject>
#include <QJsonObject>

namespace Lz {

class PatternStorage;
class PresetStorage;
class ClientStorage;

class Core : public QObject
{
    Q_OBJECT
public:
    Core(QObject* parent = 0);

    bool        render(const QJsonObject& request);
    bool        saveToDb(const QJsonObject& request);
    QJsonObject loadFromDb(const QJsonObject& request);

    bool init(const QJsonObject& config);
    bool init(const QString& fileName);

    PatternStorage* patternStorage();
    PresetStorage* presetStorage();
    ClientStorage* clientStorage();


private:
    PatternStorage* m_patternStorage;
    PresetStorage* m_presetStorage;
    ClientStorage* m_clientStorage;
};

} // namespace Lz

#endif // LZ_CORE_H
