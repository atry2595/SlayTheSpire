#ifndef ABSTRACTENTITY_H
#define ABSTRACTENTITY_H

#include <QObject>
#include "combat/attack_info.h"
#include "combat/damage_info.h"
#include "combat/combat_event.h"
#include "combat/blocking_info.h"
#include "categories/powers.h"
#include <vector>
#include "categories/enemies.h"

struct game_action;

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
    int gold = 0;

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

    virtual entityType get_type() = 0;
    virtual entityID get_ID() = 0;

    void set_max_hp(int i_init) { max_hp = i_init; }
    void set_hp(int i_init) { hp = i_init; }
    void set_block(int i_init) { block = i_init; }
    void set_reset_block(bool b_init) { block_reset_in_combat = b_init; }

    int get_max_hp() { return max_hp;}
    int get_hp() { return hp;}
    int get_block() { return block;}
    auto get_power_list() {return powers_list; }

    int get_gold() { return gold; }
    int lose_gold(int value) {
        int stolen = std::min(gold, value);
        gold -= stolen;
        return stolen;
    }
    void earn_coin(int value) { gold += value; }

    void add_power(game_action&, abstractPower*);
    void remove_power(abstractPower*);
    void remove_power_by_id(powerID);
    abstractPower* get_spec_power(powerID);
    void remove_zero_power();


    void modify_attack(attackInfo&);
    void modify_incoming_damage(damageInfo&);
    void modify_blocking(blockingInfo&);
    virtual void at_turn_start(game_action&);
    virtual void at_turn_end(game_action&);
    virtual void at_combat_start(game_action&);
    virtual void at_combat_end(game_action&);
    virtual void damage_applied(game_action&);



};

#endif // ABSTRACTENTITY_H
