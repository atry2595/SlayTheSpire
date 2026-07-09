
#include "Map.h"
#include <QQueue>
#include <QSet>
#include <QDebug>

Map::Map()
{
    grid.resize(TOTAL_FLOORS);

    for(int floor = 0;floor < TOTAL_FLOORS ; ++floor)
    {
        grid[floor].resize(MAX_COLS);
    }
    initGrid();

    currentFloor = 0;
    currentCol = -1;
}

void Map::initGrid()
{
    for (int floor = 0; floor < TOTAL_FLOORS; floor++)
    {
        for (int col = 0; col < MAX_COLS; col++)
        {
            Room& room = grid[floor][col];

            room.floor = floor;
            room.col = col;

            room.type = RoomType::MONSTER;

            room.active = false;
            room.visited = false;

            room.nextCols.clear();
            room.parentCols.clear();
        }
    }
}

void Map::markVisited(int floor, int col)
{
    if (!isInsideMap(floor, col))
        return;

    grid[floor][col].visited = true;
}

bool Map::isInsideMap(int floor, int col) const
{
    return floor >= 0 &&
           floor < TOTAL_FLOORS &&
           col >= 0 &&
           col < MAX_COLS;
}

QVector<int> Map::generateStartingColumns()
{
    QVector<int> starts;

    int pathCount = RNG::instance().randint(4, 6);

    double spacing = double(MAX_COLS - 1) / double(pathCount - 1);

    for (int i = 0; i < pathCount; i++)
    {
        int col = qRound(i * spacing);

        col += RNG::instance().randint(-1, 1);

        col = qBound(0, col, MAX_COLS - 1);

        while (starts.contains(col))
        {
            if (col < MAX_COLS - 1)
                col++;
            else if (col > 0)
                col--;
            else
                break;
        }

        starts.append(col);
    }

    std::sort(starts.begin(), starts.end());

    return starts;
}

void Map::buildPath(int startColumn)
{
    int currentCol = startColumn;

    for (int floor = 0; floor < TOTAL_FLOORS - 1; floor++)
    {
        Room& current = grid[floor][currentCol];

        current.active = true;

        int nextCol = chooseNextColumn(floor, currentCol);

        if (nextCol == -1)
        {
            nextCol = currentCol;
        }

        if (!current.nextCols.contains(nextCol))
        {
            current.nextCols.append(nextCol);
        }

        Room& nextRoom = grid[floor + 1][nextCol];

        nextRoom.active = true;

        if (!nextRoom.parentCols.contains(currentCol))
        {
            nextRoom.parentCols.append(currentCol);
        }

        currentCol = nextCol;
    }

    grid[TOTAL_FLOORS - 1][currentCol].active = true;
}

int Map::chooseNextColumn(int floor, int currentCol)
{
    QVector<int> candidates;


    for(int delta = -1; delta <= 1; delta++)
    {
        int nextCol = currentCol + delta;

        if(nextCol < 0 || nextCol >= MAX_COLS)
            continue;

        if(causesCrossing(floor, currentCol, nextCol))
            continue;

        candidates.append(nextCol);
    }

    if(candidates.isEmpty())
        return currentCol;

    QVector<int> weighted;

    for(int nextCol : candidates)
    {
        if(nextCol == currentCol)
        {
            weighted.append(nextCol);
            weighted.append(nextCol);
            weighted.append(nextCol);
        }
        else
        {
            weighted.append(nextCol);
        }

        if(grid[floor + 1][nextCol].parentCols.isEmpty())
        {
            weighted.append(nextCol);
        }
    }

    int index =RNG::instance().randint(0, weighted.size() - 1);

    return weighted[index];
}

void Map::generatePaths()
{
    QVector<int> starts = generateStartingColumns();

    for (int startCol : starts)
    {
        buildPath(startCol);
    }
}

bool Map::causesCrossing(int floor, int fromCol, int toCol) const
{
    for(int col = 0; col < MAX_COLS; col++)
    {
        const Room& room = grid[floor][col];

        if(!room.active)
            continue;

        for(int nextCol : room.nextCols)
        {
            if(col == fromCol)
                continue;

            if(nextCol == toCol)
                continue;

            if(col < fromCol && nextCol > toCol)
                return true;

            if(col > fromCol && nextCol < toCol)
                return true;
        }
    }

    return false;
}

void Map::removeOrphanNodes()
{
    bool changed;

    do
    {
        changed = false;

        for(int floor = 0; floor < TOTAL_FLOORS; floor++)
        {
            for(int col = 0; col < MAX_COLS; col++)
            {
                Room& room = grid[floor][col];

                if(!room.active)
                    continue;

                bool hasParent =(floor == 0) || !room.parentCols.isEmpty();

                bool hasChild =(floor == TOTAL_FLOORS - 1) || !room.nextCols.isEmpty();

                if(!hasParent || !hasChild)
                {
                    room.active = false;

                    room.parentCols.clear();
                    room.nextCols.clear();

                    changed = true;
                }
            }
        }

        if(changed)
        {
            for(int floor = 0; floor < TOTAL_FLOORS; floor++)
            {
                for(int col = 0; col < MAX_COLS; col++)
                {
                    Room& room = grid[floor][col];

                    if(!room.active)
                        continue;

                    if(floor > 0)
                    {
                        for(int i = room.parentCols.size() - 1; i >= 0; i--)
                        {
                            int parentCol = room.parentCols[i];

                            if(!grid[floor - 1][parentCol].active)
                            {
                                room.parentCols.removeAt(i);
                            }
                        }
                    }

                    if(floor < TOTAL_FLOORS - 1)
                    {
                        for(int i = room.nextCols.size() - 1; i >= 0; i--)
                        {
                            int childCol = room.nextCols[i];

                            if(!grid[floor + 1][childCol].active)
                            {
                                room.nextCols.removeAt(i);
                            }
                        }
                    }
                }
            }
        }

    }
    while(changed);
}

void Map::assignRoomTypes()
{
    for (int floor = 0; floor < TOTAL_FLOORS; floor++)
    {
        for (int col = 0; col < MAX_COLS; col++)
        {
            Room& room = grid[floor][col];

            if (!room.active)
                continue;

            if (floor <= 1)
            {
                room.type = RoomType::MONSTER;
                continue;
            }

            if (floor == TREASURE_FLOOR - 1)
            {
                room.type = RoomType::TREASURE;
                continue;
            }

            if (floor == BOSS_FLOOR - 1)
            {
                room.type = RoomType::BOSS;
                continue;
            }

            if (floor == REST_FLOOR - 1)
            {
                room.type = RoomType::REST;
                continue;
            }

            RoomType type = RoomType::MONSTER;

            bool found = false;

            for (int attempt = 0; attempt < 50; attempt++)
            {
                RoomType candidate = randomRoomType();

                if (isRoomValid(floor, col, candidate))
                {
                    type = candidate;
                    found = true;
                    break;
                }
            }

            if (!found)
            {
                type = RoomType::MONSTER;
            }

            room.type = type;
        }
    }

}
RoomType Map::randomRoomType()
{
    std::vector<RoomType> types =
        {
            RoomType::MONSTER,
            RoomType::UNKNOWN,
            RoomType::REST,
            RoomType::ELITE,
            RoomType::MERCHANT
        };

    std::vector<double> weights =
        {
            53.0,
            22.0,
            12.0,
            8.0,
            5.0
        };

    return RNG::instance().weighted_choice(types, weights);
}

void Map::applyFixedFloors()
{
    for(int col = 0; col < MAX_COLS; col++)
    {
        if(grid[TREASURE_FLOOR - 1][col].active)
        {
            grid[TREASURE_FLOOR - 1][col].type =RoomType::TREASURE;
        }
    }

    for(int col = 0; col < MAX_COLS; col++)
    {
        if(grid[REST_FLOOR - 1][col].active)
        {
            grid[REST_FLOOR - 1][col].type =RoomType::REST;
        }
    }

    for(int col = 0; col < MAX_COLS; col++)
    {
        if(grid[BOSS_FLOOR - 1][col].active)
        {
            grid[BOSS_FLOOR - 1][col].type =RoomType::BOSS;
        }
    }
}

bool Map::hasParentOfType(int floor, int col, RoomType type) const
{
    if(floor == 0)
        return false;

    for(int parentCol : grid[floor][col].parentCols)
    {
        if(grid[floor - 1][parentCol].type == type)
            return true;
    }

    return false;
}

bool Map::hasChildOfType(int floor, int col, RoomType type) const
{
    if(floor == TOTAL_FLOORS - 1)
        return false;

    for(int childCol : grid[floor][col].nextCols)
    {
        if(grid[floor + 1][childCol].type == type)
            return true;
    }

    return false;
}

bool Map::isRoomValid(int floor, int col, RoomType type) const
{
    if (!isInsideMap(floor, col))
        return false;

    const Room& room = getRoom(floor, col);

    if (!room.active)
        return false;

    if (type == RoomType::TREASURE)
        return floor == TREASURE_FLOOR - 1;

    if (type == RoomType::BOSS)
        return floor == BOSS_FLOOR - 1;

    if (type == RoomType::REST)
    {
        if (floor == REST_FLOOR - 1)
            return true;

        if (floor < 2)
            return false;

        if (hasParentOfType(floor, col, RoomType::REST))
            return false;

        return true;
    }

    if (type == RoomType::MERCHANT)
    {
        if (hasParentOfType(floor, col, RoomType::MERCHANT))
            return false;
    }

    if (type == RoomType::ELITE)
    {
        if (hasParentOfType(floor, col, RoomType::ELITE))
            return false;
    }

    return true;
}

void Map::mergeBossRoom()
{
    int bossCol = MAX_COLS / 2;

    for(int col = 0; col < MAX_COLS; col++)
    {
        grid[BOSS_FLOOR - 1][col].active = false;
        grid[BOSS_FLOOR - 1][col].parentCols.clear();
        grid[BOSS_FLOOR - 1][col].nextCols.clear();
    }

    Room& boss = grid[BOSS_FLOOR - 1][bossCol];

    boss.active = true;

    for(int col = 0; col < MAX_COLS; col++)
    {
        Room& room = grid[REST_FLOOR - 1][col];

        if(!room.active)
            continue;

        room.nextCols.clear();
        room.nextCols.append(bossCol);

        boss.parentCols.append(col);
    }
}

bool Map::enterStartingRoom(int col)
{
    if(col < 0 || col >= MAX_COLS)
        return false;

    if(!grid[0][col].active)
        return false;

    currentFloor = 0;
    currentCol = col;

    markVisited(0,col);

    return true;
}

bool Map::moveTo(int col)
{
    if(currentCol == -1)
        return false;

    const Room& current =getRoom(currentFloor,currentCol);

    if(!current.nextCols.contains(col))
        return false;

    currentFloor++;

    currentCol = col;

    markVisited(currentFloor,col);

    return true;
}

QList<Room> Map::getRoomsOnFloor(int floor) const
{
    QList<Room> rooms;

    if (!isInsideMap(floor, 0))
        return rooms;

    for (int col = 0; col < MAX_COLS; col++)
    {
        const Room& room = grid[floor][col];

        if (room.active)
        {
            rooms.append(room);
        }
    }

    return rooms;
}

QList<Room> Map::getAvailableRooms() const
{
    if(currentCol == -1)
        return getRoomsOnFloor(0);

    return getNextRooms(currentFloor,currentCol);
}

bool Map::isFinished() const
{
    return currentFloor == BOSS_FLOOR-1;
}

int Map::getCurrentFloor() const
{
    return currentFloor;
}

int Map::getCurrentColumn() const
{
    return currentCol;
}

Room& Map::getRoom(int floor, int col)
{
    return grid[floor][col];
}

const Room& Map::getRoom(int floor, int col) const
{
    return grid[floor][col];
}

QList<Room> Map::getNextRooms(int floor, int col) const
{
    QList<Room> rooms;

    if (!isInsideMap(floor, col))
        return rooms;

    const Room& current = grid[floor][col];

    for (int nextCol : current.nextCols)
    {
        if (isInsideMap(floor + 1, nextCol))
        {
            rooms.append(grid[floor + 1][nextCol]);
        }
    }

    return rooms;
}

QList<Room*> Map::getSelectableRooms()
{
    QList<Room*> rooms;

    if(currentCol == -1)
    {
        for(int col = 0; col < MAX_COLS; col++)
        {
            Room& room = getRoom(0,col);

            if(room.active)
                rooms.append(&room);
        }

        return rooms;
    }

    Room& current =getRoom(currentFloor,currentCol);

    for(int nextCol : current.nextCols)
    {
        rooms.append(&getRoom(currentFloor + 1,nextCol));
    }

    return rooms;
}

void Map::minimumElite()
{
    int eliteCount = 0;

    for(int floor = 0; floor < TOTAL_FLOORS; floor++)
    {
        for(int col = 0; col < MAX_COLS; col++)
        {
            const Room& room = grid[floor][col];

            if(room.active && room.type == RoomType::ELITE)
            {
                eliteCount++;
            }
        }
    }

    if(eliteCount >= 6)
        return;

    for(int floor = 2; floor < TOTAL_FLOORS; floor++)
    {
        if(floor == TREASURE_FLOOR - 1)
            continue;

        if(floor == REST_FLOOR - 1)
            continue;

        if(floor == BOSS_FLOOR - 1)
            continue;

        for(int col = 0; col < MAX_COLS; col++)
        {
            Room& room = grid[floor][col];

            if(!room.active)
                continue;

            if(room.type != RoomType::MONSTER)
                continue;

            if(!isRoomValid(floor, col, RoomType::ELITE))
                continue;

            room.type = RoomType::ELITE;

            eliteCount++;

            if(eliteCount >= 6)
                return;
        }
    }
}

bool Map::validateBoss() const
{
    int bossCount = 0;
    int bossCol = -1;

    for(int col = 0; col < MAX_COLS; col++)
    {
        const Room& room = grid[BOSS_FLOOR - 1][col];

        if(room.active)
        {
            bossCount++;
            bossCol = col;

            if(room.type != RoomType::BOSS)
                return false;
        }
    }

    if(bossCount != 1)
        return false;

    const Room& boss = grid[BOSS_FLOOR - 1][bossCol];

    if(!boss.nextCols.isEmpty())
        return false;

    if(boss.parentCols.isEmpty())
        return false;

    for(int parentCol : boss.parentCols)
    {
        const Room& parent = grid[REST_FLOOR - 1][parentCol];

        if(!parent.active)
            return false;

        if(!parent.nextCols.contains(bossCol))
            return false;
    }

    return true;
}

bool Map::validateTreasure() const
{
    for(int col = 0; col < MAX_COLS; col++)
    {
        const Room& room = grid[TREASURE_FLOOR - 1][col];

        if(!room.active)
            continue;

        if(room.type != RoomType::TREASURE)
            return false;
    }

    for(int floor = 0; floor < TOTAL_FLOORS; floor++)
    {
        if(floor == TREASURE_FLOOR - 1)
            continue;

        for(int col = 0; col < MAX_COLS; col++)
        {
            const Room& room = grid[floor][col];

            if(!room.active)
                continue;

            if(room.type == RoomType::TREASURE)
                return false;
        }
    }

    return true;
}

bool Map::validateRest() const
{
    for(int col = 0; col < MAX_COLS; col++)
    {
        const Room& room = grid[REST_FLOOR - 1][col];

        if(!room.active)
            continue;

        if(room.type != RoomType::REST)
            return false;
    }

    return true;
}

bool Map::validateConnections() const
{
    for(int floor = 0; floor < TOTAL_FLOORS; floor++)
    {
        for(int col = 0; col < MAX_COLS; col++)
        {
            const Room& room = grid[floor][col];

            if(!room.active)
                continue;

            if(floor != 0)
            {
                if(room.parentCols.isEmpty())
                    return false;
            }

            if(floor != TOTAL_FLOORS - 1)
            {
                if(room.nextCols.isEmpty())
                    return false;
            }

            for(int parentCol : room.parentCols)
            {
                if(parentCol < 0 || parentCol >= MAX_COLS)
                    return false;

                const Room& parent =
                    grid[floor - 1][parentCol];

                if(!parent.active)
                    return false;

                if(!parent.nextCols.contains(col))
                    return false;
            }

            for(int childCol : room.nextCols)
            {
                if(childCol < 0 || childCol >= MAX_COLS)
                    return false;

                const Room& child =
                    grid[floor + 1][childCol];

                if(!child.active)
                    return false;

                if(!child.parentCols.contains(col))
                    return false;
            }
        }
    }

    return true;
}

bool Map::validateDuplicates() const
{
    for(int floor = 0; floor < TOTAL_FLOORS; floor++)
    {
        for(int col = 0; col < MAX_COLS; col++)
        {
            const Room& room = grid[floor][col];

            if(!room.active)
                continue;

            QSet<int> nextSet;

            for(int next : room.nextCols)
            {
                if(nextSet.contains(next))
                    return false;

                nextSet.insert(next);
            }

            QSet<int> parentSet;

            for(int parent : room.parentCols)
            {
                if(parentSet.contains(parent))
                    return false;

                parentSet.insert(parent);
            }
        }
    }

    return true;
}

bool Map::validateReachability() const
{
    QSet<QPair<int,int>> visited;
    QQueue<QPair<int,int>> queue;

    for(int col = 0; col < MAX_COLS; col++)
    {
        if(grid[0][col].active)
        {
            queue.enqueue({0,col});
            visited.insert({0,col});
        }
    }

    while(!queue.isEmpty())
    {
        auto current = queue.dequeue();

        int floor = current.first;
        int col = current.second;

        const Room& room = grid[floor][col];

        for(int nextCol : room.nextCols)
        {
            QPair<int,int> next(floor + 1,nextCol);

            if(!visited.contains(next))
            {
                visited.insert(next);
                queue.enqueue(next);
            }
        }
    }

    for(int floor = 0; floor < TOTAL_FLOORS; floor++)
    {
        for(int col = 0; col < MAX_COLS; col++)
        {
            if(grid[floor][col].active)
            {
                if(!visited.contains({floor,col}))
                    return false;
            }
        }
    }

    return true;
}

bool Map::validateCoordinates() const
{
    for(int floor = 0; floor < TOTAL_FLOORS; floor++)
    {
        for(int col = 0; col < MAX_COLS; col++)
        {
            const Room& room = grid[floor][col];

            if(room.floor != floor)
                return false;

            if(room.col != col)
                return false;
        }
    }

    return true;
}

bool Map::validateCrossings() const
{
    for(int floor = 0; floor < TOTAL_FLOORS - 1; floor++)
    {
        for(int col = 0; col < MAX_COLS; col++)
        {
            const Room& room = grid[floor][col];

            if(!room.active)
                continue;

            for(int nextCol : room.nextCols)
            {
                if(causesCrossing(floor, col, nextCol))
                    return false;
            }
        }
    }

    return true;
}

bool Map::validateMap() const
{
    if (!validateBoss())
    {
        return false;
    }

    if (!validateTreasure())
    {
        return false;
    }

    if (!validateRest())
    {
        return false;
    }

    if (!validateConnections())
    {
        return false;
    }

    if (!validateCrossings())
    {
        return false;
    }

    if (!validateReachability())
    {
        return false;
    }

    if (!validateCoordinates())
    {
        return false;
    }

    if (!validateDuplicates())
    {
        return false;
    }

    return true;
}

int Map::getActiveRoomsCountInFloor(int floor) const {
    if (floor < 0 || floor >= TOTAL_FLOORS) {
        return 0;
    }
    int activeCount = 0;
    for (int col = 0; col < MAX_COLS; ++col) {
        if (grid[floor][col].active) {
            activeCount++;
        }
    }
    return activeCount;
}

bool Map::hasValidFloorLayout(int level) const
{
    int count2 = 0;
    int count3 = 0;
    int count5 = 0;
    int count6 = 0;

    for (int floor = 0; floor < TOTAL_FLOORS - 1; floor++)
    {
        switch (getActiveRoomsCountInFloor(floor))
        {
        case 2: count2++; break;
        case 3: count3++; break;
        case 5: count5++; break;
        case 6: count6++; break;
        default: break;
        }
    }

    switch(level)
    {

    case 0:

        if (count3 + count5 < 6)
            return false;

        if (count2 + count6 < 1)
            return false;


        if (count2 > 1)
            return false;

        if (count6 > 1)
            return false;

        return true;

    case 1:

        if (count3 + count5 < 5)
            return false;

        return true;

    case 2:

        if (count3 + count5 < 3)
            return false;

        return true;

    default:
        return true;
    }
}

void Map::generate()
{


    for (int i = 0; i < 200; i++)
    {
        qDebug() << "Attempt" << i << "(Ideal)";

        qDebug() << "init";
        initGrid();

        qDebug() << "paths";
        generatePaths();

        qDebug() << "boss";
        mergeBossRoom();

        qDebug() << "orphan";
        removeOrphanNodes();

        qDebug() << "assign";
        assignRoomTypes();

        qDebug() << "elite";
        minimumElite();

        qDebug() << "validate";
        bool valid = validateMap();

        qDebug() << "layout";
        bool layout = hasValidFloorLayout(0);

        if (valid && layout)
        {
            qDebug() << "Generated Ideal Map";
            return;
        }
    }


    for (int i = 0; i < 150; i++)
    {
        qDebug() << "Attempt" << i << "(Good)";

        initGrid();
        generatePaths();
        mergeBossRoom();
        removeOrphanNodes();
        assignRoomTypes();
        minimumElite();

        bool valid = validateMap();
        bool layout = hasValidFloorLayout(1);

        if (valid && layout)
        {
            qDebug() << "Generated Good Map";
            return;
        }
    }


    for (int i = 0; i < 100; i++)
    {
        qDebug() << "Attempt" << i << "(Acceptable)";

        initGrid();
        generatePaths();
        mergeBossRoom();
        removeOrphanNodes();
        assignRoomTypes();
        minimumElite();

        bool valid = validateMap();
        bool layout = hasValidFloorLayout(2);

        if (valid && layout)
        {
            qDebug() << "Generated Acceptable Map";
            return;
        }
    }


    for (int i = 0; i < 100; i++)
    {
        qDebug() << "Attempt" << i << "(Fallback)";

        initGrid();
        generatePaths();
        mergeBossRoom();
        removeOrphanNodes();
        assignRoomTypes();
        minimumElite();

        if (validateMap())
        {
            qDebug() << "Generated Fallback Map";
            return;
        }
    }

    throw std::runtime_error("Generated map is invalid.");
}

//---------------------------------------------------------
//by Ai:
QString Map::debugMap() const
{
    QString out;

    out += "\n=============== MAP DEBUG ===============\n\n";

    for (int floor = TOTAL_FLOORS - 1; floor >= 0; floor--)
    {
        out += QString("F%1  ").arg(floor, 2);

        //-------------------------------------------------
        // Rooms
        //-------------------------------------------------

        for (int col = 0; col < MAX_COLS; col++)
        {
            const Room& room = grid[floor][col];

            if (!room.active)
            {
                out += " . ";
                continue;
            }

            switch(room.type)
            {
            case RoomType::MONSTER:  out += " M "; break;
            case RoomType::ELITE:    out += " E "; break;
            case RoomType::REST:     out += " R "; break;
            case RoomType::MERCHANT: out += " $ "; break;
            case RoomType::TREASURE: out += " T "; break;
            case RoomType::UNKNOWN:  out += " ? "; break;
            case RoomType::BOSS:     out += " B "; break;
            }
        }

        out += "\n";

        //-------------------------------------------------
        // Connections
        //-------------------------------------------------

        if (floor == 0)
            continue;

        out += "    ";

        for (int col = 0; col < MAX_COLS; col++)
        {
            const Room& room = grid[floor][col];

            if (!room.active)
            {
                out += "   ";
                continue;
            }

            QString s;

            for (int parent : room.parentCols)
            {
                if (parent == col)
                    s += "|";

                else if (parent < col)
                    s += "/";

                else
                    s += "\\";
            }

            if (s.isEmpty())
                s = " ";

            while (s.size() < 3)
                s += " ";

            out += s.left(3);
        }

        out += "\n";
    }

    out += "\n=========================================\n";

    return out;
}