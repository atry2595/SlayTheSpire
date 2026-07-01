#ifndef PLAYER_H
#define PLAYER_H

#include <QString>
#include "Stats.h"

class Player
{
private:
    QString username;
    QString email;
    QString passwordHash;
    Stats stats;
    static QString hashPassword(const QString &pass);

public:
    Player(QString username = "", QString email = "", QString password = "");
    QString getUsername() const;
    QString getEmail() const;
    Stats& getStats();
    bool checkPassword(const QString &pass) const;
    void setPassword(const QString &newPass);
    QString toFileRecord() const;
    static Player fromFileRecord(const QString &record);


};

#endif
