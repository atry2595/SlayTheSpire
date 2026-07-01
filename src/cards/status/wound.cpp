#include "wound.h"

wound::wound()
    :abstractStatusCard(tr("Wound"), "", 0, false, false, false, false)
{
    base_is_playable = playable = false;
    QString s;
    if (!playable) s += tr("Unplayable.\n");
    base_description = description = s;
}

QString wound::generate_description(){

    QString s;
    if (!playable) s += tr("Unplayable.\n");
    return s;
}

void wound::play(playInfo& play_info){
}

void wound::upgrade(){
}

void wound::base_upgrade(){
}





