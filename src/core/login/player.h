#ifndef PLAYER_H
#define PLAYER_H

#include <QString>
#include "Stats.h"

class Player
{
public:
    Player(QString username = "", QString email = "", QString password = "");
    QString getUsername() const;
    QString getEmail() const;
    Stats& getStats();

private:
    QString username;
    QString email;
    QString passwordHash;
    Stats stats;
};

#endif
