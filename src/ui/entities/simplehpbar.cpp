#include "simplehpbar.h"
#include <QPainter>
#include <QPainterPath>

SimpleHpBar::SimpleHpBar(QWidget *parent)
    : QWidget(parent)
    , m_hp(100)
    , m_maxHp(100)
    , m_shield(0)
    , m_displayPercent(1.0f)
{
    m_animation = new QPropertyAnimation(this, "displayPercent");
    m_animation->setDuration(300);
    m_animation->setEasingCurve(QEasingCurve::OutCubic);

    // سایز پیش‌فرض
    setFixedSize(200, 24);

    // شفاف برای QGraphicsItem
    setAttribute(Qt::WA_TranslucentBackground);
    setAttribute(Qt::WA_NoSystemBackground);
    setAutoFillBackground(false);
    setStyleSheet("background: transparent;");
}

void SimpleHpBar::setMaxHp(int maxHp)
{
    m_maxHp = maxHp > 0 ? maxHp : 1;
    if (m_hp > m_maxHp) {
        setHp(m_maxHp);
    }
}

void SimpleHpBar::setHp(int hp)
{
    int oldHp = m_hp;
    m_hp = qBound(0, hp, m_maxHp);

    float newPercent = (float)m_hp / m_maxHp;

    // اگر آسیب خورده
    if (m_hp < oldHp) {
        float oldPercent = (float)oldHp / m_maxHp;

        m_animation->stop();
        m_animation->setStartValue(oldPercent);
        m_animation->setEndValue(newPercent);
        m_animation->start();
    }
    // اگر شفا گرفته
    else {

        m_animation->stop();
        m_animation->setStartValue(m_displayPercent);
        m_animation->setEndValue(newPercent);
        m_animation->start();
    }
}

void SimpleHpBar::setShield(int shield)
{
    m_shield = qMax(0, shield);
    update();
}

void SimpleHpBar::setSize(int width, int height)
{
    setFixedSize(width, height);
}

void SimpleHpBar::setDisplayPercent(float percent)
{
    m_displayPercent = percent;
    update();
}

void SimpleHpBar::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);

    // پس‌زمینه شفاف
    painter.fillRect(rect(), Qt::transparent);

    int pad = 0;
    QRectF barRect(pad, pad, width() - pad * 2, height() - pad * 2);

    painter.setPen(QPen(QColor(80, 80, 80), 1.5));  // خط خاکستری
    painter.setBrush(Qt::NoBrush);  // داخلش خالی باشه
    painter.drawRoundedRect(barRect, 4, 4);

    // رنگ نوار
    QColor barColor = (m_shield > 0) ? QColor(74, 144, 217) : QColor(220, 50, 50);

    // ===== نوار HP =====
    float barWidth = barRect.width() * m_displayPercent;
    if (barWidth > 0) {
        QPainterPath path;
        path.addRoundedRect(QRectF(barRect.x(), barRect.y(), barWidth, barRect.height()), 4, 4);
        painter.fillPath(path, barColor);


    }


    // ===== سپر =====
    if (m_shield > 0) {
        int iconSize = barRect.height() - 4;
        QRectF iconRect(barRect.x() + 3, barRect.y() + 2, iconSize, iconSize);

        painter.setPen(Qt::NoPen); // ine
        painter.setBrush(QColor(74, 144, 217, 100));
        painter.drawRect(iconRect);

        painter.setFont(QFont("Arial", 8, QFont::Bold));
        painter.drawText(iconRect, Qt::AlignCenter, QString::number(m_shield));
    }

    // ===== متن HP =====
    painter.setPen(Qt::white);
    painter.setFont(QFont("Arial", 9, QFont::Bold));
    painter.drawText(barRect, Qt::AlignCenter,
                     QString("%1/%2").arg(m_hp).arg(m_maxHp));
}