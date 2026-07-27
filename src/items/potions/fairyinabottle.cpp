#include "fairyinabottle.h"
#include "combat/attack_info.h"
#include "entity/abstractentity.h"

fairyInABottle::fairyInABottle(abstractEntity* owner_init)
    :abstractPotion(tr("Fairy in a Bottle"), tr("When you would die, heal to 30%of your Max HP instead and discard this potion."), owner_init)
{}

void fairyInABottle::play(playInfo& info){
    healInfo h;
    h.owner = owner;
    h.value = (int)owner->get_max_hp() * amount;
    info.actions.heal(h);
}

QString fairyInABottle::get_story() {
    return (QObject::tr("The Fairy in a Bottle presses its translucent wings against the glass, eyes closed in a deep slumber.\nBut at the moment of death, the bottle shatters and the fairy awakens to pull the traveler back with a kiss from beyond oblivion, then vanishes, never to be seen."));
}
