#ifndef ABSTRACTCARD_H
#define ABSTRACTCARD_H

#include <QObject>
#include <QGraphicsItemGroup>

#include "combat/play_info.h"

class Entity;

typedef enum CardType{attack, skill, power, status, curse}CardType;

class abstractCard : public QGraphicsItemGroup
{
    Q_OBJECT

protected:

    QString base_name;
    QString base_description;
    int base_energy;
    bool base_is_upgraded;
    bool base_is_exhaust;
    bool base_is_retain;
    bool base_is_ethereal;
    bool base_is_initial;

    QString name;
    QString description;
    int energy;
    bool lock;
    bool playable;
    bool is_upgraded;
    bool is_exhaust;
    bool is_retain;
    bool is_ethereal;
    bool is_initial;


    //card image + generate + anim + music

    //card image + generate + anim + music

    void initial_set();

public:
    abstractCard() {};
    abstractCard(QString name_init, QString description_init, int energy_init,
                 bool upgraded_init, bool exhaust_init, bool retain_init,
                 bool  ethereal_init, bool initial_init);

    virtual ~abstractCard() = default;
    virtual void reset();

    void set_name(const QString& name_init) { name = name_init; }
    void set_description(const QString& desc_init) { description = desc_init; }
    void set_energy(int energy_init) { energy = energy_init; }
    void set_lock(bool lock_init) { lock = lock_init; }
    void set_playable(bool play_init) { playable = play_init; }
    void set_exhaust(bool bool_init) { is_exhaust = bool_init; }
    void set_retain(bool bool_init) { is_retain = bool_init; }
    void set_ethereal(bool bool_init) { is_ethereal = bool_init; }
    void set_initial(bool bool_init) { is_initial = bool_init; }

    QString get_name() { return name; }
    QString get_description() { return description; }
    int get_energy() { return energy; }
    bool get_lock() { return lock; }
    bool get_playbale() { return playable; }
    bool get_upgraded() { return is_upgraded; }
    bool get_exhaust() { return is_exhaust; }
    bool get_retain() { return is_retain; }
    bool get_ethereal() { return is_ethereal; }
    bool get_initial() { return is_initial; }

    virtual void base_upgrade() = 0;
    virtual void upgrade() = 0;
    virtual void play(playInfo& play_info) = 0;
};

#endif // ABSTRACTCARD_H
