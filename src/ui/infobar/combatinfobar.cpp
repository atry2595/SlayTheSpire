#include "combatinfobar.h"
#include "assetsManager/imagemanager.h"
#include "core/setting.h"

void CombatInfoBar::initial() {
    parent =  new infobarParent(nullptr, barAlign::left, {1600, 900});
    parent->setZValue(123456);

    border = new BaseItem(parent, {600, 900}, {-195, 0});
    border->setBackColor(QColor::fromRgb(0, 0, 0));

    section = new BaseItem(parent, {600, 900}, {-200, 0});
    section->setBackColor(QColor::fromRgb(0, 0, 20));


    item_image = new ImageItem(parent, {200, 200}, {100, 100});
    item_image->setHighlight(true);

    item_name = new TextItem(parent, {300, 100}, {50, 300});
    QFont ft;
    ft.setBold(true);
    ft.setFamily((setting::game_language == language::English)?(Fonts::Cascadia):(Fonts::koodak));
    ft.setPixelSize(23);
    item_name->setFont(ft);

    item_description = new TextItem(parent, {300, 100}, {50, 400});
    QFont fd;
    fd.setBold(true);
    fd.setFamily((setting::game_language == language::English)?(Fonts::Cascadia):(Fonts::koodak));
    fd.setPixelSize(18);
    item_description->setFont(fd);
    item_description->setAlignment(Qt::AlignTop | Qt::AlignCenter);

    item_story = new TextItem(parent, {300, 350}, {50, 500});
    QFont fs;
    fs.setBold(true);
    fs.setFamily((setting::game_language == language::English)?(Fonts::lotrance):(Fonts::ebhaar));
    fs.setPixelSize(20);
    item_story->setFont(fs);
    item_story->setAlignment(Qt::AlignTop | Qt::AlignCenter);
    item_story->setColor(QColor::fromRgb(240, 210, 225));


}

CombatInfoBar::CombatInfoBar(abstractRelic* rlc) {
    initial();
    if (rlc->get_rarity() == relicRarity::boss){
        item_name->setColor(Qt::red);
        item_image->setHighlightColor(Qt::red);
    }
    else if (rlc->get_rarity() == relicRarity::event) {
        item_name->setColor(Qt::yellow);
        item_image->setHighlightColor(Qt::yellow);
    }
    else if (rlc->get_rarity() == relicRarity::rare) {
        item_name->setColor(Qt::green);
        item_image->setHighlightColor(Qt::green);
    }
    else{
        item_name->setColor(Qt::cyan);
        item_image->setHighlightColor(Qt::cyan);
    }
    item_image->setPixmap(imageManager::instance().getRelicIcon(rlc->get_id()));
    item_name->setText(rlc->get_name());
    item_description->setText(rlc->get_description());
    item_story->setText(rlc->get_story());
}

CombatInfoBar::CombatInfoBar(abstractPotion* pot) {
    initial();
    if (pot->get_type() == PotionType::rare){
        item_name->setColor(Qt::yellow);
        item_image->setHighlightColor(Qt::yellow);
    }
    else if (pot->get_type() == PotionType::uncommon) {
        item_name->setColor(Qt::cyan);
        item_image->setHighlightColor(Qt::cyan);
    }
    else{
        item_name->setColor(Qt::green);
        item_image->setHighlightColor(Qt::green);
    }

    item_image->setPixmap(imageManager::instance().getPotionIcon(pot->get_ID()));
    item_name->setText(pot->get_name());
    item_description->setText(pot->get_description());
    item_story->setText(pot->get_story());
}

CombatInfoBar::CombatInfoBar(abstractPower* pwr) {
    initial();

    if (pwr->get_is_buff()){
        item_name->setColor(Qt::green);
        item_image->setHighlightColor(Qt::green);
    }
    else{
        item_name->setColor(Qt::red);
        item_image->setHighlightColor(Qt::red);
    }

    item_image->setPixmap(imageManager::instance().getPowerIcon(pwr->get_id()));
    item_name->setText(pwr->get_name());
    item_description->setText(pwr->get_description());
    item_story->setText(pwr->get_story());
}

CombatInfoBar::CombatInfoBar(abstractEntity* ent) {
    initial();

    if (ent->get_ID() == entityID::ironclad){
        item_name->setColor(Qt::yellow);
        item_image->setHighlightColor(Qt::yellow);
    }
    else{
        item_name->setColor(Qt::red);
        item_image->setHighlightColor(Qt::red);
    }

    item_image->setPixmap(imageManager::instance().getEntity1x1(ent->get_ID()));
    item_name->setText(ent->get_name());
    item_description->setText("");
    item_story->setText(ent->get_story());
}


CombatInfoBar::~CombatInfoBar() {
    delete parent;
}