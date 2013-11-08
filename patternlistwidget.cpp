#include <QListWidgetItem>

#include "patternstorage.h"
#include "patternlistwidget.h"


Lz::PatternListWidget::PatternListWidget(QWidget *parent) :
    QListWidget(parent)
{
    //connect(this, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(handleClicked(QListWidgetItem*)));
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
}

QStringList Lz::PatternListWidget::checkedPatterns()
{
    auto patterns = m_patternStorage->patterns();
    foreach(auto pattern, patterns.keys())
    {
        QListWidgetItem* item = new QListWidgetItem(pattern);
        item->setCheckState(Qt::Unchecked);
        item->setFlags(item->flags() | Qt::ItemIsUserCheckable);
        this->addItem(item);
    }
}
