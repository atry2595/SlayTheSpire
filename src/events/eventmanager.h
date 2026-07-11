#ifndef EVENTMANAGER_H
#define EVENTMANAGER_H

#include <QObject>
#include <QList>

class Event;

class EventManager
{
public:

    EventManager();

    Event* getRandomEvent(int act);

private:

    QList<Event*> act1Events;
    QList<Event*> act2Events;
    QList<Event*> shrineEvents;
};

#endif
