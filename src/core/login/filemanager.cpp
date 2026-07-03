#include "FileManager.h"
#include <QFile>
#include <QTextStream>

FileManager::FileManager()
{
    nextId = 1001;
    loggedInPlayerIndex = -1;
    loadFromFile();
}

int FileManager::generateId()
{
    return nextId++;
}

bool FileManager::loadFromFile(const QString &filePath)
{
    QFile file(filePath);

    players.clear();

    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        nextId = 1001;
        return false;
    }

    QTextStream in(&file);

    int maxId = 1000;

    while(!in.atEnd())
    {
        QString line = in.readLine().trimmed();

        if(line.isEmpty())
        {
            continue;
        }

        Player p =Player::fromFileRecord(line);

        players.append(p);

        if(p.getId() > maxId)
        {
            maxId = p.getId();
        }
    }

    nextId = maxId + 1;

    file.close();

    return true;
}

bool FileManager::saveToFile(const QString &filePath)
{
    QFile file(filePath);

    if(!file.open(QIODevice::WriteOnly |QIODevice::Text))
    {
        return false;
    }

    QTextStream out(&file);

    for(const Player &p : players)
    {
        out << p.toFileRecord() << "\n";
    }

    file.close();

    return true;
}