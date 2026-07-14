#include "injury.h"

injury::injury()
    :abstractCurseCard(tr("Injury"), "", 0, false, false, false, false)
{
    base_is_playable = playable = false;
    QString s;
    if (!playable) s += tr("Unplayable.\n");
    base_description = description = s;
}

QString injury::generate_description(){

    QString s;
    if (!playable) s += tr("Unplayable.\n");
    return s;
}

void injury::play(playInfo& play_info){
}

void injury::upgrade(){
}

void injury::base_upgrade(){
}




