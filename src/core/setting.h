#ifndef SETTING_H
#define SETTING_H

#include <QString>

enum class language{
    English,
    Persian
};

struct setting {
    inline static language game_language = language::English;
};


namespace Fonts {
inline QString Cascadia;
inline QString koodak;
}
#endif // SETTING_H
