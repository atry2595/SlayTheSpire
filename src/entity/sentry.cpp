#include "sentry.h"
#include "cards/cardfactory.h"
#include "entity/ironclad.h"

sentry::sentry(QString name_init, int base_max_hp_init)
    :abstractEnemy(name_init, base_max_hp_init)
{}


sentry* sentry::create(game_action& actions, bool is_middle){

    QString name = tr("Sentry");

    RNG& rng = RNG::instance();
    int hp = rng.randint(38, 42);

    sentry* enemy = new sentry(name, hp);

    enemy_intent intnt1;
    intnt1.name = tr("Bolt");
    intnt1.type = intent_type::debuff;

    enemy_intent intnt2;
    intnt2.name = tr("Beam");
    intnt2.type = intent_type::attack;
    intnt2.damage = 9;

    enemy->intent_list[(int)sentry_move::bolt] = intnt1;
    enemy->intent_list[(int)sentry_move::beam] = intnt2;

    if (is_middle) enemy->current_move = (int)sentry_move::beam;
    else enemy->current_move = (int)sentry_move::bolt;

    return enemy;
}



void sentry::choose_move() {


        if (current_move == (int)sentry_move::beam) {
            current_move = (int)sentry_move::bolt;
        }
        else {
            current_move = (int)sentry_move::beam;
        }


}



void sentry::play_turn(playInfo& info){

    switch((sentry_move)current_move){


    case (sentry_move::bolt):{

        int card_count = 2;

        for (auto item : info.target_list) {
            abstractCard* nc1 = CardFactory::createCard(cardID::dazed);
            abstractCard* nc2 = CardFactory::createCard(cardID::dazed);
            ironclad* player = dynamic_cast<ironclad*>(item);
            if (!player) continue;
            player->discard_pile_add(nc1, true);
            player->discard_pile_add(nc2, true);
        }

        break;
    }


    case (sentry_move::beam): {


        perform_attack(info);


        break;
    }

    }

    enemy_turn++;
    choose_move();
}

QString sentry::get_story() {
    return (QObject::tr("The Sentry stands among its two kin, its sensor eyes spinning ceaselessly between attack and defense.\nIt never knows that this endless algorithmic dance is merely its escape from the inner void, in the Spire's absolute silence."));
}
