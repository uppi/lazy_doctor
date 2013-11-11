#ifndef LZ_CORE_H
#define LZ_CORE_H

#include <QObject>
#include <QJsonObject>

namespace Lz {

class PatternStorage;
class PresetStorage;

class Core : public QObject
{
    Q_OBJECT
public:
    Core(QObject* parent = 0);

    bool render(const QJsonObject& request);

    bool init(const QJsonObject& config);
    bool init(const QString& fileName);

    PatternStorage* patternStorage();
    PresetStorage* presetStorage();

private:
    PatternStorage* m_patternStorage;
    PresetStorage* m_presetStorage;
};

} // namespace Lz

#endif // LZ_CORE_H
