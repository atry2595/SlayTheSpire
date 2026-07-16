#ifndef COMBAT_EVENT_H
#define COMBAT_EVENT_H

#include <QObject>
#include <QPointF>

class abstractEntity;
class abstractCard;
class abstractPower;
class abstractPotion;
class combat_manager;
class CardParent;
struct attackInfo;
struct damageInfo;
struct blockingInfo;
struct enemy_intent;
struct playCardInfo;
enum class PileType;

class combatEvent : public QObject{
    Q_OBJECT

signals:
    void combat_started(combat_manager*);
    void combat_ended(combat_manager*, bool victory);

    void turn_started(abstractEntity*);
    void turn_ended(abstractEntity*);

    void attack_started(attackInfo&);
    void damage_before_taken(damageInfo&);
    void damage_before_blocking(damageInfo&);
    void before_block_set(blockingInfo&);

    void entity_killed(abstractEntity*);
    void entity_removed(abstractEntity*);
    void entity_escape(abstractEntity*);
    void entity_add_after(abstractEntity* entity, abstractEntity* after);
    void entity_add_before(abstractEntity* entity, abstractEntity* before);

    void hp_changed(abstractEntity*, int oldHP, int newHP);
    void block_changed(blockingInfo&);
    void block_break(blockingInfo&);
    void damage_applied(damageInfo&);

    void card_played(playCardInfo&);
    void card_moved(playCardInfo&, PileType from, PileType to);
    void draw_pile_shuffled();
    void card_locked(playCardInfo&);
    void card_disabled(playCardInfo&);

    void intent_changed(abstractEntity*);
    void power_added(abstractPower*);
    void power_changed(abstractPower*);
    void power_removed(abstractPower*);
    void potion_added(abstractPotion*);
    void potion_used(abstractPotion*);
    void potion_removed(abstractPotion*);

    void lift(abstractEntity*);

    //=============ui=========================
    void cardPressed(CardParent*);
    void cardMoved(CardParent*, const QPointF&);
    void cardReleased(CardParent*, const QPointF&);
    void cardUpdated(abstractCard*);

};

#endif // COMBAT_EVENT_H
