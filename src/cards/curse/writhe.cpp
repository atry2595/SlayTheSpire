#include "writhe.h"

writhe::writhe()
    :abstractCurseCard(tr("Writhe"), "", 0, false, false, false, true)
{
    base_is_playable = playable = false;
    QString s;
    if (!playable) s += tr("Unplayable.\n");
    if (is_initial) s+= tr("Innate.");
    base_description = description = s;
}

QString writhe::generate_description(){

    QString s;
    if (!playable) s += tr("Unplayable.\n");
    if (is_initial) s+= tr("Innate.");
    return s;
}

void writhe::play(playInfo& play_info){
}

void writhe::upgrade(){
}

void writhe::base_upgrade(){
}





