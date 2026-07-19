#ifndef GETRELICIMAGE_H
#define GETRELICIMAGE_H

#include "categories/relics.h"
#include <QPixmap>

inline QPixmap getRelicImage(relicID id) {
    switch (id){
    case relicID::anchor : return QPixmap(":/icon/relic/anchor.ico");
    case relicID::bag_of_marbles : return QPixmap(":/icon/relic/bag_of_marbles.ico");
    case relicID::black_star : return QPixmap(":/icon/relic/black_star.ico");
    case relicID::blood_vial : return QPixmap(":/icon/relic/blood_vial.ico");
    case relicID::burning_blood : return QPixmap(":/icon/relic/burning_blood.ico");
    case relicID::calling_bell : return QPixmap(":/icon/relic/calling_bell.ico");
    case relicID::captains_wheel : return QPixmap(":/icon/relic/captains_wheel.ico");
    case relicID::centennial_puzzle : return QPixmap(":/icon/relic/centennial_puzzle.ico");
    case relicID::girya : return QPixmap(":/icon/relic/girya.ico");
    case relicID::golden_idol : return QPixmap(":/icon/relic/golden_idol.ico");
    case relicID::greenback : return QPixmap(":/icon/relic/greenback.ico");
    case relicID::gremlin_horn : return QPixmap(":/icon/relic/gremlin_horn.ico");
    case relicID::gremlin_visage : return QPixmap(":/icon/relic/gremlin_visage.ico");
    case relicID::happy_flower : return QPixmap(":/icon/relic/happy_flower.ico");
    case relicID::helmet_of_the_cleric : return QPixmap(":/icon/relic/helmet_of_the_cleric.ico");
    case relicID::horn_cleat : return QPixmap(":/icon/relic/horn_cleat.ico");
    case relicID::ice_cream : return QPixmap(":/icon/relic/ice_cream.ico");
    case relicID::kunai : return QPixmap(":/icon/relic/kunai.ico");
    case relicID::mark_of_pain : return QPixmap(":/icon/relic/mark_of_pain.ico");
    case relicID::mutagenic_strength : return QPixmap(":/icon/relic/mutagenic_strength.ico");
    case relicID::oddly_smooth_stone : return QPixmap(":/icon/relic/oddly_smooth_stone.ico");
    case relicID::philosophers_stone : return QPixmap(":/icon/relic/philosophers_stone.ico");
    case relicID::preserved_insect : return QPixmap(":/icon/relic/preserved_insect.ico");
    case relicID::red_mask : return QPixmap(":/icon/relic/red_mask.ico");
    case relicID::red_skull : return QPixmap(":/icon/relic/red_skull.ico");
    case relicID::shuriken : return QPixmap(":/icon/relic/shuriken.ico");
    case relicID::slavers_collar : return QPixmap(":/icon/relic/slavers_collar.ico");
    case relicID::sozu : return QPixmap(":/icon/relic/sozu.ico");
    case relicID::spirit_poop : return QPixmap(":/icon/relic/spirit_poop.ico");
    case relicID::the_boot : return QPixmap(":/icon/relic/the_boot.ico");
    case relicID::tungsten_rod : return QPixmap(":/icon/relic/tungsten_rod.ico");
    case relicID::vajra : return QPixmap(":/icon/relic/vajra.ico");
    case relicID::velvet_choker : return QPixmap(":/icon/relic/velvet_choker.ico");
    case relicID::warped_tongs : return QPixmap(":/icon/relic/warped_tongs.ico");
    case relicID::cultist_headpiece : return QPixmap(":/icon/relic/warped_tongs.ico");;
    case relicID::lively_plant : return QPixmap(":/icon/relic/lively_plant.ico");;
    case relicID::cursed_key : return QPixmap(":/icon/relic/cursed_key.ico");;
    }
}
#endif // GETRELICIMAGE_H
