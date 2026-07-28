#include "gameflowcontroller.h"
#include <QVBoxLayout>

GameFlowController::GameFlowController(Player* plyr, QWidget *parent)
    : QWidget(parent)
    , player(plyr)
{
    eve = new combatEvent();
    character = new ironclad(eve);
    state = new Stats();

    stack = new QStackedWidget(this);

    auto* layout = new QVBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);
    layout->addWidget(stack);
    setLayout(layout);
}

void GameFlowController::start() {
    starting = new startingSelect(this, eve);
    stack->addWidget(starting);
    stack->setCurrentWidget(starting);
}
