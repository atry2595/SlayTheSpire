#ifndef event_H
#define event_H

#include <QString>
#include <QStringList>
#include "combat/game_action.h"
#include "entity/abstractentity.h"

class Event
{
public:
//abstract entity*
//game action& در کانستراکتور این دو تا  رو باید کاربر بده
    // به عنوان متغیر ذخیره شه
    virtual ~Event() = default;

    virtual QString getName() const = 0;

    virtual QString getDescription() const = 0;

    virtual QStringList getChoices() const = 0;

    virtual bool canAppear(int act) const = 0;

    virtual void executeChoice(int choice, Player& player) = 0;
};

#endif