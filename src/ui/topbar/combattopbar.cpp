#include "combattopbar.h"
#include "core/setting.h"
#include "assetsManager/imagemanager.h"
#include "assetsManager/soundmanager.h"
#include <QGraphicsProxyWidget>

CombatTopBar::CombatTopBar(combatEvent* event, ironclad* player, bool is_simple)
    :eve(event)
    ,player(player)
    ,simple(is_simple)
{
    auto mng = imageManager::instance();

    QString blank_css =
        "QPushButton{background:transparent;border:none;padding:0px;margin:0px;}"
        "QPushButton:hover{background:transparent;}"
        "QPushButton:pressed{background:transparent;}"
        "QPushButton:focus{border:none;outline:none;}"
        ;

    QFont f;
    f.setFamily((setting::game_language == language::English) ? (Fonts::Cascadia) : (Fonts::koodak));
    f.setPixelSize(22);

    parent = new BaseItem(nullptr, QSizeF(1600, 75), {0, 0});
    parent->setBackColor(QColor::fromRgb(20, 20, 20));
    parent->setZValue(11000);

    gold_image = new ImageItem(parent, {45, 45}, {50, 10});
    gold_image->setPixmap(mng.getIcon("gold"));

    gold_amount = new TextItem(parent, {100, 45}, {100, 10});
    gold_amount->setFont(f);


    hp_image = new ImageItem(parent, {45, 45}, {250, 10});
    hp_image->setPixmap(mng.getIcon("heart"));

    hp_amount = new TextItem(parent, {100, 45}, {300, 10});
    hp_amount->setFont(f);

    if (!simple){
        energy_bar = new SimpleHpBar();
        energy_bar->setSize(400, 50);

        energy_proxy = new QGraphicsProxyWidget(parent);
        energy_proxy->setWidget(energy_bar);
        energy_proxy->setPos({500, 10});

        end_btn = new QPushButton();
        end_btn->setFont(f);
        end_btn->setText(tr("End Turn"));
        end_btn->setDisabled(true);
        end_btn->installEventFilter(this);
        end_btn->setFixedSize(150, 40);
        end_btn->setStyleSheet("QPushButton {background-color: #6d5732;border: 2px solid #b28a45;border-radius: 8px;color: #f7e7b5;padding: 6px 18px;selection-background-color: transparent;}QPushButton:hover {background-color: #8a6d3d;border: 2px solid #e3bb63;color: #fff6d5;}QPushButton:pressed {background-color: #4d3d22;border: 2px solid #8f6a30;padding-top: 8px;padding-left: 20px;}QPushButton:disabled {background-color: #444444;border: 2px solid #666666;color: #999999;}");

        btn_proxy = new QGraphicsProxyWidget(parent);
        btn_proxy->setWidget(end_btn);
        btn_proxy->setPos({925, 15});

        connect(eve, &combatEvent::turn_started, this,  [=](abstractEntity* entity){
            if (entity == player){
                end_btn->setDisabled(false);
            }
        });

        connect(end_btn, &QPushButton::clicked, this, [=](){
            soundManager::instance().playSoundEffect(SoundEffect::menuSelect);
            end_btn->setDisabled(true);
            emit eve->turn_ended(player);
        });
    }

    end_setting = new QPushButton();
    end_setting->installEventFilter(this);
    end_setting->setFixedSize(45, 45);
    end_setting->setStyleSheet(blank_css);
    end_setting->setIcon(QIcon(":/icon/setting.png"));
    end_setting->setIconSize({45, 45});

    setting_proxy = new QGraphicsProxyWidget(parent);
    setting_proxy->setWidget(end_setting);
    setting_proxy->setPos({1520, 12});

    connect(end_setting, &QPushButton::clicked, this, [=](){
        soundManager::instance().playSoundEffect(SoundEffect::menuSelect);
        emit eve->settingOpen();
    });

    updateBar();
}


bool CombatTopBar::eventFilter(QObject* obj, QEvent* eve) {
    if (obj == end_btn || obj == end_setting) {
        if (eve->type() == QEvent::Enter) {
            soundManager::instance().playSoundEffect(SoundEffect::menuHover);
        }
    }
    return QObject::eventFilter(obj, eve);
}

void CombatTopBar::updateBar() {

    gold_amount->setText(QString::number(player->get_gold()));

    hp_amount->setText(QString::number(player->get_hp()) + "/" + QString::number(player->get_max_hp()));

    if (!simple) {
        energy_bar->setMaxHp(player->get_base_energy());
        energy_bar->setHp(player->get_energy());
    }

}