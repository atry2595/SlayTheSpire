#ifndef GAMEFLOWCONTROLLER_H
#define GAMEFLOWCONTROLLER_H

#include <QWidget>
#include "entity/ironclad.h"
#include <QStackedWidget>
#include "ui/selectItem/startingselect.h"
#include "ui/mappage/mappage.h"
#include "ui/combatpage.h"
#include "ui/restpage/restpage.h"
#include "ui/store/storepage.h"
#include "ui/treasure/treasurepage.h"
#include "ui/unknownpage/unknownpage.h"

class GameFlowController : public QWidget
{
    Q_OBJECT
public:
    explicit GameFlowController(Player* plyr, QWidget *parent = nullptr);
    void start();

signals:
    void exitToMainMenu();

private:
    static std::vector<std::vector<entityID>> easy_pool_1;
    static std::vector<std::vector<entityID>> easy_pool_2;
    static std::vector<std::vector<entityID>> hard_pool_1;
    static std::vector<std::vector<entityID>> hard_pool_2;
    static std::vector<std::vector<entityID>> elite_pool_1;
    static std::vector<std::vector<entityID>> elite_pool_2;
    static std::vector<std::vector<entityID>> boss_pool_1;
    static std::vector<std::vector<entityID>> boss_pool_2;

    static std::vector<unknownID> unknown_pool_1;
    static std::vector<unknownID> unknown_pool_2;

    void goToMons();
    void goToElite();
    void goToBoss();
    void goToRest();
    void goToTreasure();
    void goToMertchant();
    void goToUnknown();

    std::vector<abstractEnemy*> buildEnemies(const std::vector<std::vector<entityID>>& pool);

    combatEvent* eve;
    game_action* actions;
    ironclad* character;
    Stats* state;
    Player* player;

    QStackedWidget* stack;
    startingSelect* starting = nullptr;
    MapPage* mapPage = nullptr;
    CombatPage* combatPage = nullptr;
    RestPage* restPage = nullptr;
    StorePage* storePage = nullptr;
    TreasurePage* treasurePage = nullptr;
    UnknownPage* unknownPage = nullptr;

    void goToStartingSelect();
    void goToMap();

    void leaveCurrentPageAndReturnToMap();

private slots:
    void onNextAction();
};

#endif // GAMEFLOWCONTROLLER_H