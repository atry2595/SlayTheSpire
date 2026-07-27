#ifndef ABSTRACTCARD_H
#define ABSTRACTCARD_H

#include <QObject>

#include "combat/play_info.h"
#include "categories/cards.h"
#include "categories/general.h"
#include "entity/abstractentity.h"


class abstractCard : public QObject
{
    Q_OBJECT

protected:

    QString base_name;
    QString base_description;
    bool base_is_playable = true;
    int base_energy;
    bool base_is_upgraded = false;
    bool base_is_exhaust = false;
    bool base_is_retain = false;
    bool base_is_ethereal = false;
    bool base_is_initial = false;

    QString name;
    QString description;
    bool playable = true;
    int energy;
    bool turn_lock = false;
    bool is_upgraded = false;
    bool is_exhaust = false;
    bool is_retain = false;
    bool is_ethereal = false;
    bool is_initial = false;

    bool available = false;


    //card image + generate + anim + music

    //card image + generate + anim + music

    void initial_set();

public:
    abstractCard() {};
    abstractCard(QString name_init, QString description_init, int energy_init,
                 bool exhaust_init, bool retain_init,
                 bool  ethereal_init, bool initial_init);

    virtual ~abstractCard() = default;
    virtual void combat_reset();
    virtual void turn_reset();

    virtual CardType get_card_type() = 0;
    virtual cardID get_card_id() = 0;
    virtual bool is_rare() = 0;
    virtual TargetType get_target_type() = 0;
    virtual void damage_applied() {};
    virtual bool can_remove_from_deck() { return true; }
    virtual bool repeat_x_time() { return false; }
    virtual bool is_strike() { return false; }


    void set_name(const QString& name_init) { name = name_init; }
    void set_description(const QString& desc_init) { description = desc_init; }
    void set_energy(int energy_init) { energy = energy_init; }
    void set_lock(bool lock_init) { turn_lock = lock_init; }
    void set_playable(bool play_init) { playable = play_init; }
    void set_available(bool b_init) { available = b_init; }
    void set_exhaust(bool bool_init) { is_exhaust = bool_init; }
    void set_retain(bool bool_init) { is_retain = bool_init; }
    void set_ethereal(bool bool_init) { is_ethereal = bool_init; }
    void set_initial(bool bool_init) { is_initial = bool_init; }

    QString get_name() { return name; }
    QString get_description() { return description; }
    int get_energy() { return energy; }
    bool get_turn_lock() { return turn_lock; }
    bool get_turn_playable() { return playable; }
    bool get_available() { return available; }
    bool get_upgraded() { return is_upgraded; }
    bool get_exhaust() { return is_exhaust; }
    bool get_retain() { return is_retain; }
    bool get_ethereal() { return is_ethereal; }
    bool get_initial() { return is_initial; }

    virtual void base_upgrade() = 0;
    virtual void upgrade() = 0;
    virtual void play(playInfo& play_info) = 0;
    virtual void hand_turn_end(playInfo& play_info) {};
    virtual void hand_turn_start(playInfo& play_info) {};

    virtual void update(playInfo& info);
};

#endif // ABSTRACTCARD_H
