#ifndef GENERAL_H
#define GENERAL_H

enum class TargetType {
    none,
    self,
    single_target,
    allies,
    enemies
};

enum class PileType{
    draw,
    hand,
    discard,
    exhaust,

    none //for powers cards
};


enum class CombatType{
    monster,
    elite,
    boss
};

enum class ChestType{
    regular,
    boss
};

enum class RoomType{
    MONSTER,
    ELITE,
    REST,
    MERCHANT,
    TREASURE,
    UNKNOWN,
    BOSS
};

#endif // GENERAL_H
