#include "enemyfactory.h"

// Regular Enemies
#include "cultist.h"
#include "jaw_worm.h"
#include "red_louse.h"
#include "green_louse.h"
#include "small_slime.h"
#include "medium_slime.h"
#include "large_slime.h"
#include "looter.h"
#include "mugger.h"
#include "blue_slaver.h"
#include "red_slaver.h"
#include "spheric_guardian.h"

// Elites
#include "gremlin_nob.h"
#include "sentry.h"
#include "book_of_stabbing.h"
#include "taskmaster.h"

// Bosses
#include "slime_boss.h"
#include "hexaghost.h"
#include "the_champ.h"

abstractEnemy* enemyFactory::createEnemy(entityID id, game_action& actions, bool middle)
{
    switch (id)
    {
    // Regular Enemies
    case entityID::cultist:          return cultist::create(actions);
    case entityID::jaw_worm:         return jaw_worm::create(actions);
    case entityID::red_louse:        return red_louse::create(actions);
    case entityID::green_louse:      return green_louse::create(actions);
    case entityID::small_slime:      return small_slime::create(actions);
    case entityID::medium_slime:     return medium_slime::create(actions);
    case entityID::large_slime:      return large_slime::create(actions);
    case entityID::looter:           return looter::create(actions);
    case entityID::mugger:           return mugger::create(actions);
    case entityID::blue_slaver:      return blue_slaver::create(actions);
    case entityID::red_slaver:       return red_slaver::create(actions);
    case entityID::spheric_guardian: return spheric_guardian::create(actions);

    // Elites
    case entityID::gremlin_nob:      return gremlin_nob::create(actions);
    case entityID::sentry:           return sentry::create(actions, middle);
    case entityID::book_of_stabbing: return book_of_stabbing::create(actions);
    case entityID::taskmaster:       return taskmaster::create(actions);

    // Bosses
    case entityID::slime_boss:       return slime_boss::create(actions);
    case entityID::hexaghost:        return hexaghost::create(actions);
    case entityID::the_champ:        return the_champ::create(actions);

    default:
        return nullptr;
    }
}