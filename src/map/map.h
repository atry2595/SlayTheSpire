#ifndef MAP_H
#define MAP_H

#include <QVector>
#include <QList>

enum class RoomType{
    MONSTER,
    ELITE,
    REST,
    MERCHANT,
    TREASURE,
    EVENT,
    BOSS
};

class Map{
public:

    static constexpr int TOTAL_FLOORS = 16;
    static constexpr int MAX_COLS = 7;
    static constexpr int TREASURE_FLOOR = 9;
    static constexpr int REST_FLOOR = 15;
    static constexpr int BOSS_FLOOR = 16;

};

#endif