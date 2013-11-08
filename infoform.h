#ifndef LZ_INFOFORM_H
#define LZ_INFOFORM_H

#include <QWidget>
#include <QHash>
#include <QLineEdit>
#include <QString>
#include <QFormLayout>
#include <QListWidgetItem>

namespace Lz {

class PatternStorage;
class PatternListWidget;

class InfoForm : public QWidget
{
    Q_OBJECT
public:
    explicit InfoForm(QWidget *parent = 0);
    void setPatternStorage(PatternStorage* storage);
    void setPatternListWidget(PatternListWidget* plw);

    void addField(const QString& name);
    void removeField(const QString& name);

    void setFieldSelectionStatus(const QString& name, bool isSelected);

    QJsonObject json();

signals:

public slots:
    void updateFields();
    void updateSelection();
    void handleCheckStateChanged(QListWidgetItem * item);

private:
    PatternListWidget *m_patternListWidget;
    PatternStorage *m_patternStorage;
    QHash<QString, QLineEdit*> m_labels;

    QFormLayout * m_formLayout;

};

} // namespace Lz

#endif // LZ_INFOFORM_H
