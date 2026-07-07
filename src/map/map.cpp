
#include "Map.h"

Map::Map()
{
    grid.resize(TOTAL_FLOORS);

    for(int floor = 0;floor < TOTAL_FLOORS ; ++floor)
    {
        grid[floor].resize(MAX_COLS);
    }
}

const Room& Map::getRoom(int floor, int col) const
{
    return grid[floor - 1][col];
}

QList<Room> Map::getNextRooms(int floor, int col) const
{
    QList<Room> result;

    if(floor >= TOTAL_FLOORS)
        return result;

    const Room& current =getRoom(floor,col);

    for(int nextCol : current.nextCols)
        result.append(grid[floor][nextCol]);

    return result;
}

void Map::markVisited(int floor, int col)
{
    grid[floor - 1][col].visited = true;
}

QList<Room> Map::getRoomsOnFloor(int floor) const
{
    QList<Room> rooms;
    for(int col = 0; col < MAX_COLS; ++col)
    {
        if(grid[floor - 1][col].active)
            rooms.append(grid[floor - 1][col]);
    }
    return rooms;
}

bool Map::causesCrossing(int floor, int from, int to) const
{
    for(int col = 0;
         col < MAX_COLS;
         ++col)
    {
        const Room& room =
            grid[floor][col];

        if(!room.active)
            continue;

        for(int next : room.nextCols)
        {
            if(col < from && next > to)
            {
                return true;
            }
            if(col > from && next < to)
            {
                return true;
            }
        }
    }

    return false;
}

/*QVector<int> Map::generateStartingColumns()
{
    QVector<int> starts;

    while(starts.size() < 6)
    {
        int col =RNG::instance().randint(0,MAX_COLS - 1);

        if(!starts.contains(col))
        {
            starts.append(col);
        }
    }

    return starts;
} */

void Map::initGrid()
{
    for(int floor = 0; floor < TOTAL_FLOORS; ++floor)
    {
        for(int col = 0; col < MAX_COLS; ++col)
        {
            Room& room = grid[floor][col];

            room.type = RoomType::MONSTER;
            room.floor = floor + 1;
            room.col = col;
            room.visited = false;
            room.active = false;
            room.nextCols.clear();
        }
    }
}

void Map::buildPath(int startColumn)
{
    int currentCol = startColumn;

    for (int floor = 0; floor < TOTAL_FLOORS - 1; floor++)
    {
        Room& current = grid[floor][currentCol];

        current.active = true;

        int nextCol = chooseNextColumn(floor, currentCol);

        if (!current.nextCols.contains(nextCol))
            current.nextCols.append(nextCol);

        currentCol = nextCol;
    }

    grid[TOTAL_FLOORS - 1][currentCol].active = true;
}

void Map::generatePaths()
{
    int first =RNG::instance().randint(0, MAX_COLS - 1);

    int second;

    do
    {
        second =RNG::instance().randint(0, MAX_COLS - 1);
    }
    while (second == first);

    buildPath(first);

    buildPath(second);

    for (int i = 0; i < 4; i++)
    {
        buildPath(RNG::instance().randint(0, MAX_COLS - 1));
    }
    /*   for(int floor = 0;floor < TOTAL_FLOORS-1;++floor)
    {
        for(int col = 0;col < MAX_COLS;++col)
        {
            grid[floor][col].active = false;
            grid[floor][col].nextCols.clear();
        }
    }

    QVector<int> starts = generateStartingColumns();

    for(int start : starts)
    {
        generateSinglePath(start);
    }*/
}

/*void Map::generateSinglePath(int startColumn)
{
    int currentCol = startColumn;

    for(int floor = 0;floor < TOTAL_FLOORS - 1;++floor)
    {
        grid[floor][currentCol].active = true;

        int nextCol = currentCol;

        int tries = 0;

        do
        {
            int move =RNG::instance().randint(-1,1);

            nextCol =currentCol + move;

            if(nextCol < 0)
                nextCol = 0;

            if(nextCol >= MAX_COLS)
                nextCol = MAX_COLS - 1;

            tries++;

        }
        while(
            causesCrossing(floor,currentCol,nextCol) && tries < 20);

        if(nextCol < 0)
            nextCol = 0;

        if(nextCol >= MAX_COLS)
            nextCol = MAX_COLS - 1;

        if (!grid[floor][currentCol].nextCols.contains(nextCol)){
            grid[floor][currentCol].nextCols.append(nextCol);
        }
        grid[floor + 1][nextCol].active = true;

        currentCol = nextCol;
    }

    //Boss
    grid[TOTAL_FLOORS - 1][currentCol].active = true;
} */

/*void Map::mergeBossPaths()
{
    int bossCol = MAX_COLS / 2;

    for(int col = 0;col < MAX_COLS;++col)
    {
        grid[BOSS_FLOOR - 1][col].active =false;

        grid[BOSS_FLOOR - 1][col].nextCols.clear();
    }

    grid[BOSS_FLOOR - 1][bossCol].active = true;

    int previousFloor =BOSS_FLOOR - 2;

    for(int col = 0;col < MAX_COLS;++col)
    {
        Room& room = grid[previousFloor][col];

        if(!room.active)
            continue;

        room.nextCols.clear();

        room.nextCols.append(bossCol);
    }
}

void Map::mergeTreasurePaths()
{
    int treasureCol = MAX_COLS / 2;

    for (int col = 0; col < MAX_COLS; ++col)
    {
        grid[TREASURE_FLOOR - 1][col].active = false;
        grid[TREASURE_FLOOR - 1][col].nextCols.clear();
    }

    grid[TREASURE_FLOOR - 1][treasureCol].active = true;
    int prevFloor = TREASURE_FLOOR - 2;
    for (int col = 0; col < MAX_COLS; ++col)
    {
        Room& room = grid[prevFloor][col];

        if (!room.active)
            continue;

        room.nextCols.clear();
        room.nextCols.append(treasureCol);
    }
}

void Map::mergeRestPaths()
{
    int restCol = MAX_COLS / 2;

    for (int col = 0; col < MAX_COLS; ++col)
    {
        grid[REST_FLOOR - 1][col].active = false;
        grid[REST_FLOOR - 1][col].nextCols.clear();
    }

    grid[REST_FLOOR - 1][restCol].active = true;

    int prevFloor = REST_FLOOR - 2;

    for (int col = 0; col < MAX_COLS; ++col)
    {
        Room& room = grid[prevFloor][col];

        if (!room.active)
            continue;

        room.nextCols.clear();
        room.nextCols.append(restCol);
    }
} */

RoomType Map::randomRoomType()
{
    std::vector<RoomType> types ={
        RoomType::MONSTER, RoomType::UNKNOWN, RoomType::REST, RoomType::ELITE, RoomType::MERCHANT
        };

    std::vector<double> weights ={
        53.0,22.0,12.0,8.0,5.0
    };

    return RNG::instance().weighted_choice(types,weights);
}

void Map::assignRoomTypes()
{
    for(int floor = 0; floor < TOTAL_FLOORS; ++floor)
    {
        for(int col = 0;col < MAX_COLS;++col)
        {
            Room& room = grid[floor][col];

            if(!room.active)
                continue;

            RoomType selectedType;

            do
            {
                selectedType = randomRoomType();
            }
            while(!isRoomValid(floor,col,selectedType));

            room.type =selectedType;
        }
    }
}

bool Map::hasParentOfType(int floor,int col,RoomType type) const
{
    if(floor == 0)
        return false;

    for(int prev = 0;prev < MAX_COLS;++prev)
    {
        const Room& parent = grid[floor - 1][prev];

        if(!parent.active)
            continue;

        if(parent.type != type)
            continue;

        if(parent.nextCols.contains(col))
            return true;
    }

    return false;
}

bool Map::isRoomValid(int floor,int col,RoomType type) const
{
    if(floor == 0)
        return type == RoomType::MONSTER;

    if(type == RoomType::REST)
    {
        if(hasParentOfType(floor,col,RoomType::REST))
        {
            return false;
        }
    }

    if(type == RoomType::MERCHANT)
    {
        if(hasParentOfType(floor,col,RoomType::MERCHANT))
        {
            return false;
        }
    }

    if(type == RoomType::ELITE)
    {
        if(floor < 3)
            return false;

        if(floor + 1 == TREASURE_FLOOR)
            return false;

        if(floor == REST_FLOOR - 1)
            return false;

        if(floor + 1 == BOSS_FLOOR)
            return false;

        if(hasParentOfType(floor,col,RoomType::ELITE))
        {
            return false;
        }
    }


    return true;
}

void Map::applyFixedFloors()
{
    for(int col = 0;col < MAX_COLS;++col)
    {
        if(grid[TREASURE_FLOOR - 1][col].active)
        {
            grid[TREASURE_FLOOR - 1][col].type =RoomType::TREASURE;
        }
    }

    for(int col = 0;col < MAX_COLS;++col)
    {
        if(grid[REST_FLOOR - 1][col].active)
        {
            grid[REST_FLOOR - 1][col].type =RoomType::REST;
        }
    }

    for(int col = 0;col < MAX_COLS;++col)
    {
        if(grid[BOSS_FLOOR - 1][col].active)
        {
            grid[BOSS_FLOOR - 1][col].type =RoomType::BOSS;
        }
    }
}

void Map::generate()
{
    initGrid();
    generatePaths();
   // mergeTreasurePaths();
    //mergeRestPaths();
    //mergeBossPaths();
    removeIsolatedRooms();
    assignRoomTypes();
    applyFixedFloors();
}

QString Map::toDebugString() const
{
    QString result;

    for(int floor = TOTAL_FLOORS - 1;floor >= 0;--floor)
    {
        result += QString("Floor %1 : ")
        .arg(floor + 1,2);

        for(int col = 0;
             col < MAX_COLS;
             ++col)
        {
            const Room& room =
                grid[floor][col];

            if(!room.active)
            {
                result += " . ";
                continue;
            }

            switch(room.type)
            {
            case RoomType::MONSTER:
                result += " M ";
                break;

            case RoomType::ELITE:
                result += " E ";
                break;

            case RoomType::REST:
                result += " R ";
                break;

            case RoomType::MERCHANT:
                result += " $ ";
                break;

            case RoomType::TREASURE:
                result += " T ";
                break;

            case RoomType::UNKNOWN:
                result += " ? ";
                break;

            case RoomType::BOSS:
                result += " B ";
                break;
            }
        }

        result += "\n";
    }

    return result;
}
