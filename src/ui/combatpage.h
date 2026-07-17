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
#include <queue>

class CombatPage : public QWidget
{
    Q_OBJECT

public:
    explicit CombatPage(QWidget *parent = nullptr, combat_manager* manager = nullptr, ironclad* plyr = nullptr);
    void reset_layout();
    void escape_entity(abstractEntity*);
    void died_entity(abstractEntity*);
    void remove_entity(abstractEntity*);

    void cardAdd(abstractCard*, qreal z = -1);
    void cardMovePile(abstractCard*, PileType from, PileType to);

protected:
    void resizeEvent(QResizeEvent *event) override;

    void start_combat();
    void initialize_layout();
    void setHandCardPoint(abstractCard* card, bool enter = false);

    cardTemplate tmpl;

private:
    combatEvent* eve;

    QGraphicsView *combatView;
    QGraphicsScene *combatScene;
    combat_manager* manager;
    ironclad* player;

    TextItem* discard_pile = nullptr;
    TextItem* draw_pile = nullptr;

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
    void card_updated(abstractCard*);
    void entity_update(abstractEntity*);
    void attack(attackInfo&);
};

#endif // COMBATPAGE_H