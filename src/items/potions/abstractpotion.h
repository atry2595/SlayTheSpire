#ifndef ABSTRACTPOTION_H
#define ABSTRACTPOTION_H

#include <QObject>
#include "categories/potions.h"
#include "combat/play_info.h"
#include "combat/game_action.h"
#include "categories/general.h"

class abstractEntity;

class abstractPotion : public QObject
{
    Q_OBJECT

protected:
    QString name;
    QString description;
    abstractEntity* owner;

public:
    static bool lock;
    abstractPotion(QString name_init, QString desc_init, abstractEntity* owner_init);
    ~abstractPotion() override = default;

    virtual void play(playInfo&) = 0;
    virtual void added_time(playInfo&) {};
    virtual potionID get_ID() = 0;
    virtual TargetType get_target_type() = 0;
    virtual PotionType get_type() = 0;
    virtual bool playable() { return true; }

    QString get_name() { return name; }
    QString get_description() { return description; }
    abstractEntity* get_owner() { return owner; }

};

#endif // ABSTRACTPOTION_H
