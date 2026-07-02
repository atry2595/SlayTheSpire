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
    bool changePassword(const QString &oldPassword,const QString &newPassword,const QString &confirmPassword);
    static bool isUsernameUnique(const QString &username,const QList<Player> &players);
    static bool isEmailUnique(const QString &email,const QList<Player> &players);
    static bool isValidEmail(const QString &email);
    static bool passwordsMatch(const QString &pass1,const QString &pass2);
    static bool login(const QString &username,const QString &password,const QList<Player> &players);
    static bool verifyUser(const QString &username,const QString &email,const QList<Player> &players);
    static QString suggestUsername(const QString &username,const QList<Player> &players);
    static bool registerPlayer(const QString &username,const QString &email,const QString &password,const QString &confirmPassword,const QList<Player> &players);
    QString getProfile() const;

    QString toFileRecord() const;
    static Player fromFileRecord(const QString &record);


};

#endif
