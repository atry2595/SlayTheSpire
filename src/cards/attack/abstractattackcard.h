#ifndef ABSTRACTATTACKCARD_H
#define ABSTRACTATTACKCARD_H


#include "cards/abstractcard.h"

class abstractAttackCard : public abstractCard
{
    Q_OBJECT

protected:
    void perform_attack(abstractEntity* attacker, std::vector<abstractEntity*>& target_list, game_action& actions) const;

    int base_damage;

    int damage;

    // sound effect + damage effect

    // sound effect + damage effect

    void initial_set();

public:
    static constexpr CardType type = CardType::attack;

    abstractAttackCard(QString name_init, QString description_init, int energy_init, int damage_init,
                       bool upgraded_init, bool exhaust_init, bool retain_init, bool  ethereal_init, bool initial_init);

    ~abstractAttackCard() = default;
    void reset() override;

    void set_damage(int damage_init) { damage = damage_init; }
    int get_damage() { return damage; }

    virtual QString generate_description() = 0;

};

#endif // ABSTRACTATTACKCARD_H
