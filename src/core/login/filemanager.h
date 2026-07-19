#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <QString>
#include <QList>

#include "Player.h"

class FileManager
{
private:
    QList<Player> players;
    int nextId;
    int loggedInPlayerIndex;
    int generateId();

public:
    FileManager();
    bool loadFromFile(const QString &filePath = "players_data.txt");
    bool saveToFile(const QString &filePath ="players_data.txt");
    bool isUsernameTaken(const QString &username);
    bool isEmailTaken(const QString &email);
    bool registerPlayer(const QString &username,const QString &email,const QString &password,const QString &confirmPassword,QString &errorMessage);
    Player* login(const QString &username,const QString &password);
    Player* getLoggedInPlayer();
    bool resetPassword(const QString &email,const QString &newPassword,const QString &confirmPassword,QString &errorMessage);
    Player* findPlayer(const QString &username);
    QList<Player>& getPlayers();
    QStringList getUsernameSuggestions(const QString &username);
};

#endif