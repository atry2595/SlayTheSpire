#include "combatpage.h"
#include <QVBoxLayout>
#include <QResizeEvent>
#include "baseitem.h"

CombatPage::CombatPage(QWidget *parent)
    : QWidget{parent}
{
    combatView = new QGraphicsView(this);
    combatScene = new QGraphicsScene(this);

    combatScene->setSceneRect(0, 0, 16000, 9000);
    combatView->setScene(combatScene);

    combatView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    combatView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    combatView->setRenderHint(QPainter::Antialiasing);





    auto* layout = new QVBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);
    layout->addWidget(combatView);
    setLayout(layout);

    QMetaObject::invokeMethod(this, [this]() {
        combatView->fitInView(combatScene->sceneRect(), Qt::KeepAspectRatio);
    }, Qt::QueuedConnection);

}

void CombatPage::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent(event);

    if (combatView && combatScene) {
        combatView->fitInView(combatScene->sceneRect(), Qt::KeepAspectRatio);
    }
}