#include "Stats.h"

Stats::Stats()
{
    score = 0;
    highestScore = 0;
    monstersKilled = 0;
    elitesKilled = 0;
    bossesKilled = 0;

    skinUnlocked[0] = true;
    for(int i = 1; i < SKIN_COUNT; ++i)
        skinUnlocked[i] = false;

    highestFloorReached = 0;
    timesPlayed = 0;
    timesWon = 0;
    timesLost = 0;
}

int Stats::getScore() const { return score; }
int Stats::getMonstersKilled() const { return monstersKilled; }
int Stats::getElitesKilled() const { return elitesKilled; }
int Stats::getBossesKilled() const { return bossesKilled; }
int Stats::getTotalEnemiesKilled() const {
    return monstersKilled + elitesKilled + bossesKilled; }
int Stats::getHighestFloorReached() const { return highestFloorReached; }
int Stats::getTimesPlayed() const { return timesPlayed; }
int Stats::getTimesWon() const { return timesWon; }
int Stats::getTimesLost() const { return timesLost; }
double Stats::getWinRate() const{
    if(timesPlayed == 0)
        return 0.0;

    return (100.0 * timesWon) / timesPlayed;
}
bool Stats::isSkinUnlocked(int skinIndex) const {
    if(skinIndex >= 0 && skinIndex < SKIN_COUNT) return skinUnlocked[skinIndex];
    return false;
}

void Stats::addScore(int amount) {
    score += amount;
    if(score > highestScore)
        highestScore = score;
}
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
    if(skinIndex >= 0 && skinIndex < SKIN_COUNT) skinUnlocked[skinIndex] = true;
}

void Stats::update(const Stats &other)
{
    score += other.score;
    monstersKilled += other.monstersKilled;
    elitesKilled += other.elitesKilled;
    bossesKilled += other.bossesKilled;
    timesPlayed += other.timesPlayed;
    timesWon += other.timesWon;
    timesLost += other.timesLost;

    if (other.highestFloorReached > highestFloorReached)
    {
        highestFloorReached = other.highestFloorReached;
    }

    if (other.highestScore > highestScore)
    {
        highestScore = other.highestScore;
    }
    for (int i = 0; i < SKIN_COUNT; ++i)
    {
        skinUnlocked[i] = skinUnlocked[i] || other.skinUnlocked[i];
    }
}

QString Stats::toFileRecord() const
{
    QStringList fields;

    fields << QString::number(score)
           << QString::number(highestScore)
           << QString::number(monstersKilled)
           << QString::number(elitesKilled)
           << QString::number(bossesKilled);

    for(int i = 0; i < SKIN_COUNT; ++i)
    {
        fields << (skinUnlocked[i] ? "1" : "0");
    }

    fields << QString::number(highestFloorReached)
           << QString::number(timesPlayed)
           << QString::number(timesWon)
           << QString::number(timesLost);

    return fields.join(";");
}

Stats Stats::fromFileRecord(const QString &record)
{
    Stats s;

    QStringList fields = record.split(";");

    if(fields.size() >= 14){
        s.score = fields[0].toInt();
        s.highestScore = fields[1].toInt();
        s.monstersKilled = fields[2].toInt();
        s.elitesKilled = fields[3].toInt();
        s.bossesKilled = fields[4].toInt();

        for(int i = 0; i < SKIN_COUNT; ++i)
        {
            s.skinUnlocked[i] = (fields[5 + i] == "1");
        }

        s.highestFloorReached = fields[10].toInt();
        s.timesPlayed = fields[11].toInt();
        s.timesWon = fields[12].toInt();
        s.timesLost = fields[13].toInt();
    }

    return s;
}