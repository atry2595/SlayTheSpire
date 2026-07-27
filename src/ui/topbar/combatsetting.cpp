#include "combatsetting.h"
#include "core/setting.h"
#include <QTimer>
#include "core/setting.h"
#include "assetsManager/soundmanager.h"

combatSetting::combatSetting(combatEvent* eve)
    :event(eve)
{
    QString sliderStyle = R"(
QSlider{
    background: transparent;
    border: none;
}
QSlider::groove:horizontal{
    background:qlineargradient(x1:0,y1:0,x2:0,y2:1,
                               stop:0 #2f3136,
                               stop:1 #1b1c1f);
    border:1px solid #6a5a3a;
    height:10px;
    border-radius:5px;
}

QSlider::sub-page:horizontal{
    background:qlineargradient(x1:0,y1:0,x2:1,y2:0,
                               stop:0 #b98d3d,
                               stop:1 #e5c46b);
    border-radius:5px;
}

QSlider::add-page:horizontal{
    background:#232428;
    border-radius:5px;
}

QSlider::handle:horizontal{
    background:qradialgradient(cx:0.5, cy:0.5, radius:0.8,
                               stop:0 #fff6d6,
                               stop:0.45 #d8b35a,
                               stop:1 #7a5a22);
    border:2px solid #f5d27b;
    width:20px;
    margin:-6px 0;
    border-radius:10px;
}

QSlider::handle:horizontal:hover{
    border:2px solid #fff2b0;
    background:qradialgradient(cx:0.5, cy:0.5, radius:0.9,
                               stop:0 #fffef4,
                               stop:0.45 #e9ca73,
                               stop:1 #8f6825);
}

QSlider::handle:horizontal:pressed{
    background:#ffd66b;
    border:2px solid #ffffff;
}
)";

    QString blank_css =
        "QPushButton{background:transparent;border:none;padding:0px;margin:0px;color:white;}"
        "QPushButton:hover{background:transparent; color: yellow;}"
        "QPushButton:pressed{background:transparent;}"
        "QPushButton:focus{border:none;outline:none;}"
        ;


    parent = new BaseItem(nullptr, {1650, 950}, {0, 0});
    parent->setBackColor(QColor::fromRgba(qRgba(0, 0, 0, 180)));
    parent->setZValue(13100);
    parent->setOpacity(0);

    overlay = new QPushButton();
    overlay->setFixedSize(1650, 950);
    overlay->setDisabled(true);
    overlay->setStyleSheet(blank_css);
    overlay_proxy = new QGraphicsProxyWidget(parent);
    overlay_proxy->setWidget(overlay);
    overlay_proxy->setPos(0, 0);

    header = new TextItem(parent, {1000, 100}, {300, 50});
    header->setText(tr("Setting"));
    QFont f;
    f.setFamily(Fonts::Cascadia);
    f.setPixelSize(45);
    header->setFont(f);
    header->setColor(Qt::yellow);

    QFont txt;
    txt.setFamily(Fonts::Cascadia);
    txt.setPixelSize(20);

    music_txt = new TextItem(parent, {200, 100}, {500, 900 - 650});
    music_txt->setText("Music Volume");
    music_txt->setFont(txt);
    music_txt->setColor(Qt::white);
    music = new QSlider(Qt::Horizontal, nullptr);
    music->resize({300, 100});
    music->setMinimum(0);
    music->setMaximum(100);
    music->setValue(setting::bg_volume * 100);
    music->setStyleSheet(sliderStyle);
    music_prxy = new QGraphicsProxyWidget(parent);
    music_prxy->setWidget(music);
    music_prxy->setPos(700, 900 - 650);

    sfx_txt = new TextItem(parent, {200, 100}, {500, 900 - 500});
    sfx_txt->setText("SFX Volume");
    sfx_txt->setFont(txt);
    sfx_txt->setColor(Qt::white);
    sfx = new QSlider(Qt::Horizontal, nullptr);
    sfx->setFixedSize(300, 100);
    sfx->setMinimum(0);
    sfx->setMaximum(100);
    sfx->setValue(setting::sfx_volume * 100);
    sfx->setStyleSheet(sliderStyle);
    sfx_prxy = new QGraphicsProxyWidget(parent);
    sfx_prxy->setWidget(sfx);
    sfx_prxy->setPos(700, 900 - 500);


    abandon = new QPushButton();
    abandon->setFixedSize(400, 100);
    abandon->setFont(f);
    abandon->setText(tr("Abandon Run"));
    abandon->setStyleSheet(blank_css);
    abandon->installEventFilter(this);
    abandon_prxy = new QGraphicsProxyWidget(parent);
    abandon_prxy->setWidget(abandon);
    abandon_prxy->setPos(600, 900 - 350);


    back = new QPushButton();
    back->setFixedSize(200, 100);
    back->setFont(f);
    back->setText(tr("Back"));
    back->setStyleSheet(blank_css);
    back->installEventFilter(this);
    back_prxy = new QGraphicsProxyWidget(parent);
    back_prxy->setWidget(back);
    back_prxy->setPos(700, 900 - 200);

    parent->fadeTo(1, 500, QEasingCurve::OutSine);

    connect(abandon, &QPushButton::clicked, this, [=](){
        parent->deleteLater();
        this->deleteLater();
        emit event->game_lose();
    });

    connect(back, &QPushButton::clicked, this, [=](){
        soundManager::instance().playSoundEffect(SoundEffect::menuSelect);
        parent->fadeTo(0, 500, QEasingCurve::OutSine);
        QTimer::singleShot(1000, [=](){
            parent->deleteLater();
            this->deleteLater();
        });
    });

    connect(music, &QSlider::valueChanged, this, [=](int v){
        setting::bg_volume = v/100.0;
        soundManager::instance().setBackVolume(setting::bg_volume);
    });

    connect(sfx, &QSlider::valueChanged, this, [=](int v){
        setting::sfx_volume = v/100.0;
    });
}

bool combatSetting::eventFilter(QObject* obj, QEvent* eve) {
    if (obj == back || obj == abandon) {
        if (eve->type() == QEvent::Enter) {
            soundManager::instance().playSoundEffect(SoundEffect::menuHover);
        }
    }
    return QObject::eventFilter(obj, eve);
}

