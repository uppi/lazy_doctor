#ifndef LZ_PRESETSTORAGE_H
#define LZ_PRESETSTORAGE_H

#include <QObject>
#include <QList>
#include <QString>
#include <QStringList>
#include <QHash>
#include <QJsonObject>
#include <QJsonArray>

namespace Lz {
/**
 * @brief Set of the names of @a Pattern objects to be rendered.
 */
class Preset : public QList<QString> {};

/**
 * @brief Storage class for @a Preset objects.
 */
class PresetStorage : public QObject
{
    Q_OBJECT
public:
    explicit PresetStorage(QObject *parent = 0);
    const QHash<QString, Preset>& presets() const;

    Preset preset(const QString& name);

    bool loadPresets(const QJsonObject& config);
    bool loadPreset(const QString& key, const QJsonArray& preset);

    bool checkKey(const QString& key) const;
    static bool checkPresetConfig(const QJsonValue& config);

signals:
    void presetsUpdated();

private:
    QHash<QString, Preset> m_presets;

};

} // namespace Lz

#endif // LZ_PRESETSTORAGE_H
