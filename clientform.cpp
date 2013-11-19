#include <QSet>
#include <QVBoxLayout>
#include <QLabel>
#include <QDebug>
#include "clientform.h"
#include "patternstorage.h"
#include "patternlistwidget.h"
#include "pattern.h"
Lz::ClientForm::ClientForm(QWidget *parent) :
    QScrollArea(parent), m_patternListWidget(0), m_patternStorage(0), m_id(-1)
{
    m_formLayout = new QFormLayout();
    setLayout(m_formLayout);
}

void Lz::ClientForm::setPatternStorage(PatternStorage* storage)
{
    m_patternStorage = storage;
    updateFields();
}

void Lz::ClientForm::setPatternListWidget(PatternListWidget* plw)
{
    m_patternListWidget = plw;
    connect(m_patternListWidget, SIGNAL(itemChanged(QListWidgetItem *)), this, SLOT(handleCheckStateChanged(QListWidgetItem *)));
    connect(m_patternListWidget, SIGNAL(itemPressed(QListWidgetItem*)), this, SLOT(handleCheckStateChanged(QListWidgetItem *)));
}

void Lz::ClientForm::updateFields()
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

void Lz::ClientForm::updateSelection()
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

void Lz::ClientForm::addField(const QString& name)
{
    if(m_labels.contains(name)) return;
    QLineEdit* edit = new QLineEdit();
    m_formLayout->addRow(name, edit);
    m_labels[name] = edit;
}

void Lz::ClientForm::removeField(const QString& name)
{
    if(!m_labels.contains(name)) return;
    QWidget* label = m_formLayout->labelForField(m_labels[name]);

    m_formLayout->removeWidget(label);
    m_formLayout->removeWidget(m_labels[name]);
    label->deleteLater();
    m_labels[name]->deleteLater();
}

void Lz::ClientForm::setFieldSelectionStatus(const QString& name, bool isSelected)
{
    QLabel* label = qobject_cast<QLabel *>(m_formLayout->labelForField(m_labels[name]));
    if(label)
    {
        if(isSelected) label->setText("<b>" + name + "</b>");
        else label->setText(name);
    }
}

void Lz::ClientForm::handleCheckStateChanged(QListWidgetItem * item)
{
    Q_UNUSED(item)
    updateSelection();
}

QJsonObject Lz::ClientForm::json()
{
    QJsonObject result;
    foreach(auto name, m_labels.keys())
    {
        auto text = m_labels[name]->text();
        if(!text.isEmpty()) result.insert(name, text);
    }
    if(m_id != -1)
    {
        result.insert("__id__", m_id);
    }
    return result;
}

void Lz::ClientForm::fill(const QJsonObject& request)
{
    auto reqKeys = request.keys();
    for(auto key: m_labels.keys())
    {
        if(reqKeys.contains(key) && request.value(key).isString())
        {
            if(m_labels[key]) m_labels[key]->setText(request.value(key).toString());
        }
        else
        {
            m_labels[key]->setText("");
        }
    }
    if(reqKeys.contains("__id__"))
    {
        qDebug() << request.value("__id__");
        m_id = request.value("__id__").toDouble(-1);
    }
    else m_id = -1;
}
