#include "slimed.h"

slimed::slimed()
    :abstractStatusCard(tr("Slimed"), "", 1, true, false, false, false)
{
    QString s;
    if (is_exhaust) s+= tr("Exhaust.");
    base_description = description = s;
}

QString slimed::generate_description(){

    QString s;
    if (is_exhaust) s+= tr("Exhaust.");
    return s;
}

void slimed::play(playInfo& play_info){
}

void slimed::upgrade(){
}

void slimed::base_upgrade(){
}
