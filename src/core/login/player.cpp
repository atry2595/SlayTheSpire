#include "Player.h"
#include <QStringList>
#include <QCryptographicHash>

Player::Player(QString username, QString email, QString password): username(username), email(email)
{
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

