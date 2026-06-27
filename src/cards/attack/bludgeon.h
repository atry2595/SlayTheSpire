#ifndef BLUDGEON_H
#define BLUDGEON_H
#include <QObject>
#include "abstractattackcard.h"

class bludgeon : public abstractAttackCard
{
    Q_OBJECT

public:
    bludgeon(bool upgraded_init = false);
    QString generate_description() override;
    void play() override;
    void upgrade() override;
    void base_upgrade() override;
};

#endif // bludgeon_H
