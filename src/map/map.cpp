#ifndef MAP_H
#define MAP_H

#include "Map.h"

Map::Map()
{
    grid.resize(TOTAL_FLOORS);

    for(int floor = 0;floor < TOTAL_FLOORS ; ++floor)
    {
        grid[floor].resize(MAX_COLS);
    }
}

bool Map::causesCrossing(
    int floor,
    int fromCol,
    int toCol) const
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
            if(col < fromCol && next > toCol)
            {
                return true;
            }
            if(col > fromCol && next < toCol)
            {
                return true;
            }
        }
    }

    return false;
}

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

void Map::generatePaths()
{
    for(int floor = 0;floor < TOTAL_FLOORS;++floor)
    {
        for(int col = 0;col < MAX_COLS;++col)
        {
            grid[floor][col].active = false;
            grid[floor][col].nextCols.clear();
        }
    }

    for(int i = 0; i < 6; ++i)
    {
        int startCol =RNG::instance().randint(0, MAX_COLS - 1);

        generateSinglePath(startCol);
    }
}

void Map::generateSinglePath(int startColumn)
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
        currentCol = nextCol;
    }

    //Boss
    grid[TOTAL_FLOORS - 1][currentCol].active = true;
}

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