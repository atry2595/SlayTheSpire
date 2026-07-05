#ifndef BLOCKING_INFO_H
#define BLOCKING_INFO_H

class abstractEntity;

struct blockingInfo{
    abstractEntity* owner = nullptr;
    int block = 0;
    bool affected_by_other = true;
};

struct healInfo{
    abstractEntity* owner;
    int value = 0;
};

#endif // BLOCKING_INFO_H
