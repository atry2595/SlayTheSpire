#include "curse_of_the_bell.h"

curse_of_the_bell::curse_of_the_bell()
    :abstractCurseCard(tr("Curse of the bell"), "", 0, false, false, false, false)
{
    base_is_playable = playable = false;
    QString s;
    if (!playable) s += tr("Unplayable.\n");
    s+= tr("Cannot be removed from your deck.");
    base_description = description = s;
}

QString curse_of_the_bell::generate_description(){

    QString s;
    if (!playable) s += tr("Unplayable.\n");
    s+= tr("Cannot be removed from your deck.");
    return s;
}

void curse_of_the_bell::play(playInfo& play_info){
}

void curse_of_the_bell::upgrade(){
}

void curse_of_the_bell::base_upgrade(){
}





