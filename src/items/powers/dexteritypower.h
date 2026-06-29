#ifndef DEXTERITYPOWER_H
#define DEXTERITYPOWER_H

#include "abstractpower.h"

class dexterityPower : public abstractPower
{
    Q_OBJECT
public:
    dexterityPower(abstractEntity* owner_init, int x);
    void modify_blocking(blockingInfo&) override;
    QString generate_description() override;

};

#endif // DEXTERITYPOWER_H
