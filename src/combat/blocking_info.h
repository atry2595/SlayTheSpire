#ifndef BLOCKING_INFO_H
#define BLOCKING_INFO_H

class abstractEntity;

struct blockingInfo{
    abstractEntity* owner = nullptr;
    int block = 0;
};

#endif // BLOCKING_INFO_H
