#ifndef CARNAGE_H
#define CARNAGE_H
#include <QObject>
#include "abstractattackcard.h"

class carnage : public abstractAttackCard
{
    Q_OBJECT

public:
    carnage(bool upgraded_init = false);
    QString generate_description() override;
    void play() override;
    void upgrade() override;
    void base_upgrade() override;
};

#endif // CARNAGE_H
