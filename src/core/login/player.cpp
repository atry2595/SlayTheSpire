#include "Player.h"
#include <QStringList>
#include <QCryptographicHash>

Player::Player(QString username, QString email, QString password): username(username), email(email)
{

}

QString Player::getUsername() const { return username; }
QString Player::getEmail() const { return email; }
Stats& Player::getStats() { return stats; }
