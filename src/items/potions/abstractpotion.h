#ifndef ABSTRACTPOTION_H
#define ABSTRACTPOTION_H

#include <QObject>
#include "categories/potions.h"
#include "combat/play_info.h"

class abstractEntity;

class abstractPotion : public QObject
{
    Q_OBJECT

protected:
    QString name;
    abstractEntity* owner;

public:
    abstractPotion(QString name_init, abstractEntity* owner_init);
    virtual ~abstractPotion() = default;

    virtual void play(playInfo&) = 0;
    virtual potionID get_type() = 0;
    QString get_name() { return name; }
    abstractEntity* get_owner() { return owner; }

};

#endif // ABSTRACTPOTION_H
