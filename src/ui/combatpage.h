#ifndef COMBATPAGE_H
#define COMBATPAGE_H

#include <QWidget>
#include <QGraphicsView>
#include <QGraphicsScene>

class CombatPage : public QWidget
{
    Q_OBJECT
private:
    QGraphicsView* combatView;
    QGraphicsScene* combatScene;

public:
    explicit CombatPage(QWidget *parent = nullptr);

signals:
};

#endif // COMBATPAGE_H
