#include "presetstorage.h"

Lz::PresetStorage::PresetStorage(QObject *parent) :
    QObject(parent)
{
}

const QHash<QString, Lz::Preset>& Lz::PresetStorage::presets() const
{
    return m_presets;
}

Lz::Preset Lz::PresetStorage::preset(const QString& name)
{
    if(m_presets.contains(name)) return m_presets[name];
    else return Lz::Preset();
}

bool Lz::PresetStorage::loadPresets(const QJsonObject& config)
{
    for(auto key : config.keys())
    {
        if(checkKey(key) && checkPresetConfig(config.value(key)))
        {
            Lz::Preset preset;
            for(auto s: config.value(key).toArray())
            {
                preset.append(s.toString());
            }
            m_presets[key] = preset;
        }
        else
        {
            /* TODO error report*/
            /* then change to 'return false;'. */
        }
    }
    emit presetsUpdated();
    return true;
}

bool Lz::PresetStorage::loadPreset(const QString& key, const QJsonArray& config)
{
    if(checkKey(key) && checkPresetConfig(config))
    {
        Lz::Preset preset;
        for(auto s: config)
        {
            preset.append(s.toString());
        }
        m_presets[key] = preset;
    }
    else
    {
        /* TODO error report*/
        return false;
    }
    emit presetsUpdated();
    return true;
}

bool Lz::PresetStorage::checkKey(const QString& key) const
{
    return !m_presets.contains(key);
}

bool Lz::PresetStorage::checkPresetConfig(const QJsonValue& config)
{
    if(!config.isArray())
    {
        return false;
    }
    for(auto value : config.toArray())
    {
        if(!value.isString())
        {
            return false;
        }
    }
    return true;
}
