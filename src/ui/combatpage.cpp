#include "combatpage.h"
#include <QVBoxLayout>
#include <QResizeEvent>
#include "ui/entities/getvisualdata.h"
#include <QTimer>


CombatPage::CombatPage(QWidget *parent, combat_manager* m)
    : QWidget{parent}
    , manager(m)
{
    combatView = new QGraphicsView(this);
    combatScene = new QGraphicsScene(this);

    combatScene->setSceneRect(0, 0, 1600, 900);
    combatView->setScene(combatScene);

    combatView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    combatView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    combatView->setFrameShape(QFrame::NoFrame);
    combatView->setStyleSheet("background: red;");

    combatView->setRenderHint(QPainter::Antialiasing);


    auto* layout = new QVBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);
    layout->addWidget(combatView);
    setLayout(layout);

    QMetaObject::invokeMethod(this, [this]() {
        combatView->fitInView(combatScene->sceneRect(), Qt::KeepAspectRatio);
    }, Qt::QueuedConnection);

    start_combat();
}



void CombatPage::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent(event);

    if (combatView && combatScene) {
        combatView->fitInView(combatScene->sceneRect(), Qt::KeepAspectRatioByExpanding);
    }
}



void CombatPage::start_combat() {
    if (!manager) return;

    initialize_layout();
}



void CombatPage::initialize_layout() {

    int players_count = manager->get_players().size();
    int sum_players_width = 1;
    int players_margine_width = 0;

    int enemies_count = manager->get_enemies().size();
    int sum_enemies_width = 1;
    int enemies_margine_width = 0;



    for (auto item :manager->get_players()){
        sum_players_width += getEntityVisual(item->get_ID()).size.width();
    }
    for (auto item : manager->get_enemies()){
        sum_enemies_width += getEntityVisual(item->get_ID()).size.width();
    }


    players_scene_width = std::min(sum_players_width * 1600 / (sum_players_width + sum_enemies_width), 800);
    enemies_scene_width = 1600 - players_scene_width;

    players_margine_width = (players_scene_width - sum_players_width) / (players_count + 1);
    enemies_margine_width = (enemies_scene_width - sum_enemies_width) / (enemies_count + 1);

    qreal x = players_margine_width;
    for (auto item : manager->get_players())  {
        auto p = new IroncladItem(item, {x, 565 - getEntityVisual(item->get_ID()).size.height()}, 100);
        players.push_back(p);
        combatScene->addItem(p->getParent());
        x += getEntityVisual(item->get_ID()).size.width() + players_margine_width;
    }

    x += enemies_margine_width;
    for (auto item : manager->get_enemies())  {
        auto p = new EnemyItem(item, {x, 565 - getEntityVisual(item->get_ID()).size.height()}, 200);
        enemies.push_back(p);
        combatScene->addItem(p->getParent());
        x += getEntityVisual(item->get_ID()).size.width() + enemies_margine_width;
    }

}



void CombatPage::reset_layout() {
    for (auto item : enemies) delete item;
    enemies.clear();

    int sum_enemy = 0;
    int count = 0;

    for (int i = 0; i < manager->get_enemies().size(); i++){
        if (manager->get_enemy_is_alive()[i]){
            count++;
            sum_enemy += getEntityVisual(manager->get_enemies()[i]->get_ID()).size.width();
        }
    }

    int margine = (enemies_scene_width - sum_enemy) / (count + 1);

    qreal x = players_scene_width + margine;

    for (int i = 0; i < manager->get_enemies().size(); i++){
        if (manager->get_enemy_is_alive()[i]){
            auto p = new EnemyItem(manager->get_enemies()[i], {x, 565 - getEntityVisual(manager->get_enemies()[i]->get_ID()).size.height()}, 200);
            enemies.push_back(p);
            combatScene->addItem(p->getParent());
            x += getEntityVisual(manager->get_enemies()[i]->get_ID()).size.width() + margine;
        }
    }
}