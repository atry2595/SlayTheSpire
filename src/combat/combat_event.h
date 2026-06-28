#ifndef COMBAT_EVENT_H
#define COMBAT_EVENT_H

#include <QObject>

class Entity;
class abstractCard;
struct attackInfo;
struct damageInfo;

class combatEvent : public QObject{
    Q_OBJECT

signals:
    void combat_started();
    void combat_ended(bool victory);

    void turn_started(Entity*);
    void turn_ended(Entity*);

    void card_played(abstractCard*);

    void attack_started(attackInfo&);
    void before_loseHP(damageInfo&);

    void enemy_killed(Entity*);

    void hp_changed(Entity*, int);
    void block_changed(Entity*, int);
    void block_break(Entity*);
    void damage_applied(damageInfo&);
};

#endif // COMBAT_EVENT_H
