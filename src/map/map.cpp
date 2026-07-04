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