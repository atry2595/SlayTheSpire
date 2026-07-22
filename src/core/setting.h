#ifndef SETTING_H
#define SETTING_H

#include <QString>

enum class language{
    English,
    Persian
};

enum class characters {
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
};

struct combat_data {
    inline static int floor = 0;
    inline static int player_count = 1;
    inline static characters selected_character = characters::ironclad;
    inline static cardTemplates selected_card_template = cardTemplates::common;
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
