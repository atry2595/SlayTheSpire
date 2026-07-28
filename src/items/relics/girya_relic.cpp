#include "girya_relic.h"
#include "items/powers/powerfactory.h"
#include "entity/abstractentity.h"
#include "ui/restpage/restpage.h"

girya_relic::girya_relic(abstractEntity* owner_init)
    :abstractRelic(tr("Girya"), owner_init)
{
    description = tr("(%1)You can now gain Strength at Rest Sites (up to 3 times).").arg(value);
}

QString girya_relic::generate_description(){
    description = tr("(%1)You can now gain Strength at Rest Sites (up to 3 times).").arg(value);
    return description;
}

void girya_relic::at_combat_start(game_action& actions){
    if (value == 0) return;
    abstractPower* np = PowerFactory::createPower(powerID::strength, owner, value);
    owner->add_power(actions, np);
}

void girya_relic::added_time(game_action& actions){
    RestPage::can_lift = true;
    lifting_connection = connect(actions.get_event(), &combatEvent::lift, this,
        [this](abstractEntity* entity){
        if (entity == owner) {
            value = std::min(max_value, value + 1);
            if (value == max_value) {
                RestPage::can_lift = false;
            }
            generate_description();
        }
    });
}

QString girya_relic::get_story() {
    return (QObject::tr("Girya, the seal of silent grief, weighs heavy in the traveler's pocket—soundless but relentless.\nWith every strike landed, more power is drawn from this compressed sorrow, as if sorrow itself knows how to turn into fury."));
}
