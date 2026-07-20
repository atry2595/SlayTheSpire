#include "cultist.h"
#include "items/powers/powerfactory.h"

cultist::cultist(QString name_init, int base_max_hp_init)
    :abstractEnemy(name_init, base_max_hp_init)
{}


cultist* cultist::create(game_action& actions){

    QString name = tr("Cultist");

    RNG& rng = RNG::instance();
    int hp = rng.randint(48, 54);

    cultist* enemy = new cultist(name, hp);

    enemy_intent intnt1;
    intnt1.name = tr("Incantation");
    intnt1.type = intent_type::buff;

    enemy_intent intnt2;
    intnt2.name = tr("Dark Strike");
    intnt2.type = intent_type::attack;
    intnt2.damage = 6;

    enemy->intent_list[(int)cultist_move::incantation] = intnt1;
    enemy->intent_list[(int)cultist_move::dark_strike] = intnt2;

    enemy->current_move = (int)cultist_move::incantation;

    return enemy;
}



void cultist::choose_move() {
    current_move = (int)cultist_move::dark_strike;
}



void cultist::play_turn(playInfo& info){

    switch((cultist_move)current_move){


    case (cultist_move::incantation):{
        int effect_number = 3;

        abstractPower* np = PowerFactory::createPower(powerID::ritual, info.attacker, effect_number);
        info.attacker->add_power(info.actions, np);
        break;
    }



    case (cultist_move::dark_strike): {

        perform_attack(info);

        break;
    }

    }

    enemy_turn++;
    choose_move();
}

QString cultist::get_story() {
    return (QObject::tr("The Cultist lifts his beak to the Spire’s sky and chants the sacred caw.\nWith every cry, tendrils of dark power root deeper into his soul, whispering promises of a blazing ascension."));
}
