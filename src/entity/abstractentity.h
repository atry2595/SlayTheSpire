#ifndef ABSTRACTENTITY_H
#define ABSTRACTENTITY_H

#include <QObject>
#include "combat/attack_info.h"
#include "combat/damage_info.h"
#include "combat/combat_event.h"
#include "combat/blocking_info.h"
#include "categories/powers.h"
#include <vector>

class abstractPower;

class abstractEntity : public QObject
{
    Q_OBJECT

protected:
    QString name;
    int base_max_hp;

    int max_hp;
    int hp;
    int block;

    std::vector<abstractPower*> powers_list;
    bool block_reset_in_combat = true;

    // image + anim

    // image + anim

    void initial_set();

public:
    abstractEntity(QString name_init, int base_max_hp_init);
    virtual ~abstractEntity() = default;
    virtual void act_reset();
    virtual void combat_reset();
    virtual void turn_reset();

    void set_max_hp(int i_init) { max_hp = i_init; }
    void set_hp(int i_init) { hp = i_init; }
    void set_block(int i_init) { block = i_init; }
    void set_reset_block(bool b_init) { block_reset_in_combat = b_init; }

    int get_max_hp() { return max_hp;}
    int get_hp() { return hp;}
    int get_block() { return block;}

    void add_power(abstractPower*);
    void remove_power(abstractPower*);
    void remove_power_by_id(powerID);
    abstractPower* get_spec_power(powerID);

    virtual void modify_attack(attackInfo&) {};
    virtual void modify_incoming_damage(damageInfo&) {};
    virtual void modify_blocking(blockingInfo&) {};

};

#endif // ABSTRACTENTITY_H
