#ifndef LEADERBOARD_H
#define LEADERBOARD_H

#include <QList>
#include "Player.h"

class Leaderboard
{
public:
    static QList<Player> getTopPlayers(QList<Player> players,int count);

    static int getPlayerRank(const QString &username,QList<Player> players);

    static QString getLeaderboardText(QList<Player> players,int count);
};

#endif