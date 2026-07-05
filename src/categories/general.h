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

#endif // GENERAL_H
