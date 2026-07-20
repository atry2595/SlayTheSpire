#ifndef DARKEMBRACEPOWER_H
#define DARKEMBRACEPOWER_H

#include "abstractpower.h"

class darkEmbracePower : public abstractPower
{
    Q_OBJECT
private:
    QMetaObject::Connection exhaust_card_connection;

public:
    darkEmbracePower(abstractEntity* owner_init, int x);
    void added_time(game_action&) override;
    QString generate_description() override;
    powerID get_id() override { return powerID::dark_embrace; }
    QString get_story() override;
};

#endif //DARKEMBRACEPOWER_H
