#include "Player.h"
#include <QStringList>
#include <QCryptographicHash>

Player::Player(QString username, QString email, QString password): username(username), email(email)
{
    passwordHash = "";
    if (!password.isEmpty()) {
        this->passwordHash = hashPassword(password);
    }

}

QString Player::getUsername() const { return username; }
QString Player::getEmail() const { return email; }
Stats& Player::getStats() { return stats; }

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

QString Player::suggestUsername(const QString &username,const QList<Player> &players)
{
    QStringList suffixes =
        {
            "Gaming",
            "Pro",
            "X",
            "A",
            "King",
            "Player",
            "Master"
        };

    QString suggestion;

    do
    {
        int mode = QRandomGenerator::global()->bounded(3);

        if(mode == 0)
        {
            QString suffix =suffixes[QRandomGenerator::global()->bounded(suffixes.size())];

            suggestion = username + suffix;
        }
        else if(mode == 1)
        {
            int number = QRandomGenerator::global()->bounded(1000);

            suggestion =username + "_" +QString::number(number);
        }
        else
        {
            QString suffix =
                suffixes[
                    QRandomGenerator::global()->bounded(suffixes.size())];

            int number =QRandomGenerator::global()->bounded(100);

            suggestion =username + suffix +QString::number(number);
        }

    } while(!isUsernameUnique(suggestion, players));

    return suggestion;
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

QString Player::toFileRecord() const {
    return username + ";" + email + ";" + passwordHash + ";" + stats.toFileRecord();
}

Player Player::fromFileRecord(const QString &record) {
    QStringList fields = record.split(";");

    if (fields.size() < 4){
        return Player();}

    Player p;
    p.username = fields[0];
    p.email = fields[1];
    p.passwordHash = fields[2];

    QStringList statsFields = fields.mid(3);
    QString statsRecord = statsFields.join(";");
    p.stats = Stats::fromFileRecord(statsRecord);

    return p;
}
