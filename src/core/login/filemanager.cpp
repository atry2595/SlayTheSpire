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

bool FileManager::isUsernameTaken(const QString &username)
{
    for(const Player &p: players)
    {
        if(p.getUsername().toLower() == username.toLower())
        {
            return true;
        }
    }
    return false;
}

bool FileManager::isEmailTaken(const QString &email)
{
    for(const Player &p: players)
    {
        if(p.getEmail().toLower() == email.toLower())
        {
            return true;
        }
    }
    return false;
}

bool FileManager::registerPlayer(const QString &username,const QString &email,const QString &password,const QString &confirmPassword,QString &errorMessage)
{
    if(isUsernameTaken(username))
    {
        errorMessage ="Username already exists.";
        return false;
    }

    if(isEmailTaken(email))
    {
        errorMessage = "Email already exists.";
        return false;
    }

    if(!Player::isValidEmail(email))
    {
        errorMessage ="Invalid email.";
        return false;
    }

    if(!Player::passwordsMatch(password,confirmPassword))
    {
        errorMessage ="Passwords do not match.";
        return false;
    }

    QString passwordError = Player::validatePassword(password);

    if(!passwordError.isEmpty())
    {
        errorMessage =passwordError;
        return false;
    }

    Player newPlayer(generateId(),username,email,password);

    players.append(newPlayer);

    saveToFile();

    errorMessage = "";

    return true;
}

Player* FileManager::login(const QString &username,const QString &password)
{
    for(int i = 0;i < players.size();i++)
    {
        if(players[i].getUsername().toLower() == username.toLower())
        {
            if(players[i].checkPassword(password))
            {
                loggedInPlayerIndex = i;
                return &players[i];
            }
            return nullptr;
        }
    }
    return nullptr;
}

Player* FileManager::getLoggedInPlayer()
{
    if(loggedInPlayerIndex >= 0 && loggedInPlayerIndex < players.size())
    {
        return &players[loggedInPlayerIndex];
    }
    return nullptr;
}

bool FileManager::resetPassword(const QString &username,const QString &email,const QString &newPassword,const QString &confirmPassword)
{
    if(!Player::passwordsMatch(newPassword,confirmPassword))
    {
        return false;
    }

    QString passwordError = Player::validatePassword(newPassword);

    if(!passwordError.isEmpty())
    {
        return false;
    }

    for(Player &p : players)
    {
        if(p.getUsername().toLower() == username.toLower() && p.getEmail().toLower()==email.toLower())
        {
            p.setPassword(newPassword);

            saveToFile();

            return true;
        }
    }

    return false;
}

Player* FileManager::findPlayer(const QString &username)
{
    for(Player &p : players)
    {
        if(p.getUsername().toLower()==username.toLower())
        {
            return &p;
        }
    }

    return nullptr;
}

QList<Player>& FileManager::getPlayers()
{
    return players;
}