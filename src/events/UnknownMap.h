#ifndef UNKNOWNMAP_H
#define UNKNOWNMAP_H

#include <QString>
#include "categories/unknowns.h"

struct UnknownNode {

    QString title;

    QString description;

    std::function<void()> actions;

    std::function<bool()> canUse;

    std::vector<int> next_nodes;

};

struct UnknownManager {

    unknownID unknown_ID;

    QString unknown_name;

    int current_node = 0;

    bool isEvent = true;

    std::vector<UnknownNode> nodes;
};

#endif // UNKNOWNMAP_H
