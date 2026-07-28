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
class PotionParent;
class abstractRelic;
struct attackInfo;
struct damageInfo;
struct blockingInfo;
struct enemy_intent;
struct playCardInfo;
struct attackResult;
enum class PileType;

class combatEvent : public QObject{
    Q_OBJECT

signals:
    void game_lose();

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
    void card_added(abstractCard*);
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
    void campRest(abstractEntity*);
    void campSmith(abstractEntity*);

    //=============ui=========================
    void cardPressed(CardParent*);
    void cardMoved(CardParent*, const QPointF&);
    void cardReleased(CardParent*, const QPointF&);
    void potionPressed(PotionParent*);
    void potionMoved(PotionParent*, const QPointF&);
    void potionReleased(PotionParent*, const QPointF&);
    void cardUpdated(abstractCard*);
    void entityUpdate(abstractEntity*);
    void barUpdate();
    void afterAttack(attackResult&);
    void resetLayout();

    void relicRightButton(abstractRelic*);
    void potionRightButton(abstractPotion*);
    void powerRightButton(abstractPower*);
    void entityRightButton(abstractEntity*);

    void barExit();

    void cardSelected(abstractCard*);
    void selectCard(std::vector<abstractCard*>);

    void nextAction();

    void settingOpen();
    void settingClose();

    void relicSelected(abstractRelic*);

    void selectPotion(std::vector<abstractPotion*>);
    void potionSelected(abstractPotion*);

    void chestOpened();

};

#endif // COMBAT_EVENT_H
