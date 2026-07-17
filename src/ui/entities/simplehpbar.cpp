#include "simplehpbar.h"
#include <QPainter>
#include <QPainterPath>
#include "core/setting.h"

SimpleHpBar::SimpleHpBar(QWidget *parent)
    : QWidget(parent)
    , m_hp(100)
    , m_maxHp(100)
    , m_shield(0)
    , m_displayPercent(1.0f)
    , shield_pix(QPixmap(":/icon/shield.ico"))
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
    m_hp = hp;

    float newPercent = std::min((float)m_hp / m_maxHp, 1.0f);

    // اگر آسیب خورده
    if (m_hp < oldHp) {
        float oldPercent = std::min((float)oldHp / m_maxHp, 1.0f);

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

    painter.fillRect(rect(), Qt::transparent);

    int pad = height() / 2;
    QRectF barRect(pad, 9, width() - pad * 2, height() - 18);

    painter.setPen(QPen(QColor(80, 80, 80), 1.5));
    painter.setBrush(Qt::NoBrush);
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
        int iconSize = height();
        QRectF iconRect(0, 0, iconSize, iconSize);

        painter.drawPixmap(iconRect.toRect(), shield_pix.scaled(
                                                  iconRect.size().toSize(),
                                                  Qt::IgnoreAspectRatio,
                                                  Qt::SmoothTransformation));


        QRectF textRect(iconSize, 0, iconSize, iconSize);
        QFont fn;
        fn.setFamily(Fonts::Cascadia);
        fn.setPixelSize(13);
        fn.setBold(true);
        painter.setFont(fn);

        painter.setPen(Qt::black);
        painter.drawText(iconRect.translated(-1, -1), Qt::AlignCenter, QString::number(m_shield));
        painter.drawText(iconRect.translated( 1, -1), Qt::AlignCenter, QString::number(m_shield));
        painter.drawText(iconRect.translated(-1,  1), Qt::AlignCenter, QString::number(m_shield));
        painter.drawText(iconRect.translated( 1,  1), Qt::AlignCenter, QString::number(m_shield));

        painter.setPen(Qt::white);
        painter.drawText(iconRect, Qt::AlignCenter, QString::number(m_shield));

    }

    // ===== متن HP =====
    painter.setPen(Qt::white);
    QFont fn;
    fn.setFamily(Fonts::Cascadia);
    fn.setPixelSize((int)height() * 2 / 5);
    fn.setBold(true);

    painter.setFont(fn);
    painter.drawText(barRect, Qt::AlignCenter,
                     QString("%1/%2").arg(m_hp).arg(m_maxHp));
}