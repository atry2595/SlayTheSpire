#include "imagemanager.h"
#include "core/setting.h"


imageManager& imageManager::instance() {
    static imageManager mng;
    return mng;
}

imageManager::imageManager() {
    icon_table["error"] = QPixmap(":/icon/error.png");
    icon_table["gold"] = QPixmap(":/icon/coin.ico");
    icon_table["corner"] = QPixmap(":/icon/corner.ico");
    icon_table["heart"] = QPixmap(":/icon/heart.png");
    icon_table["left_button"] = QPixmap(":/icon/left_button.png");
    icon_table["right_button"] = QPixmap(":/icon/right_button.png");
    icon_table["setting"] = QPixmap(":/icon/setting.png");
    icon_table["shield"] = QPixmap(":/icon/shield.ico");
    power_table[powerID::barricade] = QPixmap(":/icon/buff/barricade.ico");
    power_table[powerID::berserk] = QPixmap(":/icon/buff/berserk.ico");
    power_table[powerID::brutality] = QPixmap(":/icon/buff/brutality.ico");
    power_table[powerID::curl_up] = QPixmap(":/icon/buff/curl_up.ico");
    power_table[powerID::dark_embrace] = QPixmap(":/icon/buff/dark_embrace.ico");
    power_table[powerID::demon_form] = QPixmap(":/icon/buff/demon_form.ico");
    power_table[powerID::dexterity] = QPixmap(":/icon/buff/dexterity.ico");
    power_table[powerID::enrage] = QPixmap(":/icon/buff/enrage.ico");
    power_table[powerID::rage] = QPixmap(":/icon/buff/enrage.ico");
    power_table[powerID::entangled] = QPixmap(":/icon/buff/entangled.ico");
    power_table[powerID::feel_no_pain] = QPixmap(":/icon/buff/feel_no_pain.ico");
    power_table[powerID::frail] = QPixmap(":/icon/buff/frail.ico");
    power_table[powerID::metallicize] = QPixmap(":/icon/buff/metallicize.ico");
    power_table[powerID::painful_stabs] = QPixmap(":/icon/buff/painful_stab.ico");
    power_table[powerID::ritual] = QPixmap(":/icon/buff/ritual.ico");
    power_table[powerID::strength] = QPixmap(":/icon/buff/strength.ico");
    power_table[powerID::thievery] = QPixmap(":/icon/buff/thievery.ico");
    power_table[powerID::vulnerable] = QPixmap(":/icon/buff/vulnerable.ico");
    power_table[powerID::weak] = QPixmap(":/icon/buff/weak.ico");
    intent_table["attack1"] = QPixmap(QString(":/icon/intent/attack1.ico"));
    intent_table["attack2"] = QPixmap(QString(":/icon/intent/attack2.ico"));
    intent_table["attack3"] = QPixmap(QString(":/icon/intent/attack3.ico"));
    intent_table["attack4"] = QPixmap(QString(":/icon/intent/attack4.ico"));
    intent_table["attack5"] = QPixmap(QString(":/icon/intent/attack5.ico"));
    intent_table["attack6"] = QPixmap(QString(":/icon/intent/attack6.ico"));
    intent_table["attack7"] = QPixmap(QString(":/icon/intent/attack7.ico"));
    intent_table["attack1_block"] = QPixmap(QString(":/icon/intent/attack1_block.ico"));
    intent_table["attack2_block"] = QPixmap(QString(":/icon/intent/attack2_block.ico"));
    intent_table["attack3_block"] = QPixmap(QString(":/icon/intent/attack3_block.ico"));
    intent_table["attack4_block"] = QPixmap(QString(":/icon/intent/attack4_block.ico"));
    intent_table["attack5_block"] = QPixmap(QString(":/icon/intent/attack5_block.ico"));
    intent_table["attack6_block"] = QPixmap(QString(":/icon/intent/attack6_block.ico"));
    intent_table["attack7_block"] = QPixmap(QString(":/icon/intent/attack7_block.ico"));
    intent_table["attack1_buff"] = QPixmap(QString(":/icon/intent/attack1_buff.ico"));
    intent_table["attack2_buff"] = QPixmap(QString(":/icon/intent/attack2_buff.ico"));
    intent_table["attack3_buff"] = QPixmap(QString(":/icon/intent/attack3_buff.ico"));
    intent_table["attack4_buff"] = QPixmap(QString(":/icon/intent/attack4_buff.ico"));
    intent_table["attack5_buff"] = QPixmap(QString(":/icon/intent/attack5_buff.ico"));
    intent_table["attack6_buff"] = QPixmap(QString(":/icon/intent/attack6_buff.ico"));
    intent_table["attack7_buff"] = QPixmap(QString(":/icon/intent/attack7_buff.ico"));
    intent_table["attack1_debuff"] = QPixmap(QString(":/icon/intent/attack1_debuff.ico"));
    intent_table["attack2_debuff"] = QPixmap(QString(":/icon/intent/attack2_debuff.ico"));
    intent_table["attack3_debuff"] = QPixmap(QString(":/icon/intent/attack3_debuff.ico"));
    intent_table["attack4_debuff"] = QPixmap(QString(":/icon/intent/attack4_debuff.ico"));
    intent_table["attack5_debuff"] = QPixmap(QString(":/icon/intent/attack5_debuff.ico"));
    intent_table["attack6_debuff"] = QPixmap(QString(":/icon/intent/attack6_debuff.ico"));
    intent_table["attack7_debuff"] = QPixmap(QString(":/icon/intent/attack7_debuff.ico"));
    intent_table["buff"] = QPixmap(":/icon/intent/buff.ico");
    intent_table["debuff"] = QPixmap(":/icon/intent/debuff.ico");
    intent_table["block"] = QPixmap(":/icon/intent/block.ico");
    intent_table["block_buff"] = QPixmap(":/icon/intent/block-buff.ico");
    intent_table["escape"] = QPixmap(":/icon/intent/escape.ico");
    intent_table["unknown"] = QPixmap(":/icon/intent/unknown.ico");
    potion_table[potionID::block_potion] = QPixmap(":/icon/potion/block_potion.ico");
    potion_table[potionID::white_blood_potion] = QPixmap(":/icon/potion/blood_potion.ico");
    potion_table[potionID::cultist_potion] = QPixmap(":/icon/potion/cultist_potion.ico");
    potion_table[potionID::dexterity_potion] = QPixmap(":/icon/potion/dexterity_potion.ico");
    potion_table[potionID::energy_potion] = QPixmap(":/icon/potion/energy_potion.ico");
    potion_table[potionID::explosive_potion] = QPixmap(":/icon/potion/explosive_potion.ico");
    potion_table[potionID::fairy_in_a_bottle] = QPixmap(":/icon/potion/fairy_in_a_bottle.ico");
    potion_table[potionID::fear_potion] = QPixmap(":/icon/potion/fear_potion.ico");
    potion_table[potionID::fire_potion] = QPixmap(":/icon/potion/fire_potion.ico");
    potion_table[potionID::strength_potion] = QPixmap(":/icon/potion/strength_potion.ico");
    potion_table[potionID::swift_potion] = QPixmap(":/icon/potion/swift_potion.ico");
    potion_table[potionID::weak_potion] = QPixmap(":/icon/potion/weak_potion.ico");
    relic_table[relicID::anchor] = QPixmap(":/icon/relic/anchor.ico");
    relic_table[relicID::bag_of_marbles] = QPixmap(":/icon/relic/bag_of_marbles.ico");
    relic_table[relicID::black_star] = QPixmap(":/icon/relic/black_star.ico");
    relic_table[relicID::blood_vial] = QPixmap(":/icon/relic/blood_vial.ico");
    relic_table[relicID::burning_blood] = QPixmap(":/icon/relic/burning_blood.ico");
    relic_table[relicID::calling_bell] = QPixmap(":/icon/relic/calling_bell.ico");
    relic_table[relicID::captains_wheel] = QPixmap(":/icon/relic/captains_wheel.ico");
    relic_table[relicID::centennial_puzzle] = QPixmap(":/icon/relic/centennial_puzzle.ico");
    relic_table[relicID::girya] = QPixmap(":/icon/relic/girya.ico");
    relic_table[relicID::golden_idol] = QPixmap(":/icon/relic/golden_idol.ico");
    relic_table[relicID::greenback] = QPixmap(":/icon/relic/greenback.ico");
    relic_table[relicID::gremlin_horn] = QPixmap(":/icon/relic/gremlin_horn.ico");
    relic_table[relicID::gremlin_visage] = QPixmap(":/icon/relic/gremlin_visage.ico");
    relic_table[relicID::happy_flower] = QPixmap(":/icon/relic/happy_flower.ico");
    relic_table[relicID::helmet_of_the_cleric] = QPixmap(":/icon/relic/helmet_of_the_cleric.ico");
    relic_table[relicID::horn_cleat] = QPixmap(":/icon/relic/horn_cleat.ico");
    relic_table[relicID::ice_cream] = QPixmap(":/icon/relic/ice_cream.ico");
    relic_table[relicID::kunai] = QPixmap(":/icon/relic/kunai.ico");
    relic_table[relicID::mark_of_pain] = QPixmap(":/icon/relic/mark_of_pain.ico");
    relic_table[relicID::mutagenic_strength] = QPixmap(":/icon/relic/mutagenic_strength.ico");
    relic_table[relicID::oddly_smooth_stone] = QPixmap(":/icon/relic/oddly_smooth_stone.ico");
    relic_table[relicID::philosophers_stone] = QPixmap(":/icon/relic/philosophers_stone.ico");
    relic_table[relicID::preserved_insect] = QPixmap(":/icon/relic/preserved_insect.ico");
    relic_table[relicID::red_mask] = QPixmap(":/icon/relic/red_mask.ico");
    relic_table[relicID::red_skull] = QPixmap(":/icon/relic/red_skull.ico");
    relic_table[relicID::shuriken] = QPixmap(":/icon/relic/shuriken.ico");
    relic_table[relicID::slavers_collar] = QPixmap(":/icon/relic/slavers_collar.ico");
    relic_table[relicID::sozu] = QPixmap(":/icon/relic/sozu.ico");
    relic_table[relicID::spirit_poop] = QPixmap(":/icon/relic/spirit_poop.ico");
    relic_table[relicID::the_boot] = QPixmap(":/icon/relic/the_boot.ico");
    relic_table[relicID::tungsten_rod] = QPixmap(":/icon/relic/tungsten_rod.ico");
    relic_table[relicID::vajra] = QPixmap(":/icon/relic/vajra.ico");
    relic_table[relicID::velvet_choker] = QPixmap(":/icon/relic/velvet_choker.ico");
    relic_table[relicID::warped_tongs] = QPixmap(":/icon/relic/warped_tongs.ico");
    relic_table[relicID::cultist_headpiece] = QPixmap(":/icon/relic/cultist_headpiece.ico");
    relic_table[relicID::lively_plant] = QPixmap(":/icon/relic/lively_plant.ico");
    relic_table[relicID::cursed_key] = QPixmap(":/icon/relic/cursed_key.ico");
    frame_table["0at"] = QPixmap(":/image/card/frame/frame_red.png");
    frame_table["0sk"] = QPixmap(":/image/card/frame/frame_green.png");
    frame_table["0po"] = QPixmap(":/image/card/frame/frame_purple.png");
    frame_table["0st"] = QPixmap(":/image/card/frame/frame_gray.png");
    frame_table["0cu"] = QPixmap(":/image/card/frame/frame_black.png");
    frame_table["1"] = QPixmap(":/image/card/frame/frame1.png");
    frame_table["2"] = QPixmap(":/image/card/frame/frame2.png");
    frame_table["3"] = QPixmap(":/image/card/frame/frame3.png");
    back_table[cardTemplates::common] = QPixmap(":/image/cards/back/back.png");
    back_table[cardTemplates::ancient] = QPixmap(":/image/cards/back/back1.png");
    back_table[cardTemplates::metallic] = QPixmap(":/image/cards/back/back2.png");
    back_table[cardTemplates::toxic_blossom] = QPixmap(":/image/cards/back/back3.png");
    card_table[cardID::strike] = QPixmap(":/image/cards/attack/strike.png");
    card_table[cardID::reaper] = QPixmap(":/image/cards/attack/reaper.png");
    card_table[cardID::bludgeon] = QPixmap(":/image/cards/attack/bludgeon.png");
    card_table[cardID::feed] = QPixmap(":/image/cards/attack/feed.png");
    card_table[cardID::immolate] = QPixmap(":/image/cards/attack/immolate.png");
    card_table[cardID::whirlwind] = QPixmap(":/image/cards/attack/whirlwind.png");
    card_table[cardID::blood_for_blood] = QPixmap(":/image/cards/attack/blood_for_blood.png");
    card_table[cardID::bash] = QPixmap(":/image/cards/attack/bash.png");
    card_table[cardID::twin_strike] = QPixmap(":/image/cards/attack/twin_strike.png");
    card_table[cardID::perfected_strike] = QPixmap(":/image/cards/attack/perfected_strike.png");
    card_table[cardID::clash] = QPixmap(":/image/cards/attack/clash.png");
    card_table[cardID::uppercut] = QPixmap(":/image/cards/attack/uppercut.png");
    card_table[cardID::heavy_blade] = QPixmap(":/image/cards/attack/heavy_blade.png");
    card_table[cardID::pommel_strike] = QPixmap(":/image/cards/attack/pommel_strike.png");
    card_table[cardID::carnage] = QPixmap(":/image/cards/attack/carnage.png");
    card_table[cardID::hemokinesis] = QPixmap(":/image/cards/attack/hemokinesis.png");
    card_table[cardID::defend] = QPixmap(":/image/cards/skill/defend.png");
    card_table[cardID::exhume] = QPixmap(":/image/cards/skill/exhume.png");
    card_table[cardID::limit_break] = QPixmap(":/image/cards/skill/limit_break.png");
    card_table[cardID::offering] = QPixmap(":/image/cards/skill/offering.png");
    card_table[cardID::impervious] = QPixmap(":/image/cards/skill/impervious.png");
    card_table[cardID::dual_wield] = QPixmap(":/image/cards/skill/dual_wield.png");
    card_table[cardID::entrench] = QPixmap(":/image/cards/skill/entrench.png");
    card_table[cardID::warcry] = QPixmap(":/image/cards/skill/warcry.png");
    card_table[cardID::true_grit] = QPixmap(":/image/cards/skill/true_grit.png");
    card_table[cardID::shrug_it_off] = QPixmap(":/image/cards/skill/shrug_it_off.png");
    card_table[cardID::power_through] = QPixmap(":/image/cards/skill/power_through.png");
    card_table[cardID::bloodletting] = QPixmap(":/image/cards/skill/bloodletting.png");
    card_table[cardID::disarm] = QPixmap(":/image/cards/skill/disarm.png");
    card_table[cardID::battle_trance] = QPixmap(":/image/cards/skill/battle_trance.png");
    card_table[cardID::spot_weakness] = QPixmap(":/image/cards/skill/spot_weakness.png");
    card_table[cardID::rage] = QPixmap(":/image/cards/skill/rage.png");
    card_table[cardID::JAX] = QPixmap(":/image/cards/skill/JAX.png");
    card_table[cardID::inflame] = QPixmap(":/image/cards/power/inflame.png");
    card_table[cardID::metallicize] = QPixmap(":/image/cards/power/metallicize.png");
    card_table[cardID::demon_form] = QPixmap(":/image/cards/power/demon_form.png");
    card_table[cardID::brutality] = QPixmap(":/image/cards/power/brutality.png");
    card_table[cardID::feel_no_pain] = QPixmap(":/image/cards/power/feel_no_pain.png");
    card_table[cardID::barricade] = QPixmap(":/image/cards/power/barricade.png");
    card_table[cardID::dark_embrace] = QPixmap(":/image/cards/power/dark_embrace.png");
    card_table[cardID::berserk] = QPixmap(":/image/cards/power/berserk.png");
    card_table[cardID::dazed] = QPixmap(":/image/cards/status/dazed.png");
    card_table[cardID::slimed] = QPixmap(":/image/cards/status/slimed.png");
    card_table[cardID::wound] = QPixmap(":/image/cards/status/wound.png");
    card_table[cardID::burn] = QPixmap(":/image/cards/status/burn.png");
    card_table[cardID::curse_of_the_bell] = QPixmap(":/image/cards/curse/curse_of_bell.png");
    card_table[cardID::regret] = QPixmap(":/image/cards/curse/regret.png");
    card_table[cardID::writhe] = QPixmap(":/image/cards/curse/writhe.png");
    card_table[cardID::pain] = QPixmap(":/image/cards/curse/pain.png");
    card_table[cardID::shame] =  QPixmap(":/image/cards/curse/shame.png");
    card_table[cardID::doubt] =  QPixmap(":/image/cards/curse/doubt.png");
    card_table[cardID::injury] = QPixmap(":/image/cards/curse/injury.png");
    entity_table[entityID::cultist] =  QPixmap(":/image/characters/cultist.png");
    entity_table[entityID::jaw_worm] =  QPixmap(":/image/characters/jaw_worm.png");
    entity_table[entityID::red_louse] =  QPixmap(":/image/characters/red_louse.png");
    entity_table[entityID::green_louse] =  QPixmap(":/image/characters/green_louse.png");
    entity_table[entityID::small_slime] =  QPixmap(":/image/characters/small_slime.png");
    entity_table[entityID::medium_slime] =  QPixmap(":/image/characters/medium_slime.png");
    entity_table[entityID::large_slime] =  QPixmap(":/image/characters/large_slime.png");
    entity_table[entityID::looter] =  QPixmap(":/image/characters/looter.png");
    entity_table[entityID::mugger] =  QPixmap(":/image/characters/mugger.png");
    entity_table[entityID::blue_slaver] =  QPixmap(":/image/characters/blue_slaver.png");
    entity_table[entityID::red_slaver] =  QPixmap(":/image/characters/red_slaver.png");
    entity_table[entityID::spheric_guardian] =  QPixmap(":/image/characters/spheric_guardian.png");
    entity_table[entityID::gremlin_nob] =  QPixmap(":/image/characters/gremlin_nob.png");
    entity_table[entityID::sentry] =  QPixmap(":/image/characters/sentry.png");
    entity_table[entityID::book_of_stabbing] =  QPixmap(":/image/characters/book_of_stabbing.png");
    entity_table[entityID::taskmaster] =  QPixmap(":/image/characters/taskmaster.png");
    entity_table[entityID::slime_boss] =  QPixmap(":/image/characters/king_slime.png");
    entity_table[entityID::hexaghost] =  QPixmap(":/image/characters/hexaghost.png");
    entity_table[entityID::the_champ] =  QPixmap(":/image/characters/the_champ.png");
    entity_table[entityID::veilclad] =  QPixmap(":/image/characters/veilclad.png");
    entity_table[entityID::oathclad] =  QPixmap(":/image/characters/oathclad.png");
    entity1x1_table[entityID::cultist] =  QPixmap(":/image/characters/1x1/cultist.png");
    entity1x1_table[entityID::jaw_worm] =  QPixmap(":/image/characters/1x1/jaw_worm.png");
    entity1x1_table[entityID::red_louse] =  QPixmap(":/image/characters/1x1/red_louse.png");
    entity1x1_table[entityID::green_louse] =  QPixmap(":/image/characters/1x1/green_louse.png");
    entity1x1_table[entityID::small_slime] =  QPixmap(":/image/characters/1x1/small_slime.png");
    entity1x1_table[entityID::medium_slime] =  QPixmap(":/image/characters/1x1/medium_slime.png");
    entity1x1_table[entityID::large_slime] =  QPixmap(":/image/characters/1x1/large_slime.png");
    entity1x1_table[entityID::looter] =  QPixmap(":/image/characters/1x1/looter.png");
    entity1x1_table[entityID::mugger] =  QPixmap(":/image/characters/1x1/mugger.png");
    entity1x1_table[entityID::blue_slaver] =  QPixmap(":/image/characters/1x1/blue_slaver.png");
    entity1x1_table[entityID::red_slaver] =  QPixmap(":/image/characters/1x1/red_slaver.png");
    entity1x1_table[entityID::spheric_guardian] =  QPixmap(":/image/characters/1x1/spheric_guardian.png");
    entity1x1_table[entityID::gremlin_nob] =  QPixmap(":/image/characters/1x1/gremlin_nob.png");
    entity1x1_table[entityID::sentry] =  QPixmap(":/image/characters/1x1/sentry.png");
    entity1x1_table[entityID::book_of_stabbing] =  QPixmap(":/image/characters/1x1/book_of_stabbing.png");
    entity1x1_table[entityID::taskmaster] =  QPixmap(":/image/characters/1x1/taskmaster.png");
    entity1x1_table[entityID::slime_boss] =  QPixmap(":/image/characters/1x1/king_slime.png");
    entity1x1_table[entityID::hexaghost] =  QPixmap(":/image/characters/1x1/hexaghost.png");
    entity1x1_table[entityID::the_champ] =  QPixmap(":/image/characters/1x1/the_champ.png");
    entity1x1_table[entityID::ironclad] =  QPixmap(":/image/characters/1x1/ironclad1.png");
    ironclad_table[skins::ironclad] = QPixmap(":/image/characters/ironclad1.png");
    ironclad_table[skins::ironclad] = QPixmap(":/image/characters/ironclad1.png");
    ironclad_table[skins::ironclad] = QPixmap(":/image/characters/ironclad1.png");
    ironclad_table[skins::ironclad] = QPixmap(":/image/characters/ironclad1.png");
    ironclad_table[skins::ironclad] = QPixmap(":/image/characters/ironclad1.png");
    effect_table["bite"] = QPixmap(":/image/effect/bite.png");
    effect_table["dmg"] = QPixmap(":/image/effect/dmg.png");
    effect_table["dmg2"] = QPixmap(":/image/effect/dmg2.png");
    effect_table["dmg3"] = QPixmap(":/image/effect/dmg3.png");
    effect_table["explosion"] = QPixmap(":/image/effect/explosion.png");
    effect_table["feather"] = QPixmap(":/image/effect/feather.png");
    effect_table["fire"] = QPixmap(":/image/effect/fire.png");
    effect_table["mace"] = QPixmap(":/image/effect/mace.png");
    effect_table["rotary"] = QPixmap(":/image/effect/rotary.png");
    effect_table["rotary_blow"] = QPixmap(":/image/effect/rotary_blow.png");
    effect_table["sickle"] = QPixmap(":/image/effect/sickle.png");
    effect_table["spearhead"] = QPixmap(":/image/effect/spearhead.png");
    effect_table["squeeze"] = QPixmap(":/image/effect/squeeze.png");
    effect_table["tornado"] = QPixmap(":/image/effect/tornado.png");
    effect_table["twin"] = QPixmap(":/image/effect/twin.png");
    effect_table["web"] = QPixmap(":/image/effect/web.png");
    effect_table["web_dmg"] = QPixmap(":/image/effect/web_dmg.png");
    effect_table["wings"] = QPixmap(":/image/effect/wings.png");
    background_table["1m"] = QPixmap(":/image/scene/map1_normal.jpg");
    background_table["1e"] = QPixmap(":/image/scene/map1_dark.jpg");
    background_table["1b"] = QPixmap(":/image/scene/map1_epic.jpg");
    background_table["2m"] = QPixmap(":/image/scene/map2_normal.jpg");
    background_table["2e"] = QPixmap(":/image/scene/map2_dark.jpg");
    background_table["2b"] = QPixmap(":/image/scene/map2_epic.jpg");
    background_table["mr"] = QPixmap(":/image/scene/shop");
    background_table["r"] = QPixmap(":/image/scene/rest.png");
    chest_table[ChestType::regular] = QPixmap(":/image/chest/veilchest.png");
    chest_table[ChestType::boss] = QPixmap(":/image/chest/oathchest.png");
    dialogbox_table[ChestType::regular] = QPixmap(":/image/chest/veil_dialogbox.png");
    dialogbox_table[ChestType::boss] = QPixmap(":/image/chest/oath_dialogbox.png");
    other_table["map"] = QPixmap(":/image/map/map_back.png");
    other_table["legend"] = QPixmap(":/image/map/legend.png");
    legend_table[RoomType::MONSTER] = QPixmap(":/icon/map/mons.ico");
    legend_table[RoomType::ELITE] = QPixmap(":/icon/map/elite.ico");
    legend_table[RoomType::UNKNOWN] = QPixmap(":/icon/map/event.ico");
    legend_table[RoomType::MERCHANT] = QPixmap(":/icon/map/merch.ico");
    legend_table[RoomType::REST] = QPixmap(":/icon/map/rest.png");
    legend_table[RoomType::TREASURE] = QPixmap(":/icon/map/treasure.ico");
    legend_table[RoomType::BOSS] = QPixmap(":/icon/map/boss.ico");
    unknown_table[unknownID::ancient_writing] = QPixmap(":/image/events/ancient.jpg");
    unknown_table[unknownID::augmenter] = QPixmap(":/image/events/augmenter.jpg");
    unknown_table[unknownID::bonfire_spirits] = QPixmap(":/image/events/bonefire.jpg");
    unknown_table[unknownID::the_cleric] = QPixmap(":/image/events/cleric.jpg");
    unknown_table[unknownID::face_trader] = QPixmap(":/image/events/facetrader.jpg");
    unknown_table[unknownID::golden_idol] = QPixmap(":/image/events/goldenidol.jpg");
    unknown_table[unknownID::golden_shrine] = QPixmap(":/image/events/goldenshirine.jpg");
    unknown_table[unknownID::lab] = QPixmap(":/image/events/lab.jpg");
    unknown_table[unknownID::the_joust] = QPixmap(":/image/events/joust.jpg");
    unknown_table[unknownID::ominous_forge] = QPixmap(":/image/events/ominous.jpg");
    unknown_table[unknownID::pleading_vagrant] = QPixmap(":/image/events/pleading.jpg");
    unknown_table[unknownID::the_ssssssserpant] = QPixmap(":/image/events/serpent.jpg");
    unknown_table[unknownID::shining_light] = QPixmap(":/image/events/shininglight.jpg");
}

QPixmap& imageManager::getIcon(QString name) {
    if (icon_table.contains(name)){
        return icon_table[name];
    }
    return icon_table["error"];
}

QPixmap& imageManager::getPowerIcon(powerID id){
    if (power_table.contains(id)){
        return power_table[id];
    }
    return icon_table["error"];
}

QPixmap& imageManager::getIntentIcon(const enemy_intent& intent) {
    int damage = intent.damage * intent.repeat;
    int lvl = std::min((1 + damage % 5), 7);

    switch (intent.type) {

    case intent_type::attack: {
        return intent_table[QString("attack%1").arg(lvl)];
    }

    case intent_type::attack_block: {
        return intent_table[QString("attack%1_block").arg(lvl)];
    }

    case intent_type::attack_buff: {
        return intent_table[QString("attack%1_buff").arg(lvl)];
    }

    case intent_type::attack_debuff: {
        return intent_table[QString("attack%1_debuff").arg(lvl)];
    }

    case intent_type::block: {
        return intent_table[QString("block")];
    }

    case intent_type::block_buff: {
        return intent_table[QString("block_buff")];
    }

    case intent_type::escape: {
        return intent_table[QString("escape")];
    }

    case intent_type::buff: {
        return intent_table[QString("buff")];
    }

    case intent_type::debuff: {
        return intent_table[QString("debuff")];
    }

    case intent_type::special: {
        return intent_table[QString("unknown")];
    }

    default:
        return icon_table["error"];
    }
}

QPixmap& imageManager::getPotionIcon(potionID id) {
    if (potion_table.contains(id)){
        return potion_table[id];
    }
    return icon_table["error"];
}

QPixmap& imageManager::getRelicIcon(relicID id) {
    if (relic_table.contains(id)){
        return relic_table[id];
    }
    return icon_table["error"];
}

QPixmap& imageManager::getCardFrame(cardTemplates tmpel, CardType id) {
    QString s;
    if (tmpel == cardTemplates::common && id == CardType::attack) s = "0at";
    if (tmpel == cardTemplates::common && id == CardType::skill) s = "0sk";
    if (tmpel == cardTemplates::common && id == CardType::power) s = "0po";
    if (tmpel == cardTemplates::common && id == CardType::status) s = "0st";
    if (tmpel == cardTemplates::common && id == CardType::curse) s = "0cu";
    if (tmpel == cardTemplates::ancient) s = "1";
    if (tmpel == cardTemplates::metallic) s = "2";
    if (tmpel == cardTemplates::toxic_blossom) s = "3";

    if (frame_table.contains(s)){
        return frame_table[s];
    }
    return icon_table["error"];
}
QPixmap& imageManager::getCardBack(cardTemplates tmpel) {
    if (back_table.contains(tmpel)){
        return back_table[tmpel];
    }
    return icon_table["error"];
}
QPixmap& imageManager::getCardImage(cardID id) {
    if (card_table.contains(id)){
        return card_table[id];
    }
    return icon_table["error"];
}

QPixmap& imageManager::getEntityImage(entityID id) {
    if (entity_table.contains(id)){
        return entity_table[id];
    }
    return icon_table["error"];
}
QPixmap& imageManager::getEntity1x1(entityID id) {
    if (entity1x1_table.contains(id)){
        return entity1x1_table[id];
    }
    return icon_table["error"];
}
QPixmap& imageManager::getIroncladImage(skins skin) {
    if (ironclad_table.contains(skin)){
        return ironclad_table[skin];
    }
    return icon_table["error"];
}

QPixmap& imageManager::getEffectImage(QString name) {
    if (effect_table.contains(name)){
        return effect_table[name];
    }
    return icon_table["error"];
}

QPixmap& imageManager::getBackroundImage() {
    if (combat_data::act == 1 && combat_data::room_type == RoomType::MONSTER) return background_table["1m"];
    if (combat_data::act == 1 && combat_data::room_type == RoomType::ELITE) return background_table["1e"];
    if (combat_data::act == 1 && combat_data::room_type == RoomType::BOSS) return background_table["1b"];
    if (combat_data::act == 2 && combat_data::room_type == RoomType::MONSTER) return background_table["2m"];
    if (combat_data::act == 2 && combat_data::room_type == RoomType::ELITE) return background_table["2e"];
    if (combat_data::act == 2 && combat_data::room_type == RoomType::BOSS) return background_table["2b"];
    if (combat_data::act == 1 && combat_data::room_type == RoomType::TREASURE) return background_table["1m"];
    if (combat_data::act == 2 && combat_data::room_type == RoomType::TREASURE) return background_table["2m"];
    if (combat_data::room_type == RoomType::MERCHANT) return background_table["mr"];

    return icon_table["error"];
}

QPixmap& imageManager::getChestImage(ChestType type) {
    if (chest_table.contains(type)){
        return chest_table[type];
    }
    return icon_table["error"];
}

QPixmap& imageManager::getDialogImage(ChestType type) {
    if (dialogbox_table.contains(type)){
        return dialogbox_table[type];
    }
    return icon_table["error"];
}

QPixmap& imageManager::getMapImage(QString name){
    if (other_table.contains(name)){
        return other_table[name];
    }
    return icon_table["error"];
}

QPixmap& imageManager::getMapImage(RoomType room){
    if (legend_table.contains(room)){
        return legend_table[room];
    }
    return icon_table["error"];
}

QPixmap& imageManager::getUnknownImage(unknownID id) {
    if (unknown_table.contains(id)){
        return unknown_table[id];
    }
    return icon_table["error"];
}
