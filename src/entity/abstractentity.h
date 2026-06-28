#ifndef ABSTRACTENTITY_H
#define ABSTRACTENTITY_H

#include <QObject>
#include "combat/attack_info.h"
#include "combat/damage_info.h"
#include "combat/combat_event.h"

class abstractEntity
{
    Q_OBJECT

protected:
    QString name;
    int base_max_hp;

    int max_hp;
    int hp;
    int block;

    // image + anim

    // image + anim

public:
    abstractEntity(QString name_init, int base_max_hp_init);
    virtual ~abstractEntity() = default;
    virtual void initial_set();
    virtual void reset();

    void set_max_hp(int i_init) { max_hp = i_init; }
    void set_hp(int i_init) { hp = i_init; }
    void set_block(int i_init) { block = i_init; }

    int get_max_hp() { return max_hp;}
    int get_hp() { return hp;}
    int get_block() { return block;}

    virtual void modify_attack(attackInfo&);
    virtual void modify_incoming_damage(damageInfo&);

};

#endif // ABSTRACTENTITY_H
