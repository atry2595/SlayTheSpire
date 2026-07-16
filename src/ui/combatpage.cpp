#include "combatpage.h"
#include <QVBoxLayout>
#include <QResizeEvent>
#include "ui/entities/getvisualdata.h"
#include <QTimer>
#include "ui/cards/cardtemplatecommon.h"
#include "ui/cards/cardtemplateuncommon.h"
#include "ui/cards/cardtemplaterare.h"
#include "ui/cards/cardtemplatelegend.h"
#include "ui/cards/getCardPixmap.h"
#include "core/setting.h"

//=================================================================================
//=====================contructur and intializer functions=========================
//=================================================================================

CombatPage::CombatPage(QWidget *parent, combat_manager* m, ironclad* plyr)
    : QWidget{parent}
    , manager(m)
    , player(plyr)
    , eve(m->get_event())
{
    tmpl = cardTemplate::legend;

    //----------------------------------------------------
    combatView = new QGraphicsView(this);
    combatScene = new QGraphicsScene(this);

    combatScene->setSceneRect(0, 0, 1600, 900);
    combatView->setScene(combatScene);

    combatView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    combatView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    combatView->setFrameShape(QFrame::NoFrame);
    combatView->setStyleSheet("background: red;");

    combatView->setRenderHint(QPainter::Antialiasing, true);
    combatView->setRenderHint(QPainter::SmoothPixmapTransform, true);


    auto* layout = new QVBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);
    layout->addWidget(combatView);
    setLayout(layout);

    QMetaObject::invokeMethod(this, [this]() {
        combatView->fitInView(combatScene->sceneRect(), Qt::KeepAspectRatio);
    }, Qt::QueuedConnection);

    //----------------------------------------------------
    ImageItem* bg = new ImageItem(nullptr, {1632, 918}, {-16, -9});
    bg->setPixmap(QPixmap(":/image/scene/map1_dark.jpg"));
    bg->setZValue(0);

    QFont f;
    f.setBold(true);
    f.setFamily(Fonts::Cascadia);
    f.setPixelSize(22);

    draw_pile = new TextItem(nullptr, {50, 75}, {10, 710});
    draw_pile->setBackground(getBackCard(tmpl));
    draw_pile->setColor(Qt::white);
    draw_pile->setFont(f);
    draw_pile->setAlignment(Qt::AlignHCenter | Qt::AlignBottom);
    draw_pile->setBorder(true);
    draw_pile->setZValue(5500);

    discard_pile = new TextItem(nullptr, {50, 75}, {1600 - 10 - 50, 710});
    discard_pile->setBackground(getBackCard(tmpl));
    discard_pile->setColor(Qt::white);
    discard_pile->setFont(f);
    discard_pile->setAlignment(Qt::AlignHCenter | Qt::AlignBottom);
    discard_pile->setBorder(true);
    discard_pile->setZValue(5500);

    combatScene->addItem(bg);
    combatScene->addItem(draw_pile);
    combatScene->addItem(discard_pile);

    draw_pile->setText(QString::number(player->get_deck().size()));
    discard_pile->setText(QString::number(player->get_discard_pile().size()));
    //----------------------------------------------------

    start_combat();

    connect(eve, &combatEvent::card_moved, this, [=](playCardInfo& card, PileType from, PileType to){
        this->cardMovePile(card.card, from, to);
    });
    connect(eve, &combatEvent::cardPressed, this, &CombatPage::card_pressed);
    connect(eve, &combatEvent::cardMoved, this, &CombatPage::card_moved);
    connect(eve, &combatEvent::cardReleased, this, &CombatPage::card_released);
    connect(eve, &combatEvent::cardUpdated, this, &CombatPage::card_updated);
    //----------------------------------------------------
}



void CombatPage::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent(event);

    if (combatView && combatScene) {
        combatView->fitInView(combatScene->sceneRect(), Qt::KeepAspectRatioByExpanding);
    }
}



void CombatPage::start_combat() {
    if (!manager) return;

    initialize_layout();
}



void CombatPage::initialize_layout() {

    int players_count = manager->get_players().size();
    int sum_players_width = 1;
    int players_margine_width = 0;

    int enemies_count = manager->get_enemies().size();
    int sum_enemies_width = 1;
    int enemies_margine_width = 0;



    for (auto item :manager->get_players()){
        sum_players_width += getEntityVisual(item->get_ID()).size.width();
    }
    for (auto item : manager->get_enemies()){
        sum_enemies_width += getEntityVisual(item->get_ID()).size.width();
    }


    players_scene_width = std::min(sum_players_width * 1600 / (sum_players_width + sum_enemies_width), 800);
    enemies_scene_width = 1600 - players_scene_width;

    players_margine_width = (players_scene_width - sum_players_width) / (players_count + 1);
    enemies_margine_width = (enemies_scene_width - sum_enemies_width) / (enemies_count + 1);

    qreal x = players_margine_width;
    for (auto item : manager->get_players())  {
        auto p = new IroncladItem(item, {x, 565 - getEntityVisual(item->get_ID()).size.height()}, 100);
        players.push_back(p);
        combatScene->addItem(p->getParent());
        x += getEntityVisual(item->get_ID()).size.width() + players_margine_width;
    }

    x += enemies_margine_width;
    for (auto item : manager->get_enemies())  {
        auto p = new EnemyItem(item, {x, 565 - getEntityVisual(item->get_ID()).size.height()}, 200);
        enemies.push_back(p);
        combatScene->addItem(p->getParent());
        x += getEntityVisual(item->get_ID()).size.width() + enemies_margine_width;
    }

}



void CombatPage::reset_layout() {
    for (auto item : enemies) delete item;
    enemies.clear();

    int sum_enemy = 0;
    int count = 0;

    for (int i = 0; i < manager->get_enemies().size(); i++){
        if (manager->get_enemy_is_alive()[i]){
            count++;
            sum_enemy += getEntityVisual(manager->get_enemies()[i]->get_ID()).size.width();
        }
    }

    int margine = (enemies_scene_width - sum_enemy) / (count + 1);

    qreal x = players_scene_width + margine;

    for (int i = 0; i < manager->get_enemies().size(); i++){
        if (manager->get_enemy_is_alive()[i]){
            auto p = new EnemyItem(manager->get_enemies()[i], {x, 565 - getEntityVisual(manager->get_enemies()[i]->get_ID()).size.height()}, 200);
            enemies.push_back(p);
            combatScene->addItem(p->getParent());
            x += getEntityVisual(manager->get_enemies()[i]->get_ID()).size.width() + margine;
        }
    }
}

//=================================================================================
//====================characters functions & animations============================
//=================================================================================


void CombatPage::escape_entity(abstractEntity* entity) {
    for (int i = 0; i < players.size(); i++) {
        if (entity == players[i]->getSource()) {
            players[i]->escapeAnim();
        }
    }
    for (int i = 0; i < enemies.size(); i++) {
        if (entity == enemies[i]->getSource()) {
            enemies[i]->escapeAnim();
        }
    }
}

void CombatPage::died_entity(abstractEntity* entity) {
    for (int i = 0; i < players.size(); i++) {
        if (entity == players[i]->getSource()) {
            players[i]->escapeAnim();
        }
    }
    for (int i = 0; i < enemies.size(); i++) {
        if (entity == enemies[i]->getSource()) {
            enemies[i]->escapeAnim();
        }
    }
}


void CombatPage::remove_entity(abstractEntity* entity) {
    for (int i = 0; i < players.size(); i++) {
        if (entity == players[i]->getSource()) {
            delete players[i];
            players.erase(players.begin() + i);
            return;
        }
    }
    for (int i = 0; i < enemies.size(); i++) {
        if (entity == enemies[i]->getSource()) {
            delete enemies[i];
            enemies.erase(enemies.begin() + i);
            return;
        }
    }
}

//=================================================================================
//=====================card functions & aniamtions=================================
//=================================================================================

void CombatPage::cardAdd(abstractCard* card, qreal z) {
    if (created_cards.find(card) != created_cards.end()) return;

    switch (tmpl) {
    case cardTemplate::common:
        created_cards[card] = new CardTemplateCommon(eve, card, {1650, 950}, {200, 300}, z);
        break;

    case cardTemplate::uncommon:
        created_cards[card] = new CardTemplateUncommon(eve, card, {1650, 950}, {200, 300}, z);
        break;
    case cardTemplate::rare:
        created_cards[card] = new CardTemplateRare(eve, card, {1650, 950}, {200, 300}, z);
        break;
    case cardTemplate::legend:
        created_cards[card] = new CardTemplateLegend(eve, card, {1650, 950}, {200, 300}, z);
        break;
    }
    combatScene->addItem(created_cards[card]->getParent());
    created_cards[card]->updateCard();
}


void CombatPage::setHandCardPoint(abstractCard* card, bool enter) {
    int hand_count = player->get_hand_pile().size();
    int i;
    for (i = 0; i < hand_count; i++) {
        if (player->get_hand_pile()[i] == card) break;
    }
    created_cards[card]->getParent()->setZValue(4401 + 10 * i);
    QPointF orig = created_cards[card]->getCardpos();

    if (i == hand_count) {
        created_cards[card]->setCardpos({orig.x(), 950});
        return;
    }

    qreal x = 770 - 70 * hand_count + 140 * i;
    if (enter) {
        created_cards[card]->setCardpos({x, 950});
        QTimer* t = new QTimer();
        t->start(500);

        connect(t, &QTimer::timeout, this, [=](){
            t->stop();
            created_cards[card]->setCardpos({x, 700});
        });
    }

    else {
        created_cards[card]->setCardpos({x, orig.y()});
    }

}


void CombatPage::cardMovePile(abstractCard* card, PileType from, PileType to) {
    draw_pile->setText(QString::number(player->get_draw_pile().size()));
    discard_pile->setText(QString::number(player->get_discard_pile().size()));

    //------------------------------------------------------------------------------------
    if (from == PileType::hand){
        setHandCardPoint(card);

        QTimer* t = new QTimer(this);
        t->start(3000);

        connect(t, &QTimer::timeout, this, [=](){
            t->stop();
            delete created_cards[card];
            created_cards.erase(card);
        });

        for (auto item : player->get_hand_pile()) {
            setHandCardPoint(item);
        }

    }

    //------------------------------------------------------------------------------------

    if (to == PileType::hand){
        cardAdd(card);

        for (auto item : player->get_hand_pile()) {
            setHandCardPoint(item, true);
        }

    }

    //------------------------------------------------------------------------------------

    if (from == PileType::discard){
        ImageItem* img = new ImageItem(nullptr, {40, 60}, {1650, 950});
        combatScene->addItem(img);
        img->setPixmap(getBackCard(tmpl));

        QPointF org = discard_pile->pos() + QPointF(5, 0);
        QPointF dest = discard_pile->pos() + QPointF(5, 200);
        auto anim = img->createMoveAnimation({dest}, 500);
        anim->setStartValue(org);
        anim->start();

        QTimer* t = new QTimer(this);
        t->start(3000);

        connect(t, &QTimer::timeout, this, [=](){
            t->stop();
            delete img;
        });
    }

    //------------------------------------------------------------------------------------

    if (to == PileType::discard){
        ImageItem* img = new ImageItem(nullptr, {40, 60}, {1650, 950});
        combatScene->addItem(img);
        img->setPixmap(getBackCard(tmpl));

        QPointF dest = discard_pile->pos() + QPointF(5, 0);
        QPointF org = discard_pile->pos() + QPointF(5, 200);
        auto anim = img->createMoveAnimation({dest}, 500);
        anim->setStartValue(org);
        anim->start();

        QTimer* t = new QTimer(this);
        t->start(3000);

        connect(t, &QTimer::timeout, this, [=](){
            t->stop();
            delete img;
        });
    }

    //------------------------------------------------------------------------------------

    if (from == PileType::draw){
        ImageItem* img = new ImageItem(nullptr, {40, 60}, {1650, 950});
        combatScene->addItem(img);
        img->setPixmap(getBackCard(tmpl));

        QPointF org = draw_pile->pos() + QPointF(5, 0);
        QPointF dest = draw_pile->pos() + QPointF(5, 200);
        auto anim = img->createMoveAnimation({dest}, 500);
        anim->setStartValue(org);
        anim->start();

        QTimer* t = new QTimer(this);
        t->start(3000);

        connect(t, &QTimer::timeout, this, [=](){
            t->stop();
            delete img;
        });
    }

    //------------------------------------------------------------------------------------

    if (to == PileType::draw){
        ImageItem* img = new ImageItem(nullptr, {40, 60}, {1650, 950});
        combatScene->addItem(img);
        img->setPixmap(getBackCard(tmpl));

        QPointF dest = draw_pile->pos() + QPointF(5, 0);
        QPointF org = draw_pile->pos() + QPointF(5, 200);
        auto anim = img->createMoveAnimation({dest}, 500);
        anim->setStartValue(org);
        anim->start();

        QTimer* t = new QTimer(this);
        t->start(3000);

        connect(t, &QTimer::timeout, this, [=](){
            t->stop();
            delete img;
        });
    }
//------------------------------------------------------------------------------------
    created_cards[card]->updateCard();

}



//====================================================================
//======================manager slots=================================
//====================================================================


void CombatPage::card_moved(CardParent* card, const QPointF& pos) {

    switch (card->getSource()->get_target_type()) {
    //--------------------------------------------------------------------------------------------
    case TargetType::single_target: {

        for (auto item : enemies) {


            if (entity_corner_effect.find(item->getSource()) == entity_corner_effect.end()){
                auto img = item->getImage();
                entity_corner_effect[item->getSource()] = new entityCornersFrame(img->scenePos(), img->size());
                combatScene->addItem(entity_corner_effect[item->getSource()]->getParent());
            }
            if (item->getParent()->contains(item->getParent()->mapFromScene(pos))
                && entity_corner_effect[item->getSource()]->getVisisble() == false) {
                qDebug() << "in single :" << entity_corner_effect[item->getSource()]->getParent()->scenePos();
                entity_corner_effect[item->getSource()]->EntranceEffect();
            }
            else if (!item->getParent()->contains(item->getParent()->mapFromScene(pos))
                && entity_corner_effect[item->getSource()]->getVisisble() == true) {
                qDebug() << "in single :" << entity_corner_effect[item->getSource()]->getParent()->scenePos();
                entity_corner_effect[item->getSource()]->ExitEffect();
            }
        }
        break;
    }
    //--------------------------------------------------------------------------------------------
    case TargetType::enemies: {
        if (pos.y() < 650) {
            for (auto item : enemies) {


                if (entity_corner_effect.find(item->getSource()) == entity_corner_effect.end()){
                    auto img = item->getImage();
                    entity_corner_effect[item->getSource()] = new entityCornersFrame(img->scenePos(), img->size());
                    combatScene->addItem(entity_corner_effect[item->getSource()]->getParent());
                }
                if (entity_corner_effect[item->getSource()]->getVisisble() == false) {
                    qDebug() << "in enemies :" << entity_corner_effect[item->getSource()]->getParent()->scenePos();
                    entity_corner_effect[item->getSource()]->EntranceEffect();
                }
            }
        }
        else {
            for (auto item : enemies) {


                if (entity_corner_effect.find(item->getSource()) == entity_corner_effect.end()){
                    auto img = item->getImage();
                    entity_corner_effect[item->getSource()] = new entityCornersFrame(img->scenePos(), img->size());
                    combatScene->addItem(entity_corner_effect[item->getSource()]->getParent());
                }
                if (entity_corner_effect[item->getSource()]->getVisisble() == true) {
                    entity_corner_effect[item->getSource()]->ExitEffect();
                }
            }
        }
        break;
    }
    //--------------------------------------------------------------------------------------------
    case TargetType::self: {
        if (pos.y() < 650) {
            for (auto item : players) {
                if (item->getSource() != player) continue;

                if (entity_corner_effect.find(item->getSource()) == entity_corner_effect.end()){
                    auto img = item->getImage();
                    entity_corner_effect[item->getSource()] = new entityCornersFrame(img->scenePos(), img->size());
                    combatScene->addItem(entity_corner_effect[item->getSource()]->getParent());
                }
                if (entity_corner_effect[item->getSource()]->getVisisble() == false) {
                    qDebug() << "in enemies :" << entity_corner_effect[item->getSource()]->getParent()->scenePos();
                    entity_corner_effect[item->getSource()]->EntranceEffect();
                }
            }
        }
        else {
            for (auto item : players) {
                if (item->getSource() != player) continue;

                if (entity_corner_effect.find(item->getSource()) == entity_corner_effect.end()){
                    auto img = item->getImage();
                    entity_corner_effect[item->getSource()] = new entityCornersFrame(img->scenePos(), img->size());
                    combatScene->addItem(entity_corner_effect[item->getSource()]->getParent());
                }
                if (entity_corner_effect[item->getSource()]->getVisisble() == true) {
                    entity_corner_effect[item->getSource()]->ExitEffect();
                }
            }
        }
        break;
    }
    //--------------------------------------------------------------------------------------------
    default:
        break;
    }

}


void CombatPage::card_released(CardParent* card, const QPointF& pos) {
    for (auto item : entity_corner_effect) {
        if (item.second->getVisisble()) item.second->ExitEffect();
    }

    if (card->getSource()->get_available() == false ||
        card->getSource()->get_turn_playable() == false ||
        card->getSource()->get_turn_lock() == true ||
        card->getSource()->get_energy() > player->get_energy() )
    {
        qDebug() << card->getSource()->get_available() ;
        qDebug() << card->getSource()->get_turn_playable();
        qDebug() << card->getSource()->get_turn_lock();
        qDebug() << card->getSource()->get_energy() ;
        qDebug() << player->get_energy() ;
        return;
    }

    switch (card->getSource()->get_target_type()) {
    //-----------------------------------------------------------------------------------------------
    case TargetType::single_target: {
        for (auto item : enemies) {
            if (item->getParent()->contains(item->getParent()->mapFromScene(pos))) {
                playCardInfo inf;
                inf.card = card->getSource();
                inf.owner = player;
                inf.target_list = {item->getSource()};

                qDebug() << "salam mamadd";

                game_action acts(eve);
                player->play_card(inf);

                return;
            }
        }
        break;
    }
    //-----------------------------------------------------------------------------------------------
    case TargetType::enemies: {
        playCardInfo inf;
        inf.card = card->getSource();
        inf.owner = player;
        for (auto item : enemies) {
            inf.target_list.push_back(item->getSource());
        }
        game_action acts(eve);
        player->play_card(inf);
        return;
    }
    //-----------------------------------------------------------------------------------------------
    case TargetType::self: {
        playCardInfo inf;
        inf.card = card->getSource();
        inf.owner = player;

        game_action acts(eve);
        player->play_card(inf);
        return;
    }
    default:
        return;
    }
}

void CombatPage::card_updated(abstractCard* card) {
    if (created_cards.find(card) != created_cards.end()){
        created_cards[card]->updateCard();
    }
}