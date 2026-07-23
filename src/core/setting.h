#ifndef SETTING_H
#define SETTING_H

#include <QString>

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


enum class RoomType{
    MONSTER,
    ELITE,
    REST,
    MERCHANT,
    TREASURE,
    UNKNOWN,
    BOSS
};

struct setting {
    inline static language game_language = language::English;
};

struct combat_data {
    inline static int act = 1;
    inline static int floor = 1;
    inline static int player_count = 1;
    inline static skins selected_character = skins::ironclad;
    inline static cardTemplates selected_card_template = cardTemplates::common;
    inline static RoomType room_type = RoomType::MONSTER;
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
