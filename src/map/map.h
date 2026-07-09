#ifndef MAP_H
#define MAP_H

#include <QVector>
#include <QList>
#include <QString>
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
    QList<int> parentCols;

    Room(): type(RoomType::MONSTER),floor(-1),col(-1),visited(false), active(false){}
};

class Map{

private:


    QVector<QVector<Room>> grid;

    int currentFloor;
    int currentCol;

    void initGrid();
    void markVisited(int floor, int col);

    QVector<int> generateStartingColumns();

    void generatePaths();

    void buildPath(int startColumn);

    int chooseNextColumn(int floor, int currentCol);

    bool causesCrossing(int floor,int fromCol,int toCol) const;

    bool canConnect(int floor,int from,int to) const;

    void removeOrphanNodes();

    void mergeBossRoom();

    void minimumElite();

    void assignRoomTypes();

    void applyFixedFloors();

    RoomType randomRoomType();

    bool isInsideMap(int floor,int col) const;

    bool isRoomValid(int floor,int col,RoomType type) const;

    bool hasParentOfType(int floor,int col,RoomType type) const;

    bool hasChildOfType(int floor,int col,RoomType type) const;

    bool validateMap() const;

    bool validateBoss() const;

    bool validateTreasure() const;

    bool validateRest() const;

    bool validateConnections() const;

    bool validateCrossings() const;

    bool validateReachability() const;

    bool validateCoordinates() const;

    bool validateDuplicates() const;

    QList<Room*> getSelectableRooms();

public:

    static constexpr int TOTAL_FLOORS = 16;
    static constexpr int MAX_COLS = 7;
    static constexpr int TREASURE_FLOOR = 9;
    static constexpr int REST_FLOOR = 15;
    static constexpr int BOSS_FLOOR = 16;
    Map();
    void generate(); //کامل شود
    bool enterStartingRoom(int col);

    bool moveTo(int col);

    QList<Room> getAvailableRooms() const;
    QList<Room> getRoomsOnFloor(int floor) const;
    QList<Room> getNextRooms(int floor, int col) const;

    bool isFinished() const;

    int getCurrentFloor() const;

    int getCurrentColumn() const;
    Room& getRoom(int floor, int col);

    const Room& getRoom(int floor, int col) const;

    QString debugMap() const;

};

#endif