#ifndef LZ_PRESETCOMBOBOX_H
#define LZ_PRESETCOMBOBOX_H

#include <QComboBox>
#include <QString>
#include <QList>

namespace Lz {

class PresetStorage;

/**
 * @brief QComboBox for @a Preset instances.
 */
class PresetComboBox : public QComboBox
{
    Q_OBJECT
public:
    explicit PresetComboBox(QWidget *parent = 0);

    QList<QString> currentPreset() const;

    void setPresetStorage(PresetStorage* storage);
private:
    PresetStorage* m_presetStorage;

signals:

public slots:
    void updatePresets();

};

} // namespace Lz

#endif // LZ_PRESETCOMBOBOX_H
