#ifndef ABSTRACTATTACKCARD_H
#define ABSTRACTATTACKCARD_H


#include "cards/abstractcard.h"

class abstractAttackCard : public abstractCard
{
    Q_OBJECT

protected:
    int base_damage;

    int damage;

    // sound effect + damage effect

    // sound effect + damage effect

public:
    abstractAttackCard(QString name_init, QString description_init, int energy_init, int damage_init,
                       bool upgraded_init, bool exhaust_init, bool retain_init, bool  ethereal_init, bool initial_init);
    ~abstractAttackCard() = default;
    void init();
    void reset() override;

    void set_damage(int damage_init) { damage = damage_init; }

    void play() override;
    virtual QString generate_description() = 0;

signals:
    void deal_damage(int);
};

#endif // ABSTRACTATTACKCARD_H
