#ifndef MAP_H
#define MAP_H

#include <QVector>
#include <QList>
#include "utils/RNG.h"

enum class RoomType{
    MONSTER,
    ELITE,
    REST,
    MERCHANT,
    TREASURE,
    UNKNOWN, // ؟
    BOSS
};

struct Room
{
    RoomType type;
    int floor;
    int col;
    bool visited;
    bool active; // +
    QList<int> nextCols;

    Room(): type(RoomType::MONSTER),floor(-1),col(-1),visited(false){}
};

class Map{

private:
    QVector<QVector<Room>> grid; //grid[floor-1][column-1]
    QVector<int> generateStartingColumns();

    void initGrid();

    void generatePaths();
    void generateSinglePath(int startColumn);
    bool causesCrossing(int floor,int fromCol,int toCol) const;
    // ؟ ...
    RoomType randomRoomType();


public:

    static constexpr int TOTAL_FLOORS = 16;
    static constexpr int MAX_COLS = 7;
    static constexpr int TREASURE_FLOOR = 9;
    static constexpr int REST_FLOOR = 15;
    static constexpr int BOSS_FLOOR = 16;
    Map();
    void generate(); //کامل شود


};




#endif