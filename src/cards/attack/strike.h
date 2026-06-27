#ifndef STRIKE_H
#define STRIKE_H
#include <QObject>
#include "abstractattackcard.h"

class strike : public abstractAttackCard
{
    Q_OBJECT

public:
    strike(bool upgraded_init = false);
    QString generate_description() override;
    void play() override;
    void upgrade() override;
    void base_upgrade() override;
};

#endif // STRIKE_H
