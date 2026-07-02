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

void Player::setPassword(const QString &newPass) {
    this->passwordHash = hashPassword(newPass);
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

bool Player::verifyUser(
    const QString &username,
    const QString &email,
    const QList<Player> &players)
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


