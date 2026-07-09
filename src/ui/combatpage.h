// combatpage.h
#ifndef COMBATPAGE_H
#define COMBATPAGE_H

#include <QWidget>
#include <QGraphicsView>
#include <QGraphicsScene>

class CombatPage : public QWidget
{
    Q_OBJECT

public:
    explicit CombatPage(QWidget *parent = nullptr);

protected:
    void resizeEvent(QResizeEvent *event) override;

private:
    QGraphicsView *combatView;
    QGraphicsScene *combatScene;
};

#endif // COMBATPAGE_H