#ifndef ABSTRACTCARD_H
#define ABSTRACTCARD_H

#include <QObject>
#include <QWidget>
#include <QGraphicsItemGroup>

typedef enum CardType{attack, skill, power, status, curse}CardType;

class abstractCard : public QGraphicsItemGroup
{
private:

    QString base_name;
    QString base_description;
    CardType base_type;
    int base_energy;
    bool base_upgrated = false;
    bool base_exhaust = false;
    bool base_retain = false;
    bool base_ethereal = false;
    bool base_initial = false;

    QString name;
    QString description;
    CardType type;
    int energy;
    bool lock = false;
    bool upgrated = false;
    bool exhaust = false;
    bool retain = false;
    bool ethereal = false;
    bool initial = false;

    //card image + anim + music

    //card image + anim + music

public:
    abstractCard(QString name_init, QString description_init, CardType type_init, int energy_init);

    void set_name(const QString& name_init) { name = name_init; }
    void set_description(const QString& desc_init) { description = desc_init; }
    void set_energy(int energy_init) { energy = energy_init; }
    void set_lock(bool lock_init) { lock = lock_init; }
    void set_exhaust(bool bool_init) { exhaust = bool_init; }
    void set_retain(bool bool_init) { retain = bool_init; }
    void set_ethereal(bool bool_init) { ethereal = bool_init; }
    void set_initial(bool bool_init) { initial = bool_init; }

    QString get_name() { return name; }
    QString get_description() { return description; }
    CardType get_type() { return type; }
    int get_energy() { return energy; }
    bool get_lock() { return lock; }
    bool get_upgrated() { return upgrated; }
    bool get_exhaust() { return exhaust; }
    bool get_retain() { return retain; }
    bool get_ethereal() { return ethereal; }
    bool get_initial() { return initial; }

    void base_upgrade();
    void upgrade();
    virtual void play() = 0;

signals:
    void played(abstractCard*);
};

#endif // ABSTRACTCARD_H
