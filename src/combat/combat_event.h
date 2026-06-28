#ifndef COMBAT_EVENT_H
#define COMBAT_EVENT_H

#include <QObject>

class abstractEntity;
class abstractCard;
struct attackInfo;
struct damageInfo;

class combatEvent : public QObject{
    Q_OBJECT

signals:
    void combat_started();
    void combat_ended(bool victory);

    void turn_started(abstractEntity*);
    void turn_ended(abstractEntity*);

    void card_played(abstractCard*);

    void attack_started(attackInfo&);
    void before_damage_taken(damageInfo&);

    void entity_killed(abstractEntity*);

    void hp_changed(abstractEntity*, int);
    void block_changed(abstractEntity*, int);
    void block_break(abstractEntity*);
    void damage_applied(damageInfo&);
};

#endif // COMBAT_EVENT_H
