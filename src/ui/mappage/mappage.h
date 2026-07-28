#ifndef MapPage_H
#define MapPage_H

#include <QWidget>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QHash>
#include <QMap>
#include "categories/general.h"
#include "entity/ironclad.h"
#include "map/map.h"
#include "ui/relicbar/relicbar.h"
#include "ui/topbar/combattopbar.h"
#include <QMediaPlayer>
#include <QAudioOutput>
#include "combat/manageCombat/combatrewards.h"
#include "ui/mappage/scrollsection.h"
#include "ui/infobar/combatinfobar.h"

class MapPage : public QWidget
{
    Q_OBJECT
public:
    MapPage(QWidget *parent = nullptr, ironclad* plyr = nullptr, combatEvent* eve = nullptr);

    void initialSet();
    void Delete();
    void generateNewMap();

    ~MapPage() override;

protected:
    void resizeEvent(QResizeEvent *event) override;

private:
    bool eventFilter(QObject* obj, QEvent* eve) override;

    void refreshMapVisuals();

    QHash<QPushButton*, QGraphicsProxyWidget*> btns;
    QMap<QPushButton*, Room> btnToRoom;
    void onRoomClicked(QPushButton* btn);

    combatEvent* eve;

    QGraphicsView *combatView;
    QGraphicsScene *combatScene;
    BaseItem* black_screen;

    BaseItem* parent;

    ScrollSection* scroll;

    ironclad* player;

    CombatTopBar* bar;
    RelicBar* relic_bar;
    CombatInfoBar* info_bar = nullptr;

private slots:
    void relic_right_click(abstractRelic*);
    void open_setting();
};

#endif // MapPage_H