#ifndef LZ_CORE_H
#define LZ_CORE_H

#include <QObject>
#include <QJsonObject>
#include <QPrinter>

namespace Lz {

class PatternStorage;
class PresetStorage;
class ClientStorage;

/**
 * @brief Program core.
 */
class Core : public QObject
{
    Q_OBJECT
public:
    Core(QObject* parent = 0);

    /**
     * @brief   Main action (print, save as file)
     * @param   request                 Request in json format.
     * @param   printer                 Printer object.
     * @return                          True on success, false otherwise
     *
     * @todo    Describe request format
     * @note    Request example can be found in data/sample_request.json
     */
    bool render(const QJsonObject& request, QPrinter* printer);

    /**
     * @brief   Init from config
     * @param   config                  Config in json format.
     * @return                          True on success, false otherwise.
     *
     * @todo    Describe config format
     * @note    Config example can be found in data/sample_config.json
     */
    bool init(const QJsonObject& config);

    /**
     * @brief   Init program core from configuration file.
     * @param   fileName                Path to file containing a config in json format.
     * @return                          True on success, false otherwise.
     *
     * @note    Config file directory becomes a working directory
     * @note    Config example can be found in data/sample_config.json
     */
    bool init(const QString& fileName);

    PatternStorage      *   patternStorage();
    PresetStorage       *   presetStorage();
    ClientStorage       *   clientStorage();


private:
    PatternStorage      *   m_patternStorage;
    PresetStorage       *   m_presetStorage;
    ClientStorage       *   m_clientStorage;
};

} // namespace Lz

#endif // LZ_CORE_H
