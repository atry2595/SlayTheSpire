#include "cardtemplateuncommon.h"
#include "ui/cards/getCardPixmap.h"
#include "core/setting.h"
#include <QParallelAnimationGroup>

CardTemplateUncommon::CardTemplateUncommon(abstractCard* source, QPointF pos, QSizeF size, qreal z_value)
    :abstractCardTemplate(source, pos, size, z_value)
{
    qreal w = card_size.width();
    qreal h = card_size.height();



    card_frame = new ImageItem(card_parent, card_size, {0, 0});
    card_frame->setPixmap(QPixmap(":/image/card/frame/frame1.png"));
    card_frame->setZValue(zValue + 1);



    card_image = new ImageItem(card_parent, {0.73 * w, 0.726 * h}, {0.1345 * w, 0.182 * h});
    card_image->setPixmap(getCardPixmap(source->get_card_id()));
    card_image->setZValue(zValue);



    card_category = new TextItem(card_parent, {0.517 * w, 0.046 * h}, {0.2415 * w, 0.124 * h});
    if (card_source->get_card_type() == CardType::attack) card_category->setText(tr("Attack"));
    else if (card_source->get_card_type() == CardType::skill) card_category->setText(tr("Skill"));
    else if (card_source->get_card_type() == CardType::power) card_category->setText(tr("Power"));
    else if (card_source->get_card_type() == CardType::status) card_category->setText(tr("Status"));
    else if (card_source->get_card_type() == CardType::curse) card_category->setText(tr("Curse"));
    QFont fcat;

    if (setting::game_language == language::English) {
        fcat.setFamily(Fonts::rock);
        fcat.setPixelSize(14);
    }
    else{
        fcat.setFamily(Fonts::titrZ);
        fcat.setPixelSize(14 * 0.8);
    }
    card_category->setZValue(zValue + 2);
    card_category->setFont(fcat);
    card_category->setColor(Qt::black);



    card_cost = new TextItem(card_parent, {0.1585 * w, 0.105 * h}, {0.421 * w, 0.0256 * h});
    QFont fcost;

    if (setting::game_language == language::English) {
        fcost.setFamily(Fonts::rock);
        fcost.setPixelSize(24);
    }
    else{
        fcost.setFamily(Fonts::titrZ);
        fcost.setPixelSize(24 * 0.8);
    }

    card_cost->setFont(fcost);
    card_cost->setZValue(zValue + 2);



    card_name = new TextItem(card_parent, {0.730 * w, 0.080 * h}, {0.1345 * w, 0.545 * h});
    QFont fname;

    if (setting::game_language == language::English) {
        fname.setFamily(Fonts::rock);
        fname.setPixelSize(14);
    }
    else{
        fname.setFamily(Fonts::titrZ);
        fname.setPixelSize(14 * 0.8);
    }

    card_name->setFont(fname);
    card_name->setZValue(zValue + 4);



    card_description = new TextItem(card_parent, {0.794 * w, 0.242 * h}, {0.103 * w, 0.635 * h});
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
    card_description->setColor(Qt::black);
    card_description->setZValue(zValue + 3);



    updateCard();
}




void CardTemplateUncommon::updateCard() {

    //=================locked==============
    if (card_source->get_turn_lock()) {
        card_parent->setCanSelect(false);
        card_parent->setCanHover(false);

        QParallelAnimationGroup* outAnim = new QParallelAnimationGroup();
        QParallelAnimationGroup* inAnim = new QParallelAnimationGroup();
        QSequentialAnimationGroup* gr = new QSequentialAnimationGroup();

        gr->addPause(500);

        outAnim->addAnimation(card_parent->createMoveAnimation(
            {card_pos + QPointF(0, card_size.height())}
            , 350, QEasingCurve::OutSine));

        gr->addAnimation(outAnim);
        connect(outAnim, &QPropertyAnimation::finished, this, [this]() {
            card_frame->setPixmap(QPixmap(":/image/cards/back/back1.png"));
            card_image->clearPixmap();
            card_cost->clearText();
            card_category->clearText();
            card_name->clearText();
            card_description->clearText();
            card_parent->setZValue(card_parent->zValue() - z_value_zone);
        });



        inAnim->addAnimation(card_parent->createMoveAnimation(
            {card_pos}
            , 350, QEasingCurve::InSine));

        gr->addAnimation(inAnim);

        gr->start();

    }
    //=================locked==============


    //====================cost======================
    card_cost->setText(QString::number(card_source->get_energy()));
    if (card_source->repeat_x_time()){
        card_cost->setText("X");
    }
    if (card_source->get_available()){
        if (card_source->get_upgraded()) card_cost->setColor(Qt::green);
        else card_cost->setColor(Qt::white);
    }
    else{
        card_cost->setColor(Qt::red);
    }
    //====================cost======================



    //===================name===================
    if (card_source->get_upgraded()){
        card_name->setText(card_source->get_name() + "+");

        if (card_source->is_rare()) card_name->setColor({246, 0, 182}); //magenta
        else card_name->setColor(Qt::green);
    }
    else{
        card_name->setText(card_source->get_name());

        if (card_source->is_rare()) card_name->setColor({255, 175, 234}); //light magenta
        else card_name->setColor(Qt::white);
    }
    //===================name===================


    //=================desc=================
    card_description->setText(card_source->get_description());
    //=================desc=================


}


