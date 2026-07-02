#include "Leaderboard.h"

#include <algorithm>

QList<Player> Leaderboard::getTopPlayers(const QList<Player> &players, int count)
{
    QList<Player> sortedPlayers = players;

    std::sort(sortedPlayers.begin(), sortedPlayers.end(),
              [](const Player &a, const Player &b)
              {
                  return a.getStats().getHighestScore() >
                         b.getStats().getHighestScore();
              });

    if(count > sortedPlayers.size())
    {
        count = sortedPlayers.size();
    }

    return sortedPlayers.mid(0, count);
}