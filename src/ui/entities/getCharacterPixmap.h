#ifndef GETCHARACTERPIXMAP_H
#define GETCHARACTERPIXMAP_H

#include <QPixmap>
#include "categories/enemies.h"

inline QPixmap getCharacterPixmap(entityID id)
{
    switch (id)
    {
    case entityID::cultist:
        return QPixmap(":/image/characters/cultist.png");

    case entityID::jaw_worm:
        return QPixmap(":/image/characters/jaw_worm.png");

    case entityID::red_louse:
        return QPixmap(":/image/characters/red_louse.png");

    case entityID::green_louse:
        return QPixmap(":/image/characters/green_louse.png");

    case entityID::small_slime:
        return QPixmap(":/image/characters/small_slime.png");

    case entityID::medium_slime:
        return QPixmap(":/image/characters/medium_slime.png");

    case entityID::large_slime:
        return QPixmap(":/image/characters/large_slime.png");

    case entityID::looter:
        return QPixmap(":/image/characters/looter.png");

    case entityID::mugger:
        return QPixmap(":/image/characters/mugger.png");

    case entityID::blue_slaver:
        return QPixmap(":/image/characters/blue_slaver.png");

    case entityID::red_slaver:
        return QPixmap(":/image/characters/red_slaver.png");

    case entityID::spheric_guardian:
        return QPixmap(":/image/characters/spheric_guardian.png");

    case entityID::gremlin_nob:
        return QPixmap(":/image/characters/gremlin_nob.png");

    case entityID::sentry:
        return QPixmap(":/image/characters/sentry.png");

    case entityID::book_of_stabbing:
        return QPixmap(":/image/characters/book_of_stabbing.png");

    case entityID::taskmaster:
        return QPixmap(":/image/characters/taskmaster.png");

    case entityID::slime_boss:
        return QPixmap(":/image/characters/king_slime.png");

    case entityID::hexaghost:
        return QPixmap(":/image/characters/hexaghost.png");

    case entityID::the_champ:
        return QPixmap(":/image/characters/the_champ.png");

    default:
    return QPixmap();
    }
}


inline QPixmap getCharacter1x1Image(entityID id)
{
    switch (id)
    {
    case entityID::cultist:
        return QPixmap(":/image/characters/cultist.png");

    case entityID::jaw_worm:
        return QPixmap(":/image/characters/1x1/jaw_worm.png");

    case entityID::red_louse:
        return QPixmap(":/image/characters/1x1/red_louse.png");

    case entityID::green_louse:
        return QPixmap(":/image/characters/1x1/green_louse.png");

    case entityID::small_slime:
        return QPixmap(":/image/characters/1x1/small_slime.png");

    case entityID::medium_slime:
        return QPixmap(":/image/characters/1x1/medium_slime.png");

    case entityID::large_slime:
        return QPixmap(":/image/characters/1x1/large_slime.png");

    case entityID::looter:
        return QPixmap(":/image/characters/1x1/looter.png");

    case entityID::mugger:
        return QPixmap(":/image/characters/1x1/mugger.png");

    case entityID::blue_slaver:
        return QPixmap(":/image/characters/1x1/blue_slaver.png");

    case entityID::red_slaver:
        return QPixmap(":/image/characters/1x1/red_slaver.png");

    case entityID::spheric_guardian:
        return QPixmap(":/image/characters/1x1/spheric_guardian.png");

    case entityID::gremlin_nob:
        return QPixmap(":/image/characters/1x1/gremlin_nob.png");

    case entityID::sentry:
        return QPixmap(":/image/characters/1x1/sentry.png");

    case entityID::book_of_stabbing:
        return QPixmap(":/image/characters/1x1/book_of_stabbing.png");

    case entityID::taskmaster:
        return QPixmap(":/image/characters/1x1/taskmaster.png");

    case entityID::slime_boss:
        return QPixmap(":/image/characters/1x1/king_slime.png");

    case entityID::hexaghost:
        return QPixmap(":/image/characters/1x1/hexaghost.png");

    case entityID::the_champ:
        return QPixmap(":/image/characters/1x1/the_champ.png");

    case entityID::ironclad:
        return QPixmap(":/image/characters/1x1/ironclad1.png");

    default:
        return QPixmap();
    }
}
#endif // GETCHARACTERPIXMAP_H
