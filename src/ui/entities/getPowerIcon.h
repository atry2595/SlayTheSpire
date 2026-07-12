#ifndef GETPOWERICON_H
#define GETPOWERICON_H

#include "categories/powers.h"
#include <QPixmap>


inline QPixmap getPowerIcon(powerID id) {
    switch (id){
    case powerID::barricade:
        return QPixmap(":/icon/buff/barricade.ico");

    case powerID::berserk:
        return QPixmap(":/icon/buff/berserk.ico");

    case powerID::brutality:
        return QPixmap(":/icon/buff/brutality.ico");

    case powerID::curl_up:
        return QPixmap(":/icon/buff/curl_up.ico");

    case powerID::dark_embrace:
        return QPixmap(":/icon/buff/dark_embrace.ico");

    case powerID::demon_form:
        return QPixmap(":/icon/buff/demon_form.ico");

    case powerID::dexterity:
        return QPixmap(":/icon/buff/dexterity.ico");

    case powerID::enrage:
        return QPixmap(":/icon/buff/enrage.ico");

    case powerID::entangled:
        return QPixmap(":/icon/buff/entangled.ico");

    case powerID::feel_no_pain:
        return QPixmap(":/icon/buff/feel_no_pain.ico");

    case powerID::frail:
        return QPixmap(":/icon/buff/frail.ico");

    case powerID::metallicize:
        return QPixmap(":/icon/buff/metallicize.ico");

    case powerID::painful_stabs:
        return QPixmap(":/icon/buff/painful_stab.ico");

    case powerID::ritual:
        return QPixmap(":/icon/buff/ritual.ico");

    case powerID::strength:
        return QPixmap(":/icon/buff/strength.ico");

    case powerID::thievery:
        return QPixmap(":/icon/buff/thievery.ico");

    case powerID::vulnerable:
        return QPixmap(":/icon/buff/vulnerable.ico");

    case powerID::weak:
        return QPixmap(":/icon/buff/weak.ico");

    default:
        return QPixmap();
    }
}


#endif // GETPOWERICON_H
