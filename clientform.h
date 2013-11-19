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

class ClientForm : public QScrollArea
{
    Q_OBJECT
public:
    explicit ClientForm(QWidget *parent = 0);
    void setPatternStorage(PatternStorage* storage);
    void setPatternListWidget(PatternListWidget* plw);

    void addField(const QString& name);
    void removeField(const QString& name);

    void fill(const QJsonObject& request);

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

    int m_id;
};

} // namespace Lz

#endif // LZ_CLIENTFORM_H
