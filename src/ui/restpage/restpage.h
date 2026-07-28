#ifndef RESTPAGE_H
#define RESTPAGE_H

#include <QWidget>
#include <QGraphicsView>
#include <QGraphicsScene>
#include "categories/general.h"
#include "entity/ironclad.h"
#include "ui/relicbar/relicbar.h"
#include "ui/topbar/combattopbar.h"
#include <QMediaPlayer>
#include <QAudioOutput>
#include "combat/manageCombat/combatrewards.h"
#include "ui/infobar/combatinfobar.h"

class RestPage : public QWidget
{
    Q_OBJECT
public:
    RestPage(QWidget *parent = nullptr, ironclad* plyr = nullptr, combatEvent* eve = nullptr);

    void initialSet();
    void Delete();

    ~RestPage() override;
    inline static bool can_smith = true;
    inline static bool can_rest = true;
    inline static bool can_lift = false;
protected:
    void resizeEvent(QResizeEvent *event) override;

private:
    bool eventFilter(QObject* obj, QEvent* eve) override;

    combatEvent* eve;

    QGraphicsView *combatView;
    QGraphicsScene *combatScene;
    BaseItem* black_screen;

    BaseItem* parent;

    TextItem* header;

    QPushButton* rest_button;
    QGraphicsProxyWidget* rest_proxy;

    QPushButton* smith_button;
    QGraphicsProxyWidget* smith_proxy;

    QPushButton* lift_button;
    QGraphicsProxyWidget* lift_proxy;



    ironclad* player;

    CombatTopBar* bar;
    RelicBar* relic_bar;
    CombatInfoBar* info_bar = nullptr;

private slots:
    void relic_right_click(abstractRelic*);
    void open_setting();
    void createSelectCard(std::vector<abstractCard*> cards);
};

#endif // RESTPAGE_H
