#ifndef GETVISUALDATA_H
#define GETVISUALDATA_H

#include "categories/enemies.h"
#include <QSizeF>

enum class EntityAnimType
{
    Humanoid,
    Slime,
    Louse,
    Floating,
    Book
};

struct EntityVisualData
{
    QSizeF size;
    EntityAnimType anim;
};

inline EntityVisualData getEntityVisual(entityID id)
{
    switch (id)
    {

    case entityID::ironclad:
        return {{300,214}, EntityAnimType::Humanoid};

    case entityID::blue_slaver:
        return {{254,214}, EntityAnimType::Humanoid};

    case entityID::red_slaver:
        return {{264,214}, EntityAnimType::Humanoid};

    case entityID::cultist:
        return {{225,229}, EntityAnimType::Humanoid};

    case entityID::mugger:
        return {{171,214}, EntityAnimType::Humanoid};

    case entityID::looter:
        return {{129,214}, EntityAnimType::Humanoid};

    case entityID::taskmaster:
        return {{212,250}, EntityAnimType::Humanoid};

    case entityID::the_champ:
        return {{300,320}, EntityAnimType::Humanoid};

    case entityID::gremlin_nob:
        return {{294,326}, EntityAnimType::Humanoid};

    case entityID::jaw_worm:
        return {{300,157}, EntityAnimType::Humanoid};

    case entityID::small_slime:
        return {{105,68}, EntityAnimType::Slime};

    case entityID::medium_slime:
        return {{166,103}, EntityAnimType::Slime};

    case entityID::large_slime:
        return {{300,145}, EntityAnimType::Slime};

    case entityID::slime_boss:
        return {{350,278}, EntityAnimType::Slime};

    case entityID::red_louse:
        return {{166,109}, EntityAnimType::Louse};

    case entityID::green_louse:
        return {{166,92}, EntityAnimType::Louse};

    case entityID::book_of_stabbing:
        return {{302,355}, EntityAnimType::Book};

    case entityID::hexaghost:
        return {{335,330}, EntityAnimType::Floating};

    case entityID::spheric_guardian:
        return {{225,245}, EntityAnimType::Floating};

    case entityID::sentry:
        return {{129,336}, EntityAnimType::Floating};

    default:
        return {{200,200}, EntityAnimType::Humanoid};
    }
}

#endif // GETVISUALDATA_H
