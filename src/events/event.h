#ifndef event_H
#define event_H

#include <QString>
#include <QStringList>

class Player;

class Event
{
public:

    virtual ~Event() = default;

    virtual QString getName() const = 0;

    virtual QString getDescription() const = 0;

    virtual QStringList getChoices() const = 0;

    virtual void executeChoice(int choice, Player& player) = 0;
};

#endif