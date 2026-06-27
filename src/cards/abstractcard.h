#ifndef ABSTRACTCARD_H
#define ABSTRACTCARD_H

#include <QObject>
#include <QWidget>
#include <QGraphicsItemGroup>

typedef enum CardType{attack, skill, power, status, curse}CardType;

class abstractCard : public QGraphicsItemGroup
{
    Q_OBJECT

private:

    QString base_name;
    QString base_description;
    CardType base_type;
    int base_energy;
    bool base_upgrated;
    bool base_exhaust;
    bool base_retain;
    bool base_ethereal;
    bool base_initial;

    QString name;
    QString description;
    CardType type;
    int energy;
    bool lock;
    bool upgrated;
    bool exhaust;
    bool retain;
    bool ethereal;
    bool initial;

    //card image + generate + anim + music

    //card image + generate + anim + music

public:
    abstractCard(QString name_init, QString description_init, CardType type_init, int energy_init,
                 bool upgrated_init, bool exhaust_init, bool retain_init, bool  ethereal_init, bool initial_init);
    virtual ~abstractCard();
    void init();
    virtual void reset();

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

    virtual void base_upgrade() = 0;
    virtual void upgrade() = 0;
    virtual void play() = 0;

signals:
    void played(abstractCard*);
};

#endif // ABSTRACTCARD_H
