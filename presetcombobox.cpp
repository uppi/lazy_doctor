#include "presetcombobox.h"
#include "presetstorage.h"

Lz::PresetComboBox::PresetComboBox(QWidget *parent) :
    QComboBox(parent), m_presetStorage(0)
{
    /* ILB.  */
}

void Lz::PresetComboBox::setPresetStorage(PresetStorage* storage)
{
    m_presetStorage = storage;
    connect(m_presetStorage, SIGNAL(presetsUpdated()), this, SLOT(updatePresets()));
    updatePresets();
}

void Lz::PresetComboBox::updatePresets()
{
    if(!m_presetStorage) return;
    QString current = this->currentText();
    this->clear();
    this->addItem("");
    this->addItems(m_presetStorage->presets().keys());
    for(int i = 0; i < count(); i++)
    {
        if(itemText(i) == current)
        {
            setCurrentIndex(i);
        }
    }
}

QList<QString> Lz::PresetComboBox::currentPreset() const
{
    if(m_presetStorage)
    {
        return m_presetStorage->preset(this->currentText());
    }
    return QList<QString>();
}
