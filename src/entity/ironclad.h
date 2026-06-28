#ifndef IRONCLAD_H
#define IRONCLAD_H

#include <QWidget>
#include <vector>
#include "abstractentity.h"

enum class cards_name{strike, defend, bash};
enum class relic_name{burning_blood};

class ironclad : public abstractEntity
{
    Q_OBJECT

protected:

public:
    ironclad();

    static const std::vector<cards_name> starting_deck;

    static constexpr relic_name starting_relic = relic_name::burning_blood;

    static constexpr int starting_gold = 99;
};


#endif // IRONCLAD_H
