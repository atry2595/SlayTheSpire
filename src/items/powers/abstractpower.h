#ifndef ABSTRACTPOWER_H
#define ABSTRACTPOWER_H

#include <QObject>
#include "entity/abstractentity.h"
#include "combat/attack_info.h"
#include "combat/damage_info.h"

class abstractPower : public QObject
{
    Q_OBJECT

protected:
    QString name;
    abstractEntity* owner;

    QString description;
    int amount;
    int max_amount;
    int min_amount;

    bool is_buff;

    virtual QString generate_description() = 0;

public:

    abstractPower(QString name_init, abstractEntity* owner_init, int x, int max_x, int min_x, bool buff_init);

    QString get_name() { return name; }
    abstractEntity* get_owner() { return owner; }
    QString get_description() { return description; }
    int get_amount() { return amount; }

    void increase(int x_init = 1);
    void decrease(int x_init = 1);

    virtual void modify_attack(attackInfo&) {};
    virtual void modify_incoming_damage(damageInfo&) {}
    // virtual void modify_blocking(int value) { return value; }
    virtual void at_turn_start() {};
    virtual void at_turn_end() {};
    virtual void at_combat_start() {};
    virtual void at_combat_end() {};

};

#endif // ABSTRACTPOWER_H
