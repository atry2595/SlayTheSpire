#include "combatpage.h"
#include <QVBoxLayout>

CombatPage::CombatPage(QWidget *parent)
    : QWidget{parent}
{
    combatView = new QGraphicsView(this);
    combatScene = new QGraphicsScene(this);






    combatView->setSceneRect(0,0,1920,1080);
    combatView->setScene(combatScene);

    auto* layout = new QVBoxLayout(this);
    layout->setContentsMargins(0,0,0,0);
    layout->setSpacing(0);

    layout->addWidget(combatView);

    setLayout(layout);


}
