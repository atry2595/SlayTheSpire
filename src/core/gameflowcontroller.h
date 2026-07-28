#ifndef GAMEFLOWCONTROLLER_H
#define GAMEFLOWCONTROLLER_H

#include <QWidget>
#include "entity/ironclad.h"
#include <QStackedWidget>
#include "ui/selectItem/startingselect.h"

class GameFlowController : public QWidget
{
    Q_OBJECT
public:
    explicit GameFlowController(Player* plyr, QWidget *parent = nullptr);
    void start();

signals:
    void exitToMainMenu();

private:
    combatEvent* eve;
    ironclad* character;
    Stats* state;
    Player* player;

    QStackedWidget* stack;
    startingSelect* starting;
};

#endif // GAMEFLOWCONTROLLER_H
