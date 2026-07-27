#ifndef COMBATPAGE_H
#define COMBATPAGE_H

#include <QWidget>
#include <QGraphicsView>
#include <QGraphicsScene>
#include "combat/manageCombat/combat_manager.h"
#include "ui/entities/enemyitem.h"
#include "ui/entities/ironcladitem.h"
#include "ui/cards/abstractcardtemplate.h"
#include "ui/effects/entitycornersframe.h"
#include "ui/topbar/combattopbar.h"
#include <queue>
#include "ui/infobar/combatinfobar.h"
#include "ui/relicbar/relicbar.h"
#include <QMediaPlayer>
#include <QAudioOutput>

class CombatPage : public QWidget
{
    Q_OBJECT

public:
    CombatPage(QWidget *parent = nullptr, combat_manager* manager = nullptr, ironclad* plyr = nullptr);
    void reset_layout();
    void escape_entity(abstractEntity*);
    void died_entity(abstractEntity*);
    void remove_entity(abstractEntity*);

    void cardAdd(abstractCard*, qreal z = -1);
    void cardMovePile(abstractCard*, PileType from, PileType to);
    void Delete();

protected:
    void resizeEvent(QResizeEvent *event) override;

    void start_combat();
    void initialize_layout();
    void setHandCardPoint(abstractCard* card, bool enter = false);

    cardTemplates tmpl;

private:
    ~CombatPage() override;

    combatEvent* eve;

    QGraphicsView *combatView;
    QGraphicsScene *combatScene;
    BaseItem* black_screen;

    QMediaPlayer* media_player;
    QAudioOutput* bg_music;

    combat_manager* manager;
    ironclad* player;

    TextItem* discard_pile = nullptr;
    TextItem* draw_pile = nullptr;

    CombatTopBar* bar;
    RelicBar* relic_bar;
    CombatInfoBar* info_bar = nullptr;

    int enemies_scene_width = 0;
    int players_scene_width = 0;

    std::vector<IroncladItem*> players;
    std::vector<EnemyItem*> enemies;
    std::unordered_map<abstractCard*, abstractCardTemplate*> created_cards;

    std::unordered_map<abstractEntity*, entityCornersFrame*> entity_corner_effect;

    std::queue<std::function<void()>> action_queue;
    bool queue_busy = false;
    void enqueue(std::function<void()> fnc);
    void playNext();


private slots:
    void card_pressed(CardParent*) {};
    void card_moved(CardParent*, const QPointF&);
    void card_released(CardParent*, const QPointF&);
    void potion_moved(PotionParent*, const QPointF&);
    void potion_released(PotionParent*, const QPointF&);
    void card_updated(abstractCard*);
    void entity_update(abstractEntity*);
    void after_attack(attackResult&);
    void turn_start(abstractEntity*);

    void entity_right_click(abstractEntity*);
    void potion_right_click(abstractPotion*);
    void relic_right_click(abstractRelic*);
    void power_right_click(abstractPower*);

    void createSelectCard(std::vector<abstractCard*> cards);
    void createCollectReward(combat_manager*, bool);
    void open_setting();
};

#endif // COMBATPAGE_H