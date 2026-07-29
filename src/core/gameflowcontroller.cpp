#include "gameflowcontroller.h"
#include <QVBoxLayout>
#include "entity/abstractenemy.h"
#include "entity/enemyfactory.h"
#include "utils/RNG.h"
#include "events/unknownfactory.h"

std::vector<std::vector<entityID>> GameFlowController::easy_pool_1 = {
    {entityID::cultist}, {entityID::jaw_worm},
    {entityID::green_louse, entityID::red_louse},
    {entityID::small_slime, entityID::medium_slime}
};

std::vector<std::vector<entityID>> GameFlowController::easy_pool_2 = {
    {entityID::spheric_guardian},
    {entityID::blue_slaver, entityID::small_slime},
    {entityID::looter, entityID::mugger}
};

std::vector<std::vector<entityID>> GameFlowController::hard_pool_1 = {
    {entityID::large_slime},
    {entityID::small_slime, entityID::small_slime, entityID::small_slime, entityID::small_slime},
    {entityID::blue_slaver},
    {entityID::red_slaver},
    {entityID::green_louse, entityID::red_louse, entityID::green_louse},
    {entityID::cultist, entityID::small_slime},
    {entityID::red_slaver, entityID::red_louse},
    {entityID::looter, entityID::green_louse},
    {entityID::looter},
    {entityID::jaw_worm, entityID::medium_slime}
};

std::vector<std::vector<entityID>> GameFlowController::hard_pool_2 = {
    {entityID::red_slaver, entityID::jaw_worm},
    {entityID::cultist, entityID::medium_slime},
    {entityID::sentry, entityID::spheric_guardian},
    {entityID::cultist, entityID::cultist, entityID::cultist},
    {entityID::red_louse, entityID::green_louse, entityID::spheric_guardian},
    {entityID::blue_slaver, entityID::jaw_worm},
    {entityID::cultist, entityID::spheric_guardian},
    {entityID::cultist, entityID::sentry}
};

std::vector<std::vector<entityID>> GameFlowController::elite_pool_1 = {
    {entityID::gremlin_nob},
    {entityID::sentry, entityID::sentry, entityID::sentry}
};

std::vector<std::vector<entityID>> GameFlowController::elite_pool_2 = {
    {entityID::blue_slaver, entityID::taskmaster, entityID::red_slaver},
    {entityID::book_of_stabbing}
};

std::vector<std::vector<entityID>> GameFlowController::boss_pool_1 = {
    {entityID::slime_boss},
    {entityID::hexaghost}
};
std::vector<std::vector<entityID>> GameFlowController::boss_pool_2 = {
    {entityID::the_champ}
};

std::vector<unknownID> GameFlowController::unknown_pool_1 = {
    unknownID::ominous_forge, unknownID::golden_idol,
    unknownID::bonfire_spirits, unknownID::golden_shrine,
    unknownID::lab, unknownID::the_cleric,
    unknownID::shining_light, unknownID::the_ssssssserpant
};

std::vector<unknownID> GameFlowController::unknown_pool_2 = {
    unknownID::ominous_forge, unknownID::augmenter,
    unknownID::bonfire_spirits, unknownID::golden_shrine,
    unknownID::lab, unknownID::face_trader,
    unknownID::ancient_writing, unknownID::pleading_vagrant,
    unknownID::the_joust
};

GameFlowController::GameFlowController(Player* plyr, QWidget *parent)
    :QWidget(parent)
    ,player(plyr)
{
    eve = new combatEvent();
    actions = new game_action(eve);
    character = new ironclad(eve);
    state = new Stats();
    stack = new QStackedWidget(this);

    auto* layout = new QVBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);
    layout->addWidget(stack);
    setLayout(layout);

    connect(eve, &combatEvent::nextAction, this, &GameFlowController::onNextAction);
}

void GameFlowController::start() {
    goToStartingSelect();
}

void GameFlowController::goToStartingSelect()
{
    if (!starting) {
        starting = new startingSelect(this, eve);
        stack->addWidget(starting);
    }
    stack->setCurrentWidget(starting);
}

void GameFlowController::goToMap()
{
    if (!mapPage) {
        mapPage = new MapPage(this, character, eve);
        stack->addWidget(mapPage);
    }
    else {
        connect(eve, &combatEvent::settingOpen, mapPage, &MapPage::open_setting, Qt::UniqueConnection);
        connect(eve, &combatEvent::relicRightButton, mapPage, &MapPage::relic_right_click, Qt::UniqueConnection);
    }
    stack->setCurrentWidget(mapPage);
}

std::vector<abstractEnemy*> GameFlowController::buildEnemies(const std::vector<std::vector<entityID>>& pool)
{
    std::vector<abstractEnemy*> enemies;
    auto cp = pool;
    auto selected = RNG::instance().choice(cp);
    if (selected == std::vector<entityID>{entityID::sentry, entityID::sentry, entityID::sentry}) {
        for (int i = 0; i<3; i++){
            enemies.push_back(enemyFactory::createEnemy(selected[i], *actions, i%2));
        }
    }
    else {
        for (auto item : selected) {
            enemies.push_back(enemyFactory::createEnemy(item, *actions));
        }
    }
    return enemies;
}

void GameFlowController::onNextAction()
{
    QWidget* current = stack->currentWidget();

    if (qobject_cast<MapPage*>(current)) {
        disconnect(eve, &combatEvent::settingOpen, mapPage, &MapPage::open_setting);
        disconnect(eve, &combatEvent::relicRightButton, mapPage, &MapPage::relic_right_click);
    }
    if (qobject_cast<MapPage*>(current)) {
        switch (combat_data::room_type) {
        case RoomType::BOSS:     goToBoss();      return;
        case RoomType::ELITE:    goToElite();     return;
        case RoomType::MERCHANT: goToMertchant(); return;
        case RoomType::MONSTER:  goToMons();      return;
        case RoomType::REST:     goToRest();      return;
        case RoomType::TREASURE: goToTreasure();  return;
        case RoomType::UNKNOWN:  goToUnknown();   return;
        }
        return;
    }

    leaveCurrentPageAndReturnToMap();
}

void GameFlowController::leaveCurrentPageAndReturnToMap()
{
    QWidget* current = stack->currentWidget();

    if (auto* page = qobject_cast<startingSelect*>(current)) {
        stack->removeWidget(page);
        page->deleteLater();
        starting = nullptr;
    }
    else if (auto* page = qobject_cast<CombatPage*>(current)) {
        stack->removeWidget(page);
        page->Delete();
        combatPage = nullptr;
        if (combat_data::room_type == RoomType::BOSS) {
            goToTreasure();
            return;
        }
    }
    else if (auto* page = qobject_cast<RestPage*>(current)) {
        stack->removeWidget(page);
        page->Delete();
        restPage = nullptr;
    }
    else if (auto* page = qobject_cast<StorePage*>(current)) {
        stack->removeWidget(page);
        page->Delete();
        storePage = nullptr;
    }
    else if (auto* page = qobject_cast<TreasurePage*>(current)) {
        stack->removeWidget(page);
        page->Delete();
        treasurePage = nullptr;

        if (combat_data::room_type == RoomType::BOSS) {
            if (combat_data::act == 1) {
                combat_data::act = 2;
                if (mapPage) {
                    stack->removeWidget(mapPage);
                    mapPage->Delete();
                    mapPage = nullptr;
                }
                goToMap();
            }
            else {
                emit eve->game_win();
            }
            return;
        }
    }
    else if (auto* page = qobject_cast<UnknownPage*>(current)) {
        stack->removeWidget(page);
        page->Delete();
        unknownPage = nullptr;
    }

    goToMap();
}

void GameFlowController::goToMons() {
    std::vector<abstractEnemy*> enemies;

    if (combat_data::act == 1) {
        if (combat_data::floor <= 3) {
            auto selected = easy_pool_1[combat_data::floor%2];
            for (auto item : selected){
                enemies.push_back(enemyFactory::createEnemy(item, *actions));
            }
        }
        else {
            auto selected = RNG::instance().choice(hard_pool_1);
            for (auto item : selected){
                enemies.push_back(enemyFactory::createEnemy(item, *actions));
            }
        }
    }
    //-------------
    else {
        if (combat_data::floor <= 3) {
            auto selected = easy_pool_2[combat_data::floor%2];
            for (auto item : selected){
                enemies.push_back(enemyFactory::createEnemy(item, *actions));
            }
        }
        else {
            auto selected = RNG::instance().choice(hard_pool_2);
            for (auto item : selected){
                enemies.push_back(enemyFactory::createEnemy(item, *actions));
            }
        }
    }

    combat_manager* mngr = new combat_manager({character}, enemies, CombatType::monster, eve);
    combatPage = new CombatPage(this, mngr, character);
    stack->addWidget(combatPage);
    stack->setCurrentWidget(combatPage);
}

void GameFlowController::goToElite() {
    auto& pool = (combat_data::act == 1) ? (elite_pool_1) : (elite_pool_2);
    auto enemies = buildEnemies(pool);

    combat_manager* mngr = new combat_manager({character}, enemies, CombatType::elite, eve);
    combatPage = new CombatPage(this, mngr, character);
    stack->addWidget(combatPage);
    stack->setCurrentWidget(combatPage);
}

void GameFlowController::goToBoss() {
    auto& pool = (combat_data::act == 1) ? boss_pool_1 : boss_pool_2;
    auto enemies = buildEnemies(pool);

    combat_manager* mngr = new combat_manager({character}, enemies, CombatType::boss, eve);
    combatPage = new CombatPage(this, mngr, character);
    stack->addWidget(combatPage);
    stack->setCurrentWidget(combatPage);
}

void GameFlowController::goToRest() {
    restPage = new RestPage(this, character, eve);
    stack->addWidget(restPage);
    stack->setCurrentWidget(restPage);
}

void GameFlowController::goToTreasure() {
    if (combat_data::room_type == RoomType::TREASURE ) {
        treasurePage = new TreasurePage(this, ChestType::regular, character, eve);
    }
    else if (combat_data::room_type == RoomType::BOSS ) {
        treasurePage = new TreasurePage(this, ChestType::boss, character, eve);
    }
    stack->addWidget(treasurePage);
    stack->setCurrentWidget(treasurePage);
}

void GameFlowController::goToMertchant() {
    storePage = new StorePage(this, character, eve);
    stack->addWidget(storePage);
    stack->setCurrentWidget(storePage);
}

void GameFlowController::goToUnknown() {
    auto& pool = (combat_data::act == 1) ? unknown_pool_1 : unknown_pool_2;
    auto cp = pool;
    unknownID selected = RNG::instance().choice(cp);
    UnknownManager manager = unknownFactory::createUnknown(selected, *actions, character);
    unknownPage = new UnknownPage(manager, this, character, eve);

    stack->addWidget(unknownPage);
    stack->setCurrentWidget(unknownPage);
}