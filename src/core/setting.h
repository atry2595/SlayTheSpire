#ifndef SETTING_H
#define SETTING_H

#include <QString>
#include <map>
#include "core/login/player.h"
#include "ui/mappage/mapItems.h"
#include "categories/general.h"

enum class language{
    English,
    Persian
};

enum class skins {
    ironclad,
    armoured_ironclad,
    neon_ironclad,
    ancient_ironclad,
    cyberpunk_ironclad
};

enum class cardTemplates {
    common,
    ancient,
    metallic,
    toxic_blossom
};



struct setting {
    inline static language game_language = language::English;
    inline static qreal bg_volume = 0.5;
    inline static qreal sfx_volume = 0.5;
    inline static Player* current_player = nullptr;
};

struct combatMap {
    Map* map = nullptr;
    std::map<Room, RoomItem> rooms = {};
    std::vector<LineItem> lines = {};

    int currentFloor = -1;
    int currentCol = -1;
};

struct combat_data {
    inline static int act = 1;
    inline static int floor = 1;
    inline static int player_count = 1;
    inline static skins selected_character = skins::ironclad;
    inline static cardTemplates selected_card_template = cardTemplates::common;
    inline static RoomType room_type = RoomType::MONSTER;
    inline static combatMap combat_map;
};


namespace Fonts {
inline QString Cascadia;
inline QString koodak;
inline QString titrZ;
inline QString rock;
inline QString cinema;
inline QString lotrance;
inline QString ebhaar;
inline QString forte;
}
#endif // SETTING_H
