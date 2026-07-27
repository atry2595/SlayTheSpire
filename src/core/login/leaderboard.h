#ifndef LEADERBOARD_H
#define LEADERBOARD_H

#include <QList>
#include "player.h"

class Leaderboard
{
public:
    static QList<Player> getTopPlayers(const QList<Player> &players,int count);

    static int getPlayerRank(const QString &username,const QList<Player> &players);

    static QString getLeaderboardText(const QList<Player> &players,int count);
};

#endif