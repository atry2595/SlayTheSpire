#ifndef MAP_H
#define MAP_H

#include "Map.h"

Map::Map()
{
    grid.resize(TOTAL_FLOORS);
    colsPerFloor.resize(TOTAL_FLOORS);
}
