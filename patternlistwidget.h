#ifndef LZ_PATTERNLISTWIDGET_H
#define LZ_PATTERNLISTWIDGET_H

#include <QListWidget>

namespace Lz {

class PatternStorage;

class PatternListWidget : public QListWidget
{
    Q_OBJECT
public:
    explicit PatternListWidget(QWidget *parent = 0);

    void setPatternStorage(PatternStorage* storage);

    QStringList checkedPatterns();

signals:

public slots:
    void updatePatternList();
    void handleClicked(QListWidgetItem* item);

private:
    PatternStorage* m_patternStorage;
};

} // namespace Lz

#endif // LZ_PATTERNLISTWIDGET_H
