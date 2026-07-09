#include "Player.h"
#include <QCryptographicHash>
#include <QRandomGenerator>

Player::Player(int id, QString username, QString email, QString password):id(id), username(username), email(email)
{
    passwordHash = "";
    if (!password.isEmpty()) {
        this->passwordHash = hashPassword(password);
    }

}

QString Player::getUsername() const { return username; }
QString Player::getEmail() const { return email; }
Stats& Player::getStats() { return stats; }
const Stats& Player::getStats() const { return stats; }
int Player::getId() const {return id;}

QString Player::validatePassword(const QString &password)
{
    bool hasUpperCase = false;
    bool hasDigit = false;
    bool allDigits = true;

    if(password.length() < 6)
    {
        return "Password must be at least 6 characters long.";
    }

    QStringList commonPasswords =
        {
            "123456",
            "12345678",
            "123456789",
            "password",
            "Password",
            "qwerty",
            "111111",
            "000000"
        };

    if(commonPasswords.contains(password))
    {
        return "This password is too common.";
    }

    for(QChar c : password)
    {
        if(c.isUpper())
        {
            hasUpperCase = true;
        }

        if(c.isDigit())
        {
            hasDigit = true;
        }

        if(!c.isDigit())
        {
            allDigits = false;
        }
    }

    if(allDigits)
    {
        return "Password cannot contain only digits.";
    }

    if(!hasUpperCase)
    {
        return "Password must contain at least one uppercase letter.";
    }

    if(!hasDigit)
    {
        return "Password must contain at least one digit.";
    }

    return "";
}

QString Player::hashPassword(const QString &pass) {
    return QString(QCryptographicHash::hash(pass.toUtf8(), QCryptographicHash::Sha256).toHex());
}

bool Player::checkPassword(const QString &pass) const {
    return (hashPassword(pass) == passwordHash);
}

void Player::setPassword(const QString &newPass)
{
    passwordHash = hashPassword(newPass);}

bool Player::changePassword(const QString &oldPassword,const QString &newPassword,const QString &confirmPassword)
{
    if (!checkPassword(oldPassword))
    {
        return false;
    }

    if (newPassword != confirmPassword)
    {
        return false;
    }
    if(!validatePassword(newPassword).isEmpty())
    {
        return false;
    }

    passwordHash = hashPassword(newPassword);
    return true;
}

bool Player::isUsernameUnique(const QString &username,const QList<Player> &players)
{
    for(const Player &p : players)
    {
        if(p.username == username)
            return false;
    }

    return true;
}

bool Player::isEmailUnique(const QString &email,const QList<Player> &players)
{
    for(const Player &p : players)
    {
        if(p.email == email)
            return false;
    }

    return true;
}

bool Player::isValidEmail(const QString &email)
{
    int at = email.indexOf('@');

    if(at == -1)
        return false;

    if(email.indexOf('@', at + 1) != -1)
        return false;

    int dot = email.lastIndexOf('.');

    if(dot == -1)
        return false;

    if(dot < at)
        return false;

    if(dot == email.length() - 1)
        return false;

    return true;
}

bool Player::passwordsMatch(const QString &pass1,const QString &pass2)
{
    return pass1 == pass2;
}

bool Player::login(const QString &username,const QString &password,const QList<Player> &players)
{
    for(const Player &p : players)
    {
        if(p.username == username)
        {
            return p.checkPassword(password);
        }
    }
    return false;
}

bool Player::verifyUser(const QString &username,const QString &email,const QList<Player> &players)
{
    for(const Player &p : players)
    {
        if(p.username == username
            && p.email == email)
        {
            return true;
        }
    }
    return false;
}

QStringList Player::suggestUsername(const QString &username,const QList<Player> &players)
{
    QStringList suggestions;

    QStringList suffixes =
        {
            "Gaming",
            "Pro",
            "X",
            "A",
            "Nova",
            "King",
            "Player",
            "Master"
        };

    while(suggestions.size() < 5)
    {
        QString suggestion;

        int mode =QRandomGenerator::global()->bounded(3);

        if(mode == 0)
        {
            QString suffix =suffixes[QRandomGenerator::global()->bounded(suffixes.size())];

            suggestion = username + suffix;
        }
        else if(mode == 1)
        {
            int number =QRandomGenerator::global()->bounded(1000);

            suggestion =username + "_" +QString::number(number);
        }
        else
        {
            QString suffix =suffixes[QRandomGenerator::global()->bounded(suffixes.size())];

            int number =QRandomGenerator::global()->bounded(100);

            suggestion =username + suffix +QString::number(number);
        }

        if(isUsernameUnique(suggestion, players)&& !suggestions.contains(suggestion))
        {
            suggestions.append(suggestion);
        }
    }

    return suggestions;
}

bool Player::registerPlayer(const QString &username,const QString &email,const QString &password,const QString &confirmPassword,const QList<Player> &players)
{
    if(!isUsernameUnique(username, players))
        return false;

    if(!isEmailUnique(email, players))
        return false;

    if(!isValidEmail(email))
        return false;

    if(password != confirmPassword)
        return false;

    return true;
}

QString Player::getProfile() const
{
    QString result;

    result += QString("Player ID: %1\n").arg(id);
    result += QString("Username: %1\n").arg(username);
    result += QString("Email: %1\n\n").arg(email);

    result += QString("Score: %1\n").arg(stats.getScore());

    result += QString("Highest Score: %1\n").arg(stats.getHighestScore());

    result += QString("Monsters Killed: %1\n").arg(stats.getMonstersKilled());

    result += QString("Elites Killed: %1\n").arg(stats.getElitesKilled());

    result += QString("Bosses Killed: %1\n").arg(stats.getBossesKilled());

    result += QString("Total Enemies Killed: %1\n").arg(stats.getTotalEnemiesKilled());

    result += QString("Highest Floor Reached: %1\n").arg(stats.getHighestFloorReached());

    result += QString("Times Played: %1\n").arg(stats.getTimesPlayed());

    result += QString("Wins: %1\n").arg(stats.getTimesWon());

    result += QString("Losses: %1\n").arg(stats.getTimesLost());

    result += "\n";

    return result;
}

QString Player::toFileRecord() const {
    return QString::number(id) + ";" + username + ";" + email + ";" + passwordHash + ";" + stats.toFileRecord();
}

Player Player::fromFileRecord(const QString &record) {
    QStringList fields = record.split(";");

    if (fields.size() < 4){
        return Player();}

    Player p;
    p.id = fields[0].toInt();
    p.username = fields[1];
    p.email = fields[2];
    p.passwordHash = fields[3];

    QStringList statsFields = fields.mid(4);
    QString statsRecord = statsFields.join(";");
    p.stats = Stats::fromFileRecord(statsRecord);

    return p;
}
