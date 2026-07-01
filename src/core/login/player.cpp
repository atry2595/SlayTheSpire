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


