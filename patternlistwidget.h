#ifndef LZ_PATTERNLISTWIDGET_H
#define LZ_PATTERNLISTWIDGET_H

#include <QListWidget>
#include <QJsonArray>

namespace Lz {

class PatternStorage;
class PresetStorage;

class PatternListWidget : public QListWidget
{
    Q_OBJECT
public:
    explicit PatternListWidget(QWidget *parent = 0);

    void setPatternStorage(PatternStorage* storage);

    void setPresetStorage(PresetStorage* storage);

    QStringList checkedPatterns();

    QJsonArray json();

signals:

    void checkedItemsChanged();

public slots:
    void updatePatternList();
    void handleClicked(QListWidgetItem* item);
    void updatePreset(QString presetName);

private:
    PresetStorage* m_presetStorage;
    PatternStorage* m_patternStorage;
};

} // namespace Lz

#endif // LZ_PATTERNLISTWIDGET_H
