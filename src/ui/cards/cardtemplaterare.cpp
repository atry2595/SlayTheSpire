#include "cardtemplaterare.h"
#include "assetsManager/imagemanager.h"
#include "core/setting.h"
#include <QParallelAnimationGroup>

CardTemplateRare::CardTemplateRare(combatEvent* eve, abstractCard* source, QPointF pos, QSizeF size, qreal z_value)
    :abstractCardTemplate(eve, source, pos, size, z_value)
{
    auto mng = imageManager::instance();

    qreal w = card_size.width();
    qreal h = card_size.height();



    card_frame = new ImageItem(card_parent, card_size, {0, 0});
    card_frame->setPixmap(mng.getCardFrame(cardTemplates::metallic, source->get_card_type()));
    card_frame->setZValue(zValue + 1);



    card_image = new ImageItem(card_parent, {0.596 * w, 0.592 * h}, {0.2015 * w, 0.20 * h});
    card_image->setPixmap(mng.getCardImage(source->get_card_id()));
    card_image->setZValue(zValue);



    card_category = new TextItem(card_parent, {0.387 * w, 0.057 * h}, {0.308 * w, 0.150 * h});
    if (card_source->get_card_type() == CardType::attack) card_category->setText(tr("Attack"));
    else if (card_source->get_card_type() == CardType::skill) card_category->setText(tr("Skill"));
    else if (card_source->get_card_type() == CardType::power) card_category->setText(tr("Power"));
    else if (card_source->get_card_type() == CardType::status) card_category->setText(tr("Status"));
    else if (card_source->get_card_type() == CardType::curse) card_category->setText(tr("Curse"));
    QFont fcat;

    if (setting::game_language == language::English) {
        fcat.setFamily(Fonts::lotrance);
        fcat.setPixelSize(14);
    }
    else{
        fcat.setFamily(Fonts::cinema);
        fcat.setPixelSize(14);
    }
    card_category->setZValue(zValue + 2);
    card_category->setFont(fcat);
    card_category->setColor(Qt::black);



    card_cost = new TextItem(card_parent, {0.15 * w, 0.1 * h}, {0.427 * w, 0.046 * h});
    QFont fcost;

    if (setting::game_language == language::English) {
        fcost.setFamily(Fonts::lotrance);
        fcost.setPixelSize(24);
    }
    else{
        fcost.setFamily(Fonts::cinema);
        fcost.setPixelSize(24);
    }

    card_cost->setFont(fcost);
    card_cost->setZValue(zValue + 2);



    card_name = new TextItem(card_parent, {0.5965 * w, 0.092 * h}, {0.2015 * w, 0.471 * h});
    QFont fname;

    if (setting::game_language == language::English) {
        fname.setFamily(Fonts::lotrance);
        fname.setPixelSize(14);
    }
    else{
        fname.setFamily(Fonts::cinema);
        fname.setPixelSize(14);
    }

    card_name->setFont(fname);
    card_name->setZValue(zValue + 4);



    card_description = new TextItem(card_parent, {0.6835 * w, 0.224 * h}, {0.159 * w, 0.730 * h});
    QFont fdesc;

    if (setting::game_language == language::English) {
        fdesc.setFamily(Fonts::Cascadia);
        fdesc.setPixelSize(11);
    }
    else{
        fdesc.setFamily(Fonts::koodak);
        fdesc.setPixelSize(11 * 1.15);
    }

    card_description->setFont(fdesc);
    card_description->setColor(Qt::white);
    card_description->setZValue(zValue + 3);


    updateCard();
}




void CardTemplateRare::updateCard() {

    //=================locked==============
    // if (card_source->get_turn_lock()) {
    //     card_parent->setCanSelect(false);
    //     card_parent->setCanHover(false);

    //     QParallelAnimationGroup* outAnim = new QParallelAnimationGroup();
    //     QParallelAnimationGroup* inAnim = new QParallelAnimationGroup();
    //     QSequentialAnimationGroup* gr = new QSequentialAnimationGroup();

    //     gr->addPause(500);

    //     outAnim->addAnimation(card_parent->createMoveAnimation(
    //         {card_pos + QPointF(0, card_size.height())}
    //         , 350, QEasingCurve::OutSine));

    //     gr->addAnimation(outAnim);
    //     connect(outAnim, &QPropertyAnimation::finished, this, [this]() {
    //         card_frame->setPixmap(QPixmap(":/image/cards/back/back2.png"));
    //         card_image->clearPixmap();
    //         card_cost->clearText();
    //         card_category->clearText();
    //         card_name->clearText();
    //         card_description->clearText();
    //         card_parent->setZValue(card_parent->zValue() - z_value_zone);
    //     });



    //     inAnim->addAnimation(card_parent->createMoveAnimation(
    //         {card_pos}
    //         , 350, QEasingCurve::InSine));

    //     gr->addAnimation(inAnim);

    //     gr->start();

    // }
    //=================locked==============


    //====================cost======================
    card_cost->setText(QString::number(card_source->get_energy()));
    if (card_source->repeat_x_time()){
        card_cost->setText("X");
    }

    if (card_source->get_turn_playable() == false) {
        card_cost->setColor(Qt::red);
        card_cost->setText("-");
    }
    else if (card_source->get_available() && !card_source->get_turn_lock()){
        if (card_source->get_upgraded()) card_cost->setColor(Qt::green);
        else card_cost->setColor(Qt::white);
    }
    else{
        card_cost->setColor(Qt::red);
    }
    //====================cost======================



    //===================name===================
    if (card_source->get_upgraded()){
        card_name->setText(card_source->get_name() + "@");

        if (card_source->is_rare()) card_name->setColor({255, 195, 0}); //gold
        else card_name->setColor(Qt::green);
    }
    else{
        card_name->setText(card_source->get_name());

        if (card_source->is_rare()) card_name->setColor({255, 230, 155}); //light gold
        else card_name->setColor(Qt::white);
    }
    //===================name===================


    //=================desc=================
    card_description->setText(card_source->get_description());
    //=================desc=================


}


