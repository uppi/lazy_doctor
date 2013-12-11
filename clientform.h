#ifndef LZ_CLIENTFORM_H
#define LZ_CLIENTFORM_H

#include <QWidget>
#include <QHash>
#include <QLineEdit>
#include <QString>
#include <QFormLayout>
#include <QListWidgetItem>
#include <QScrollArea>

namespace Lz {

class PatternStorage;
class PatternListWidget;

/**
 * @brief QForm to input data to be rendered (or saved into @a ClientStorage)
 */
class ClientForm : public QScrollArea
{
    Q_OBJECT
public:
    explicit ClientForm(QWidget *parent = 0);
    void setPatternStorage(PatternStorage* storage);
    void setPatternListWidget(PatternListWidget* plw);

    void addField(const QString& name);
    void removeField(const QString& name);

    /**
     * @brief   Fill the form with data from external storage.
     *          Only the fields the form already contains are be filled.
     * @param   request                 Data as a json object: {field_name : field_value, ...}.
     * @note    if the request contains an @a __id__ field, it's value is stored as client id.
     */
    void fill(const QJsonObject& request);

    /**
     * @brief   Set selection status of the field with given @a name.
     *          It only affects the visualization, selected fields are shown with bold font.
     * @param   name                    Field name.
     * @param   isSelected              Selection status.
     */
    void setFieldSelectionStatus(const QString& name, bool isSelected);

    /**
     * @brief   Data inputted to the form in json format
     * @return                          Data as a json object: {field_name : field_value, ...}.
     */
    QJsonObject json();

public slots:
    /**
     * @brief   Update the list of fields from @a PatternStorage.
     *          The list contains every field @a Pattern instances contain.
     */
    void updateFields();
    /**
     * @brief   Update selected fields from @a PatternListWidget.
     *          Only the fields related to the @a Pattern instances checked in the @a PatternListWidget will be selected.
     */
    void updateSelection();

    void handleCheckStateChanged(QListWidgetItem * item);

private:
    PatternListWidget           *   m_patternListWidget;
    PatternStorage              *   m_patternStorage;
    QHash<QString, QLineEdit*>      m_labels;

    QFormLayout                 *   m_formLayout;

    int                             m_id;
};

} // namespace Lz

#endif // LZ_CLIENTFORM_H
