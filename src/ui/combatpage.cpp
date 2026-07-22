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
#include "ui/effects/damageeffect.h"
#include "ui/effects/DamageParticleManager.h"
#include "ui/selectItem/selectcard.h"
#include "ui/selectItem/collectreward.h"

//=================================================================================
//=====================contructur and intializer functions=========================
//=================================================================================

CombatPage::CombatPage(QWidget *parent, combat_manager* m, ironclad* plyr)
    : QWidget{parent}
    , manager(m)
    , player(plyr)
    , eve(m->get_event())
{
    tmpl = cardTemplate::common;

    //----------------------------------------------------
    combatView = new QGraphicsView(this);
    combatScene = new QGraphicsScene(this);

    combatScene->setSceneRect(0, 0, 1600, 900);
    combatView->setScene(combatScene);

    combatView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    combatView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    combatView->setFrameShape(QFrame::NoFrame);
    combatView->setStyleSheet("background: black;");

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

    bar = new CombatTopBar(eve, player);
    relic_bar = new RelicBar(eve, player->get_relic_list());

    combatScene->addItem(bg);
    combatScene->addItem(draw_pile);
    combatScene->addItem(discard_pile);
    combatScene->addItem(bar->getParent());
    combatScene->addItem(relic_bar->getParent());

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
    connect(eve, &combatEvent::potionMoved, this, &CombatPage::potion_moved);
    connect(eve, &combatEvent::potionReleased, this, &CombatPage::potion_released);
    connect(eve, &combatEvent::cardUpdated, this, &CombatPage::card_updated);
    // connect(eve, &combatEvent::entityUpdate, this, &CombatPage::entity_update);
    connect(eve, &combatEvent::entity_escape, this, &CombatPage::escape_entity);
    connect(eve, &combatEvent::entity_removed, this, &CombatPage::died_entity);
    connect(eve, &combatEvent::afterAttack, this, &CombatPage::after_attack);
    connect(eve, &combatEvent::turn_started, this, &CombatPage::turn_start);
    connect(eve, &combatEvent::resetLayout, this, [this](){
        enqueue([this](){
            reset_layout();
            QTimer::singleShot(400, [this](){playNext();});
        });
    });
    connect(eve, &combatEvent::entityRightButton, this, &CombatPage::entity_right_click);
    connect(eve, &combatEvent::potionRightButton, this, &CombatPage::potion_right_click);
    connect(eve, &combatEvent::relicRightButton, this, &CombatPage::relic_right_click);
    connect(eve, &combatEvent::powerRightButton, this, &CombatPage::power_right_click);
    connect(eve, &combatEvent::selectCard, this, &CombatPage::createSelectCard);
    connect(eve, &combatEvent::combat_ended, this, &CombatPage::createCollectReward);
    //----------------------------------------------------
}


//-------------- writed by Ai------------------
CombatPage::~CombatPage() {
    // Clean up entity corner effects
    for (auto& pair : entity_corner_effect) {
        if (pair.second) {
            delete pair.second;
            pair.second = nullptr;
        }
    }
    entity_corner_effect.clear();

    // Clean up created cards
    for (auto& pair : created_cards) {
        if (pair.second) {
            delete pair.second;
            pair.second = nullptr;
        }
    }
    created_cards.clear();

    // Clean up enemy items
    for (auto enemy : enemies) {
        if (enemy) {
            delete enemy;
            enemy = nullptr;
        }
    }
    enemies.clear();

    // Clean up player items
    for (auto player : players) {
        if (player) {
            delete player;
            player = nullptr;
        }
    }
    players.clear();

    // Clean up text items
    if (draw_pile) {
        delete draw_pile;
        draw_pile = nullptr;
    }
    if (discard_pile) {
        delete discard_pile;
        discard_pile = nullptr;
    }

    // Clean up info bar if it exists
    if (info_bar) {
        delete info_bar;
        info_bar = nullptr;
    }

    // Clean up top bar and relic bar
    if (bar) {
        delete bar;
        bar = nullptr;
    }
    if (relic_bar) {
        delete relic_bar;
        relic_bar = nullptr;
    }

    // Clean up combat view and scene
    if (combatScene) {
        // QGraphicsScene will clean up its items when deleted
        delete combatScene;
        combatScene = nullptr;
    }
    if (combatView) {
        delete combatView;
        combatView = nullptr;
    }

    // Note: manager, player, and eve are likely owned elsewhere
    // and should NOT be deleted here to avoid double deletion
    manager = nullptr;
    player = nullptr;
    eve = nullptr;

    // Clear the action queue
    while (!action_queue.empty()) {
        action_queue.pop();
    }
    queue_busy = false;
}
//-------------- writed by Ai------------------



void CombatPage::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent(event);

    if (combatView && combatScene) {
        combatView->fitInView(combatScene->sceneRect(), Qt::KeepAspectRatioByExpanding);
    }
}



void CombatPage::start_combat() {
    if (!manager) return;

    enqueue([this](){
        initialize_layout();
        QTimer::singleShot(50, [this](){playNext();});
    });
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
        auto p = new IroncladItem(eve, item, {x, 565 - getEntityVisual(item->get_ID()).size.height()}, 300);
        players.push_back(p);
        combatScene->addItem(p->getParent());
        x += getEntityVisual(item->get_ID()).size.width() + players_margine_width;
    }

    x += enemies_margine_width;
    for (auto item : manager->get_enemies())  {
        auto p = new EnemyItem(eve, item, {x, 565 - getEntityVisual(item->get_ID()).size.height()}, 200);
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
            auto p = new EnemyItem(eve, manager->get_enemies()[i], {x, 565 - getEntityVisual(manager->get_enemies()[i]->get_ID()).size.height()}, 200);
            enemies.push_back(p);
            combatScene->addItem(p->getParent());
            x += getEntityVisual(manager->get_enemies()[i]->get_ID()).size.width() + margine;
        }
    }
}

//=================================================================================
//====================queue and enqueue managment==================================
//=================================================================================

void CombatPage::enqueue(std::function<void()> fnc) {
    action_queue.push(fnc);

    if (queue_busy == false || action_queue.empty()) {
        playNext();
    }
}


void CombatPage::playNext() {
    if (action_queue.empty()){
        queue_busy = false;
    }
    else {
        queue_busy = true;
        auto fnc = action_queue.front();
        action_queue.pop();
        fnc();
    }
}

//=================================================================================
//====================characters functions & animations============================
//=================================================================================

void CombatPage::escape_entity(abstractEntity* entity) {

    //---------------------------------------------------------------------
    for (int i = 0; i < players.size(); i++) {
        if (entity == players[i]->getSource()) {

            enqueue([=](){
                players[i]->escapeAnim();
                QTimer::singleShot(100, [this](){playNext();});
            });
        }
    }
    //----------------------------------------------------------------------
    for (int i = 0; i < enemies.size(); i++) {
        if (entity == enemies[i]->getSource()) {

            enqueue([=](){
                enemies[i]->escapeAnim();
                QTimer::singleShot(100, [this](){playNext();});
            });

        }
    }
    //----------------------------------------------------------------------

}

void CombatPage::died_entity(abstractEntity* entity) {

    //---------------------------------------------------------------------
    for (int i = 0; i < players.size(); i++) {
        if (entity == players[i]->getSource()) {

            enqueue([=](){
                players[i]->dieAnim();
                QTimer::singleShot(100, [this](){playNext();});
            });

        }
    }
    //----------------------------------------------------------------------
    for (int i = 0; i < enemies.size(); i++) {
        if (entity == enemies[i]->getSource()) {

            enqueue([=](){
                enemies[i]->dieAnim();
                QTimer::singleShot(100, [this](){playNext();});
            });
        }
    }
    //----------------------------------------------------------------------
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
    enqueue([=](){
        int hand_count = player->get_hand_pile().size();

        int i;
        for (i = 0; i < hand_count; i++) {
            if (player->get_hand_pile()[i] == card) break;
        }

        created_cards[card]->getParent()->setZValue(4401 + 10 * i);
        QPointF orig = created_cards[card]->getCardpos();

        if (i == hand_count) {
            created_cards[card]->setCardpos({orig.x(), 950});
        }

        else {
            qreal x = 770 - 70 * hand_count + 140 * i;
            if (enter) {
                created_cards[card]->setCardpos({x, 950});
            }

            QTimer::singleShot(500, [=](){created_cards[card]->setCardpos({x, 700});});
        }

        QTimer::singleShot(50, [this](){playNext();});

    });

}


void CombatPage::cardMovePile(abstractCard* card, PileType from, PileType to) {


    //------------------------------------------------------------------------------------
    if (from == PileType::hand){
        setHandCardPoint(card);

        for (auto item : player->get_hand_pile()) {
            setHandCardPoint(item);
        }

    }

    //------------------------------------------------------------------------------------

    if (to == PileType::hand){
        cardAdd(card);

        for (auto item : player->get_hand_pile()) {
            setHandCardPoint(item, item == card);
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
    if (created_cards.find(card) != created_cards.end())
        created_cards[card]->updateCard();
    draw_pile->setText(QString::number(player->get_draw_pile().size()));
    discard_pile->setText(QString::number(player->get_discard_pile().size()));
    bar->updateBar();

}



//====================================================================
//======================manager slots=================================
//====================================================================


void CombatPage::card_moved(CardParent* card, const QPointF& pos) {

    switch (card->getSource()->get_target_type()) {
    //--------------------------------------------------------------------------------------------
    case TargetType::single_target: {

        for (auto item : enemies) {
            if (item->getSource()->get_hp() <= 0) continue;


            if (entity_corner_effect.find(item->getSource()) == entity_corner_effect.end()){
                auto img = item->getImage();
                entity_corner_effect[item->getSource()] = new entityCornersFrame(img->scenePos(), img->size());
                combatScene->addItem(entity_corner_effect[item->getSource()]->getParent());
            }
            if (item->getParent()->contains(item->getParent()->mapFromScene(pos))
                && entity_corner_effect[item->getSource()]->getVisisble() == false) {
                entity_corner_effect[item->getSource()]->EntranceEffect();
            }
            else if (!item->getParent()->contains(item->getParent()->mapFromScene(pos))
                     && entity_corner_effect[item->getSource()]->getVisisble() == true) {
                entity_corner_effect[item->getSource()]->ExitEffect();
            }
        }
        break;
    }
    //--------------------------------------------------------------------------------------------
    case TargetType::enemies: {
        if (pos.y() < 650) {
            for (auto item : enemies) {
                if (item->getSource()->get_hp() <= 0) continue;


                if (entity_corner_effect.find(item->getSource()) == entity_corner_effect.end()){
                    auto img = item->getImage();
                    entity_corner_effect[item->getSource()] = new entityCornersFrame(img->scenePos(), img->size());
                    combatScene->addItem(entity_corner_effect[item->getSource()]->getParent());
                }
                if (entity_corner_effect[item->getSource()]->getVisisble() == false) {
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
        if (player->get_hp() <= 0) break;

        if (pos.y() < 650) {
            for (auto item : players) {
                if (item->getSource() != player) continue;
                if (item->getSource()->get_hp() <= 0) continue;

                if (entity_corner_effect.find(item->getSource()) == entity_corner_effect.end()){
                    auto img = item->getImage();
                    entity_corner_effect[item->getSource()] = new entityCornersFrame(img->scenePos(), img->size());
                    combatScene->addItem(entity_corner_effect[item->getSource()]->getParent());
                }
                if (entity_corner_effect[item->getSource()]->getVisisble() == false) {
                    entity_corner_effect[item->getSource()]->EntranceEffect();
                }
            }
        }
        else {
            for (auto item : players) {
                if (item->getSource() != player) continue;
                if (item->getSource()->get_hp() <= 0) continue;

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

//============================================================

void CombatPage::card_released(CardParent* card, const QPointF& pos) {
    for (auto item : entity_corner_effect) {
        if (item.second->getVisisble()) item.second->ExitEffect();
    }

    if (card->getSource()->get_available() == false ||
        card->getSource()->get_turn_playable() == false ||
        card->getSource()->get_turn_lock() == true ||
        card->getSource()->get_energy() > player->get_energy() )
    {
        return;
    }

    switch (card->getSource()->get_target_type()) {
    //-----------------------------------------------------------------------------------------------
    case TargetType::single_target: {
        for (auto item : enemies) {
            if (item->getSource()->get_hp() <= 0) continue;
            if (item->getParent()->contains(item->getParent()->mapFromScene(pos))) {
                playCardInfo inf;
                inf.card = card->getSource();
                inf.owner = player;
                inf.target_list = {item->getSource()};

                game_action acts(eve);
                player->play_card(inf);
                bar->updateBar();
                for (auto item : players) item->updateEntity();
                for (auto item : enemies) item->updateEntity();

                return;
            }
        }
        break;
    }
    //-----------------------------------------------------------------------------------------------
    case TargetType::enemies: {
        if (pos.y() >= 650) break;
        playCardInfo inf;
        inf.card = card->getSource();
        inf.owner = player;
        for (auto item : enemies) {
            if (item->getSource()->get_hp() <= 0) continue;
            inf.target_list.push_back(item->getSource());
        }
        game_action acts(eve);
        player->play_card(inf);
        bar->updateBar();
        for (auto item : players) item->updateEntity();
        for (auto item : enemies) item->updateEntity();
        return;
    }
    //-----------------------------------------------------------------------------------------------
    case TargetType::self: {
        if (pos.y() >= 650) break;
        playCardInfo inf;
        inf.card = card->getSource();
        inf.owner = player;

        game_action acts(eve);
        player->play_card(inf);
        bar->updateBar();
        for (auto item : players) {
            if (item->getSource()->get_hp() <= 0) continue;
            item->updateEntity();
        }
        for (auto item : enemies) {
            if (item->getSource()->get_hp() <= 0) continue;
            item->updateEntity();
        }
        return;
    }
    default:
        return;
    }
}

//============================================================

void CombatPage::potion_moved(PotionParent* potion, const QPointF& pos) {

    switch (potion->getSource()->get_target_type()) {
    //--------------------------------------------------------------------------------------------
    case TargetType::single_target: {

        for (auto item : enemies) {
            if (item->getSource()->get_hp() <= 0) continue;


            if (entity_corner_effect.find(item->getSource()) == entity_corner_effect.end()){
                auto img = item->getImage();
                entity_corner_effect[item->getSource()] = new entityCornersFrame(img->scenePos(), img->size());
                combatScene->addItem(entity_corner_effect[item->getSource()]->getParent());
            }
            if (item->getParent()->contains(item->getParent()->mapFromScene(pos))
                && entity_corner_effect[item->getSource()]->getVisisble() == false) {
                entity_corner_effect[item->getSource()]->EntranceEffect();
            }
            else if (!item->getParent()->contains(item->getParent()->mapFromScene(pos))
                     && entity_corner_effect[item->getSource()]->getVisisble() == true) {
                entity_corner_effect[item->getSource()]->ExitEffect();
            }
        }
        break;
    }
    //--------------------------------------------------------------------------------------------
    case TargetType::enemies: {
        if (pos.x() > 600) {
            for (auto item : enemies) {
                if (item->getSource()->get_hp() <= 0) continue;


                if (entity_corner_effect.find(item->getSource()) == entity_corner_effect.end()){
                    auto img = item->getImage();
                    entity_corner_effect[item->getSource()] = new entityCornersFrame(img->scenePos(), img->size());
                    combatScene->addItem(entity_corner_effect[item->getSource()]->getParent());
                }
                if (entity_corner_effect[item->getSource()]->getVisisble() == false) {
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
        if (player->get_hp() <= 0) break;

        for (auto item : players) {
            if (item->getParent()->contains(item->getParent()->mapFromScene(pos))
                && item->getSource() == player) {

                if (item->getSource()->get_hp() <= 0) continue;

                if (entity_corner_effect.find(item->getSource()) == entity_corner_effect.end()){
                    auto img = item->getImage();
                    entity_corner_effect[item->getSource()] = new entityCornersFrame(img->scenePos(), img->size());
                    combatScene->addItem(entity_corner_effect[item->getSource()]->getParent());
                }
                if (entity_corner_effect[item->getSource()]->getVisisble() == false) {
                    entity_corner_effect[item->getSource()]->EntranceEffect();
                }
            }

            else {
                if (item->getSource() != player) continue;
                if (item->getSource()->get_hp() <= 0) continue;

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

//============================================================

void CombatPage::potion_released(PotionParent* potion, const QPointF& pos) {
    for (auto item : entity_corner_effect) {
        if (item.second->getVisisble()) item.second->ExitEffect();
    }

    if (potion->getSource()->playable() == false)
    {
        return;
    }

    switch (potion->getSource()->get_target_type()) {
    //-----------------------------------------------------------------------------------------------
    case TargetType::single_target: {
        for (auto item : enemies) {
            if (item->getSource()->get_hp() <= 0) continue;
            if (item->getParent()->contains(item->getParent()->mapFromScene(pos))) {
                drinkPotionInfo inf;
                inf.potion = potion->getSource();
                inf.owner = player;
                inf.target_list = {item->getSource()};

                game_action acts(eve);
                player->drink_potion(inf);
                bar->updateBar();
                for (auto item : players) item->updateEntity();
                for (auto item : enemies) item->updateEntity();

                return;
            }
        }
        break;
    }
    //-----------------------------------------------------------------------------------------------
    case TargetType::enemies: {
        if (pos.x() <= 600) break;
        drinkPotionInfo inf;
        inf.potion = potion->getSource();
        inf.owner = player;
        for (auto item : enemies) {
            if (item->getSource()->get_hp() <= 0) continue;
            inf.target_list.push_back(item->getSource());
        }
        game_action acts(eve);
        player->drink_potion(inf);
        bar->updateBar();
        for (auto item : players) item->updateEntity();
        for (auto item : enemies) item->updateEntity();
        return;
    }
    //-----------------------------------------------------------------------------------------------
    case TargetType::self: {
        for (auto item : players) {
            if (item->getParent()->contains(item->getParent()->mapFromScene(pos))
                && item->getSource() == player) {
                drinkPotionInfo inf;
                inf.potion = potion->getSource();
                inf.owner = player;

                game_action acts(eve);
                player->drink_potion(inf);
                bar->updateBar();
                for (auto item : players) {
                    if (item->getSource()->get_hp() <= 0) continue;
                    item->updateEntity();
                }
                for (auto item : enemies) {
                    if (item->getSource()->get_hp() <= 0) continue;
                    item->updateEntity();
                }
            }
        }
        return;
    }
    default:
        return;
    }
}

//============================================================

void CombatPage::card_updated(abstractCard* card) {
    if (created_cards.find(card) != created_cards.end()){
        created_cards[card]->updateCard();
    }
}


void CombatPage::entity_update(abstractEntity* entity) {

    bar->updateBar();
    for (auto item : players){
        if (item->getSource() == entity) item->updateEntity();
    }
    for (auto item : enemies){
        if (item->getSource() == entity) item->updateEntity();
    }
}


void CombatPage::after_attack(attackResult& res) {

    //===========attack effect & anim=================
    for (auto enmy : enemies){
        if (enmy->getSource() == res.info.attacker) {
            enqueue([=]{
                enmy->getParent()->activeAttackAnimation();
                bar->updateBar();
                enmy->updateEntity();
                QTimer::singleShot(200, [this](){playNext();});
            });
        }
    }
    for (auto plyr : players){
        if (plyr->getSource() == res.info.attacker){
            enqueue([=]{
                plyr->getParent()->activeAttackAnimation();
                plyr->updateEntity();
                QTimer::singleShot(200, [this](){playNext();});
            });
        }
    }

    //===========damage effect & anim=================
    for (auto item : res.results) {
        //----------------------------------------------------------------------------------------
        for (auto enmy : enemies){


            if (item.target == enmy->getSource()) {
                if (item.target->get_hp() == 0) continue;

                auto img = enmy->getImage();
                auto eff = new damageEffect(res.info.card_id, img->scenePos(), img->size());
                combatScene->addItem(eff->getParent());

                qreal prt_x = img->scenePos().x() + img->size().width()/2;
                qreal prt_y = img->scenePos().y() + img->size().height()/2;

                enqueue([=](){
                    eff->EntranceEffect();
                    DamageParticleManager::spawn(combatScene, QPointF(prt_x, prt_y));
                    QTimer::singleShot(1, [this](){playNext();});
                    bar->updateBar();
                    enmy->updateEntity();
                    QTimer::singleShot(5000, [=](){
                        delete eff;
                    });
                });
            }

        }
        //----------------------------------------------------------------------------------------
        for (auto plyr : players){


            if (item.target == plyr->getSource()) {
                if (item.target->get_hp() == 0) continue;

                auto img = plyr->getImage();
                auto atckr = entityID::NULLENTITY;
                if (res.info.attacker) atckr = res.info.attacker->get_ID();

                auto eff = new damageEffect(atckr, img->scenePos(), img->size());
                combatScene->addItem(eff->getParent());

                qreal prt_x = img->scenePos().x() + img->size().width()/2;
                qreal prt_y = img->scenePos().y() + img->size().height()/2;

                enqueue([=](){
                    eff->EntranceEffect();
                    DamageParticleManager::spawn(combatScene, QPointF(prt_x, prt_y));
                    QTimer::singleShot(1, [this](){playNext();});
                    bar->updateBar();
                    plyr->updateEntity();
                    QTimer::singleShot(5000, [=](){
                        delete eff;
                    });
                });

            }
        }
        //----------------------------------------------------------------------------------------
        enqueue([=](){
            QTimer::singleShot(100, [this](){playNext();});
        });
    }

    bar->updateBar();
}


void CombatPage::turn_start(abstractEntity*) {
    for (auto item : created_cards) item.second->updateCard();
    bar->updateBar();
    for (auto item : players) item->updateEntity();
    for (auto item : enemies) item->updateEntity();
    enqueue([this](){
        QTimer::singleShot(600, [this](){playNext();});
    });
}
//==========================================================

void CombatPage::entity_right_click(abstractEntity* ent) {
    info_bar = new CombatInfoBar(ent);
    combatScene->addItem(info_bar->getParent());
    info_bar->Entrance();
}

void CombatPage::potion_right_click(abstractPotion* ent) {
    info_bar = new CombatInfoBar(ent);
    combatScene->addItem(info_bar->getParent());
    info_bar->Entrance();
}

void CombatPage::relic_right_click(abstractRelic* ent) {
    info_bar = new CombatInfoBar(ent);
    combatScene->addItem(info_bar->getParent());
    info_bar->Entrance();
}

void CombatPage::power_right_click(abstractPower* ent) {
    info_bar = new CombatInfoBar(ent);
    combatScene->addItem(info_bar->getParent());
    info_bar->Entrance();
}

void CombatPage::createSelectCard(std::vector<abstractCard*> cards) {
    auto sc = new selectCard(eve, cards);
    combatScene->addItem(sc->getParent());
    for (auto item : sc->getCards()){
        combatScene->addItem(item->getParent());
    }
}

void CombatPage::createCollectReward(combat_manager* mngr, bool vic){
    if (vic && manager->get_rewards().find(player) != manager->get_rewards().end()) {
        QTimer::singleShot(1000, [=]() {
            enqueue([=](){
                auto cr = new collectReward(eve, manager->get_rewards()[player], player);
                combatScene->addItem(cr->getParent());
            });
        });
    }
}