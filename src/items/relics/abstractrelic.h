#ifndef ABSTRACTRELIC_H
#define ABSTRACTRELIC_H

#include <QObject>
#include "entity/abstractentity.h"
#include "combat/attack_info.h"
#include "combat/damage_info.h"
#include "combat/game_action.h"
#include "categories/relics.h"

class abstractRelic : public QObject
{
    Q_OBJECT

protected:
    QString name;
    abstractEntity* owner;

    QString description;

    virtual QString generate_description() = 0;

public:

    abstractRelic(QString name_init, abstractEntity* owner_init);

    QString get_name() { return name; }
    abstractEntity* get_owner() { return owner; }
    QString get_description() { return description; }
    virtual relicID get_id() = 0;
    virtual relicRarity get_rarity() = 0;

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

#endif // ABSTRACTRELIC_H
