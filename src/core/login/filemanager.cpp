#include "filemanager.h"
#include <QFile>
#include <QTextStream>
#include <QDataStream>

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

    if(!file.open(QIODevice::ReadOnly))
    {
        nextId = 1001;
        return false;
    }

    QDataStream in(&file);
    in.setVersion(QDataStream::Qt_6_11);

    int maxId = 1000;

    while(!in.atEnd())
    {
        Player p;
        in >> p;

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

    if(!file.open(QIODevice::WriteOnly))
    {
        return false;
    }

    QDataStream out(&file);
    out.setVersion(QDataStream::Qt_6_11);

    for(const Player &p : players)
    {
        out << p;
    }

    file.close();

    return true;
}

bool FileManager::isUsernameTaken(const QString &username)
{
    for(const Player &p: players)
    {
        if(p.getUsername() == username)
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
        if(p.getEmail() == email)
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

    QString passwordError = Player::validatePassword(password);

    if(!passwordError.isEmpty())
    {
        errorMessage =passwordError;
        return false;
    }


    if(!Player::passwordsMatch(password,confirmPassword))
    {
        errorMessage ="Passwords do not match.";
        return false;
    }

    Player newPlayer(generateId(),username,email,password);

    players.append(newPlayer);

    saveToFile();

    errorMessage = "";

    return true;
}

Player* FileManager::login(const QString &username, const QString &password)
{
    for (int i = 0; i < players.size(); i++)
    {
        if (players[i].getUsername() == username ||
            players[i].getEmail() == username)
        {
            if (players[i].checkPassword(password))
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

bool FileManager::resetPassword(const QString &email,
                                const QString &newPassword,
                                const QString &confirmPassword,
                                QString &errorMessage)
{
    Player *foundPlayer = nullptr;

    for(Player &player : players)
    {
        if(player.getEmail() == email)
        {
            foundPlayer = &player;
            break;
        }
    }

    if(foundPlayer == nullptr)
    {
        errorMessage = "Email not found.";
        return false;
    }

    QString passwordError = Player::validatePassword(newPassword);

    if(!passwordError.isEmpty())
    {
        errorMessage = passwordError;
        return false;
    }

    if(newPassword != confirmPassword)
    {
        errorMessage = "Passwords do not match.";
        return false;
    }

    foundPlayer->setPassword(newPassword);

    saveToFile();

    errorMessage = "";

    return true;
}

Player* FileManager::findPlayer(const QString &username)
{
    for(Player &p : players)
    {
        if(p.getUsername()==username)
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
QStringList FileManager::getUsernameSuggestions(const QString &username)
{
    return Player::suggestUsername(username, players);
}
