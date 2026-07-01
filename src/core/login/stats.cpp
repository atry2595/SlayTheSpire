#include "Stats.h"

Stats::Stats()
{
    score = 0;
    monstersKilled = 0;
    elitesKilled = 0;
    bossesKilled = 0;

    skinUnlocked[0] = true;
    for(int i = 1; i < 5; ++i) skinUnlocked[i] = false;

    highestFloorReached = 0;
    timesPlayed = 0;
    timesWon = 0;
    timesLost = 0;
}

int Stats::getScore() const { return score; }
int Stats::getMonstersKilled() const { return monstersKilled; }
int Stats::getElitesKilled() const { return elitesKilled; }
int Stats::getBossesKilled() const { return bossesKilled; }
int Stats::getTotalEnemiesKilled() const { return monstersKilled + elitesKilled + bossesKilled; }
int Stats::getHighestFloorReached() const { return highestFloorReached; }
int Stats::getTimesPlayed() const { return timesPlayed; }
int Stats::getTimesWon() const { return timesWon; }
int Stats::getTimesLost() const { return timesLost; }

bool Stats::isSkinUnlocked(int skinIndex) const {
    if(skinIndex >= 0 && skinIndex < 5) return skinUnlocked[skinIndex];
    return false;
}

void Stats::addScore(int amount) { score += amount; }
void Stats::addMonsterKill() { monstersKilled++; }
void Stats::addEliteKill() { elitesKilled++; }
void Stats::addBossKill() { bossesKilled++; }

void Stats::updateHighestFloor(int floor) {
    if(floor > highestFloorReached) highestFloorReached = floor;
}

void Stats::incrementTimesPlayed() { timesPlayed++; }
void Stats::incrementTimesWon() { timesWon++; }
void Stats::incrementTimesLost() { timesLost++; }

void Stats::unlockSkin(int skinIndex) {
    if(skinIndex >= 0 && skinIndex < 5) skinUnlocked[skinIndex] = true;
}

QString Stats::toFileRecord() const {
    QStringList fields;
    fields << QString::number(score)
           << QString::number(monstersKilled)
           << QString::number(elitesKilled)
           << QString::number(bossesKilled);

    for(int i = 0; i < 5; ++i) {
        fields << (skinUnlocked[i] ? "1" : "0");
    }

    fields << QString::number(highestFloorReached)
           << QString::number(timesPlayed)
           << QString::number(timesWon)
           << QString::number(timesLost);

    return fields.join(";");
}

Stats Stats::fromFileRecord(const QString &record) {
    Stats s;
    QStringList fields = record.split(";");

    if (fields.size() >= 13) {
        s.score = fields[0].toInt();
        s.monstersKilled = fields[1].toInt();
        s.elitesKilled = fields[2].toInt();
        s.bossesKilled = fields[3].toInt();

        for(int i = 0; i < 5; ++i) {
            s.skinUnlocked[i] = (fields[4 + i] == "1");
        }

        s.highestFloorReached = fields[9].toInt();
        s.timesPlayed = fields[10].toInt();
        s.timesWon = fields[11].toInt();
        s.timesLost = fields[12].toInt();
    }
    return s;
}
