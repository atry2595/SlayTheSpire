#ifndef BLOCKPOTION_H
#define BLOCKPOTION_H

#include "abstractpotion.h"

class blockPotion : public abstractPotion
{
    Q_OBJECT
public:
    blockPotion(abstractEntity* owner);
    void play(playInfo&) override;
    potionID get_type() override { return potionID::block_potion; }
};

#endif // BLOCKPOTION_H
