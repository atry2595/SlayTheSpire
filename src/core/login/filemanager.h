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

};

#endif