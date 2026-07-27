#include "gremlin_nob.h"
#include "items/powers/powerfactory.h"

gremlin_nob::gremlin_nob(QString name_init, int base_max_hp_init)
    :abstractEnemy(name_init, base_max_hp_init)
{}


gremlin_nob* gremlin_nob::create(game_action& actions){

    QString name = tr("Gremlin Nob");

    RNG& rng = RNG::instance();
    int hp = rng.randint(82, 86);

    gremlin_nob* enemy = new gremlin_nob(name, hp);

    enemy_intent intnt1;
    intnt1.name = tr("Bellow");
    intnt1.type = intent_type::buff;

    enemy_intent intnt2;
    intnt2.name = tr("Skull Bash");
    intnt2.type = intent_type::attack_debuff;
    intnt2.damage = 8;

    enemy_intent intnt3;
    intnt3.name = tr("Bull Rush");
    intnt3.type = intent_type::attack;
    intnt3.damage = 14;


    enemy->intent_list[(int)gremlin_nob_move::bellow] = intnt1;
    enemy->intent_list[(int)gremlin_nob_move::skull_bash] = intnt2;
    enemy->intent_list[(int)gremlin_nob_move::bull_rush] = intnt3;

    enemy->current_move = (int)gremlin_nob_move::bellow;

    return enemy;
}



void gremlin_nob::choose_move() {
    RNG& rng = RNG::instance();

    int tmp = current_move;


        if (current_move == last_move && current_move == (int)gremlin_nob_move::bull_rush) {
            current_move = (int)gremlin_nob_move::skull_bash;
        }
        else {
            if (rng.chance(0.67)) current_move = (int)gremlin_nob_move::bull_rush;
            else current_move = (int)gremlin_nob_move::skull_bash;
        }


    last_move = tmp;
}



void gremlin_nob::play_turn(playInfo& info){

    switch((gremlin_nob_move)current_move){


    case (gremlin_nob_move::bellow):{

        int effect_number = 2;

        abstractPower* np = PowerFactory::createPower(powerID::enrage, this, effect_number);
        this->add_power(info.actions, np);

        break;
    }


    case (gremlin_nob_move::skull_bash): {

        int effect_number = 2;

        perform_attack(info);

        for (auto item : info.target_list) {
            abstractPower* np = PowerFactory::createPower(powerID::vulnerable, item, effect_number);
            item->add_power(info.actions, np);
        }

        break;
    }


    case (gremlin_nob_move::bull_rush):{

        perform_attack(info);

        break;

    }


    }

    enemy_turn++;
    choose_move();
}

QString gremlin_nob::get_story() {
    return (QObject::tr("Gremlin Nob clenches his fists and lets out a growl from the pit of his scarred throat.\nEvery spell whispered in his presence only swells his rage, as if the Spire itself wants to forge him into a monster that even he is tired of being."));
}
