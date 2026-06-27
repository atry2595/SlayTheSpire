#ifndef TWIN_STRIKE_H
#define TWIN_STRIKE_H
#include <QObject>
#include "abstractattackcard.h"

class twin_strike : public abstractAttackCard
{
    Q_OBJECT

public:
    twin_strike(bool upgraded_init = false);
    QString generate_description() override;
    void play() override;
    void upgrade() override;
    void base_upgrade() override;
};

#endif // TWIN_STRIKE_H
