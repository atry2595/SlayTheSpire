#ifndef SIMPLEHPBAR_H
#define SIMPLEHPBAR_H

#include <QWidget>
#include <QPropertyAnimation>

class SimpleHpBar : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(float displayPercent READ displayPercent WRITE setDisplayPercent)
    const QPixmap shield_pix;

public:
    explicit SimpleHpBar(QWidget *parent = nullptr);

    void setMaxHp(int maxHp);
    void setHp(int hp);
    void setShield(int shield);
    void setSize(int width, int height);

    int hp() const { return m_hp; }
    int maxHp() const { return m_maxHp; }
    int shield() const { return m_shield; }
    float displayPercent() const { return m_displayPercent; }

public slots:
    void setDisplayPercent(float percent);

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    int m_hp;
    int m_maxHp;
    int m_shield;
    float m_displayPercent;

    QPropertyAnimation *m_animation;
};

#endif