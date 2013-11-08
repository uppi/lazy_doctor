#include <QSet>
#include <QVBoxLayout>
#include <QLabel>
#include "infoform.h"
#include "patternstorage.h"
#include "patternlistwidget.h"
#include "pattern.h"
Lz::InfoForm::InfoForm(QWidget *parent) :
    QWidget(parent), m_patternListWidget(0), m_patternStorage(0)
{
    m_formLayout = new QFormLayout();
    setLayout(m_formLayout);
}

void Lz::InfoForm::setPatternStorage(PatternStorage* storage)
{
    m_patternStorage = storage;
    updateFields();
}

void Lz::InfoForm::setPatternListWidget(PatternListWidget* plw)
{
    m_patternListWidget = plw;
    connect(m_patternListWidget, SIGNAL(itemChanged(QListWidgetItem *)), this, SLOT(handleCheckStateChanged(QListWidgetItem *)));
    connect(m_patternListWidget, SIGNAL(itemPressed(QListWidgetItem*)), this, SLOT(handleCheckStateChanged(QListWidgetItem *)));
}

void Lz::InfoForm::updateFields()
{
    if(!m_patternStorage) return;
    QSet<QString> newFieldSet;
    auto patterns = m_patternStorage->patterns();
    foreach (auto pattern, patterns) {
        auto fields = pattern->fields();
        foreach (auto field, fields) {
            newFieldSet.insert(field);
        }
    }

    auto currentNames =  m_labels.keys();
    foreach (auto name, currentNames) {
        if(!newFieldSet.contains(name))
        {
            removeField(name);
        }
    }

    foreach (auto name, newFieldSet) {
        if(!m_labels.contains(name))
        {
            addField(name);
        }
    }

    updateSelection();
}

void Lz::InfoForm::updateSelection()
{
    if(!m_patternListWidget) return;
    QSet<QString> checkedPatternFields;
    auto patterns = m_patternListWidget->checkedPatterns();
    foreach (auto patternName, patterns) {
        auto pattern = m_patternStorage->pattern(patternName);
        if(pattern)
        {
            auto fields = pattern->fields();
            foreach (auto field, fields) {
                checkedPatternFields.insert(field);
            }
        }
    }

    foreach (auto name, m_labels.keys()) {
        setFieldSelectionStatus(name, checkedPatternFields.contains(name));
    }
}

void Lz::InfoForm::addField(const QString& name)
{
    if(m_labels.contains(name)) return;
    QLineEdit* edit = new QLineEdit();
    m_formLayout->addRow(name, edit);
    m_labels[name] = edit;
}

void Lz::InfoForm::removeField(const QString& name)
{
    if(!m_labels.contains(name)) return;
    QWidget* label = m_formLayout->labelForField(m_labels[name]);

    m_formLayout->removeWidget(label);
    m_formLayout->removeWidget(m_labels[name]);
    label->deleteLater();
    m_labels[name]->deleteLater();
}

void Lz::InfoForm::setFieldSelectionStatus(const QString& name, bool isSelected)
{
    QLabel* label = qobject_cast<QLabel *>(m_formLayout->labelForField(m_labels[name]));
    if(label)
    {
        if(isSelected) label->setText("<b>" + name + "</b>");
        else label->setText(name);
    }
}

void Lz::InfoForm::handleCheckStateChanged(QListWidgetItem * item)
{
    Q_UNUSED(item)
    updateSelection();
}

QJsonObject Lz::InfoForm::json()
{
    QJsonObject result;
    foreach(auto name, m_labels.keys())
    {
        auto text = m_labels[name]->text();
        if(!text.isEmpty()) result.insert(name, text);
    }
    return result;
}
