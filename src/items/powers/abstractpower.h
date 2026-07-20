#ifndef ABSTRACTPOWER_H
#define ABSTRACTPOWER_H

#include <QObject>
#include "entity/abstractentity.h"
#include "combat/attack_info.h"
#include "combat/damage_info.h"
#include "combat/game_action.h"
#include "categories/powers.h"

class abstractPower : public QObject
{
    Q_OBJECT

protected:
    QString name;
    abstractEntity* owner;
    int priority_order;

    QString description;
    int amount;
    int time_affect = 1;
    int max_amount;
    int min_amount;

    bool is_buff;

    virtual QString generate_description() = 0;

public:

    abstractPower(QString name_init, abstractEntity* owner_init, int x, int max_x, int min_x, bool buff_init, int priority_init);
    ~abstractPower() override = default;

    QString get_name() { return name; }
    abstractEntity* get_owner() { return owner; }
    QString get_description() { return description; }
    virtual QString get_story() = 0;
    int get_amount() { return amount; }
    int get_order() { return priority_order;}
    bool get_is_buff() { return is_buff; }
    int get_time_affect() {return time_affect; }
    void set_time_affect(int x) {time_affect = x;}
    virtual powerID get_id() = 0;

    void increase(int x_init = 1);
    void decrease(int x_init = 1);

    virtual void modify_attack(attackInfo&) {};
    virtual void modify_incoming_damage(damageInfo&) {}
    virtual void modify_blocking(blockingInfo&) {}
    virtual void at_turn_start(game_action&) {};
    virtual void at_turn_end(game_action&) {};
    virtual void at_combat_start(game_action&) {};
    virtual void at_combat_end(game_action&) {};
    virtual void added_time(game_action&) {};
    virtual void damage_applied(game_action&) {};

};

#endif // ABSTRACTPOWER_H
