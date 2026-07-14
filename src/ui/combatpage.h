// combatpage.h
#ifndef COMBATPAGE_H
#define COMBATPAGE_H

#include <QWidget>
#include <QGraphicsView>
#include <QGraphicsScene>
#include "combat/manageCombat/combat_manager.h"
#include "ui/entities/enemyitem.h"
#include "ui/entities/ironcladitem.h"

class CombatPage : public QWidget
{
    Q_OBJECT

public:
    explicit CombatPage(QWidget *parent = nullptr, combat_manager* manager = nullptr);
    void reset_layout();
    void escape_entity(abstractEntity*);
    void died_entity(abstractEntity*);
    void remove_entity(abstractEntity*);

protected:
    void resizeEvent(QResizeEvent *event) override;

    void start_combat();
    void initialize_layout();

private:
    QGraphicsView *combatView;
    QGraphicsScene *combatScene;
    combat_manager* manager;

    int enemies_scene_width = 0;
    int players_scene_width = 0;

    std::vector<IroncladItem*> players;
    std::vector<EnemyItem*> enemies;
};

#endif // COMBATPAGE_H