#include "cardtemplatelegend.h"
#include "ui/cards/getCardPixmap.h"
#include "core/setting.h"
#include <QParallelAnimationGroup>

CardTemplateLegend::CardTemplateLegend(abstractCard* source, QPointF pos, QSizeF size, qreal z_value)
    :card_source(source),
    card_pos(pos),
    card_size(size),
    zValue(z_value)
{
    qreal w = card_size.width();
    qreal h = card_size.height();

    card_parent = new CardParent(nullptr, card_size, card_pos, z_value_zone);



    card_frame = new ImageItem(card_parent, card_size, {0, 0});
    card_frame->setPixmap(QPixmap(":/image/card/frame/frame3.png"));
    card_frame->setZValue(zValue + 1);



    card_image = new ImageItem(card_parent, {0.692 * w, 0.687 * h}, {0.153 * w, 0.146 * h});
    card_image->setPixmap(getCardPixmap(source->get_card_id()));
    card_image->setZValue(zValue);



    card_category = new TextItem(card_parent, {0.588 * w, 0.061 * h}, {0.277 * w, 0.055 * h});
    if (card_source->get_card_type() == CardType::attack) card_category->setText(tr("Attack"));
    else if (card_source->get_card_type() == CardType::skill) card_category->setText(tr("Skill"));
    else if (card_source->get_card_type() == CardType::power) card_category->setText(tr("Power"));
    else if (card_source->get_card_type() == CardType::status) card_category->setText(tr("Status"));
    else if (card_source->get_card_type() == CardType::curse) card_category->setText(tr("Curse"));
    QFont fcat;

    if (setting::game_language == language::English) {
        fcat.setFamily(Fonts::forte);
        fcat.setPixelSize(14);
    }
    else{
        fcat.setFamily(Fonts::ebhaar);
        fcat.setPixelSize(14);
    }
    card_category->setZValue(zValue + 2);
    card_category->setFont(fcat);
    card_category->setColor(Qt::white);



    card_cost = new TextItem(card_parent, {0.175 * w, 0.116 * h}, {0.084 * w, 0.035 * h});
    QFont fcost;

    if (setting::game_language == language::English) {
        fcost.setFamily(Fonts::forte);
        fcost.setPixelSize(25);
    }
    else{
        fcost.setFamily(Fonts::ebhaar);
        fcost.setPixelSize(25);
    }

    card_cost->setFont(fcost);
    card_cost->setZValue(zValue + 2);



    card_name = new TextItem(card_parent, {0.779 * w, 0.072 * h}, {0.110 * w, 0.545 * h});
    QFont fname;

    if (setting::game_language == language::English) {
        fname.setFamily(Fonts::forte);
        fname.setPixelSize(15);
    }
    else{
        fname.setFamily(Fonts::ebhaar);
        fname.setPixelSize(15);
    }

    card_name->setFont(fname);
    card_name->setZValue(zValue + 4);



    card_description = new TextItem(card_parent, {0.749 * w, 0.27 * h}, {0.12 * w, 0.636 * h});
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




void CardTemplateLegend::updateCard() {

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
            card_frame->setPixmap(QPixmap(":/image/cards/back/back3.png"));
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


