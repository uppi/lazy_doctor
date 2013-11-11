#include <QListWidgetItem>


#include "patternstorage.h"
#include "patternlistwidget.h"


Lz::PatternListWidget::PatternListWidget(QWidget *parent) :
    QListWidget(parent)
{

}

void Lz::PatternListWidget::updatePatternList()
{
    this->clear();
    auto patterns = m_patternStorage->patterns();
    foreach(auto pattern, patterns.keys())
    {
        QListWidgetItem* item = new QListWidgetItem(pattern);
        item->setCheckState(Qt::Unchecked);
        item->setFlags(item->flags() | Qt::ItemIsUserCheckable);
        this->addItem(item);
    }
}

void Lz::PatternListWidget::setPatternStorage(PatternStorage* storage)
{
    m_patternStorage = storage;
    connect(m_patternStorage, SIGNAL(patternsUpdated()), this, SLOT(updatePatternList()));
    updatePatternList();
}

void Lz::PatternListWidget::handleClicked(QListWidgetItem* item)
{
    item->setCheckState(item->checkState() == Qt::Unchecked ? Qt::Checked : Qt::Unchecked);
    emit checkedItemsChanged();
}

QStringList Lz::PatternListWidget::checkedPatterns()
{
    QStringList result;
    for(int i = 0; i < this->count(); i++)
    {
        auto it = this->item(i);
        if(it->checkState() == Qt::Checked) result.append(it->text());
    }
    return result;
}

QJsonArray Lz::PatternListWidget::json()
{
    auto checked = checkedPatterns();
    QJsonArray result;
    foreach(auto p, checked)
    {
        result.append(p);
    }
    return result;
}
