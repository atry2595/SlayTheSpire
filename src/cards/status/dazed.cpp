#include "dazed.h"

dazed::dazed()
    :abstractStatusCard(tr("dazed"), "", 0, false, false, true, false)
{
    base_is_playable = playable = false;
    QString s;
    if (!playable) s += tr("Unplayable.\n");
    if (is_ethereal) s+= tr("Ethereal.");
    base_description = description = s;
}

QString dazed::generate_description(){

    QString s;
    if (!playable) s += tr("Unplayable.\n");
    if (is_ethereal) s+= tr("Ethereal.");
    return s;
}

void dazed::play(playInfo& play_info){
}

void dazed::upgrade(){
}

void dazed::base_upgrade(){
}





