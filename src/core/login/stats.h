#ifndef STATS_H
#define STATS_H

#include <QString>
#include <QStringList>

class Stats
{
public:
    Stats();

    int getScore() const;
    int getMonstersKilled() const;
    int getElitesKilled() const;
    int getBossesKilled() const;
    int getTotalEnemiesKilled() const;
    int getHighestFloorReached() const;
    int getTimesPlayed() const;
    int getTimesWon() const;
    int getTimesLost() const;
    // skinIndex: 0-based (0=skin1, 1=skin2, 2=skin3, 3=skin4, 4=skin5)
    bool isSkinUnlocked(int skinIndex) const;

    void addScore(int amount);
    void addMonsterKill();
    void addEliteKill();
    void addBossKill();
    void updateHighestFloor(int floor);
    void incrementTimesPlayed();
    void incrementTimesWon();
    void incrementTimesLost();
    void unlockSkin(int skinIndex);

    QString toFileRecord() const;
    static Stats fromFileRecord(const QString &record);

private:
    int score;
    int monstersKilled;
    int elitesKilled;
    int bossesKilled;

    bool skinUnlocked[5];

    int highestFloorReached;
    int timesPlayed;
    int timesWon;
    int timesLost;
};

#endif
