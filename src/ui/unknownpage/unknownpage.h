#ifndef UNKNOWNPage_H
#define UNKNOWNPage_H

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
#include "ui/infobar/combatinfobar.h"
#include "events/UnknownMap.h"

class UnknownPage : public QWidget
{
    Q_OBJECT
public:
    UnknownPage(UnknownManager manag, QWidget *parent = nullptr, ironclad* plyr = nullptr, combatEvent* eve = nullptr);

    void initialSet();
    void Delete();
    void generateNewMap();

    ~UnknownPage() override;

protected:
    void resizeEvent(QResizeEvent *event) override;

private:
    bool eventFilter(QObject* obj, QEvent* eve) override;

    combatEvent* eve;

    QGraphicsView *combatView;
    QGraphicsScene *combatScene;
    BaseItem* black_screen;

    BaseItem* parent;
    TextItem* title;
    TextItem* desc;
    ImageItem* image;
    std::vector<QPushButton*> btns;
    std::vector<QGraphicsProxyWidget*> prxies;

    UnknownManager manager;
    ironclad* player;

    CombatTopBar* bar;
    RelicBar* relic_bar;
    CombatInfoBar* info_bar = nullptr;

    void eventUpdate();

private slots:
    void relic_right_click(abstractRelic*);
    void open_setting();
    void createSelectCard(std::vector<abstractCard*> cards);
    void update_bars();
    void add_card(abstractCard*);
    void createSelectPotion(std::vector<abstractPotion*> pots);
};

#endif // UNKNOWNPage_H