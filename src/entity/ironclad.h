#ifndef IRONCLAD_H
#define IRONCLAD_H

#include <QWidget>
#include <vector>
#include "abstractentity.h"

enum class cardID{strike, defend, bash};
enum class relicID{burning_blood};

class ironclad : public abstractEntity
{
    Q_OBJECT

protected:

public:
    ironclad();

    static const std::vector<cardID> starting_deck;

    static constexpr relicID starting_relic = relicID::burning_blood;

    static constexpr int starting_gold = 99;
};


#endif // IRONCLAD_H
