cmake_minimum_required(VERSION 3.16)
project(SlayTheSpire VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt6 REQUIRED COMPONENTS
    Widgets
    Core
    Gui
    Network
    Multimedia
    LinguistTools
)

qt_add_translations(SlayTheSpire
    TS_FILES
        assests/languages/SlayTheSpire_fa_IR.ts
)

add_executable(SlayTheSpire
    # Main
    src/main.cpp

    # UI
    src/ui/mainwindow.h
    src/ui/mainwindow.cpp
    src/ui/mainwindow.ui

    # Resources
    resources.qrc

    # Combat
    src/combat/attack_info.h
    src/combat/damage_info.h
    src/combat/combat_event.h
    src/combat/game_action.h
    src/combat/game_action.cpp
    src/combat/play_info.h
    src/combat/blocking_info.h

    # Cards
    src/cards/abstractcard.h
    src/cards/abstractcard.cpp

    src/cards/attack/abstractattackcard.h
    src/cards/attack/abstractattackcard.cpp

    src/cards/attack/strike.h
    src/cards/attack/strike.cpp

    src/cards/attack/bludgeon.h
    src/cards/attack/bludgeon.cpp

    src/cards/attack/carnage.h
    src/cards/attack/carnage.cpp

    src/cards/attack/twin_strike.h
    src/cards/attack/twin_strike.cpp

    # Entity
    src/entity/abstractentity.h
    src/entity/abstractentity.cpp

    src/entity/abstractenemy.h
    src/entity/abstractenemy.cpp

    src/entity/ironclad.h
    src/entity/ironclad.cpp

    # Powers
    src/items/powers/abstractpower.h
    src/items/powers/abstractpower.cpp

    src/items/powers/strengthpower.h
    src/items/powers/strengthpower.cpp

    src/items/powers/dexteritypower.h
    src/items/powers/dexteritypower.cpp

    src/items/powers/metallicizepower.h
    src/items/powers/metallicizepower.cpp

    src/items/powers/vulnerablePower.h
    src/items/powers/vulnerablePower.cpp

    src/items/powers/weakpower.h
    src/items/powers/weakpower.cpp

    src/items/powers/frailPower.h
    src/items/powers/frailPower.cpp

    src/items/powers/ritualpower.h
    src/items/powers/ritualpower.cpp

    src/items/powers/barricadepower.h
    src/items/powers/barricadepower.cpp

    src/items/powers/powerfactory.h
    src/items/powers/powerfactory.cpp

    # Potions
    src/items/potions/abstractpotion.h
    src/items/potions/abstractpotion.cpp

    src/items/potions/blockpotion.h
    src/items/potions/blockpotion.cpp

    src/items/potions/firepotion.h
    src/items/potions/firepotion.cpp

    # Categories
    src/categories/cards.h
    src/categories/enemies.h
    src/categories/powers.h
    src/categories/potions.h
    src/items/potions/abstractpotion.h src/items/potions/abstractpotion.cpp
    src/items/potions/blockpotion.h src/items/potions/blockpotion.cpp
    src/items/potions/abstractpotion.cpp src/items/potions/abstractpotion.h src/items/potions/blockpotion.cpp src/items/potions/blockpotion.h src/items/potions/firepotion.cpp src/items/potions/firepotion.h
    src/cards/attack/abstractattackcard.cpp src/cards/attack/abstractattackcard.h src/cards/attack/bash.cpp src/cards/attack/bash.h src/cards/attack/bludgeon.cpp src/cards/attack/bludgeon.h src/cards/attack/carnage.cpp src/cards/attack/carnage.h src/cards/attack/hemokinesis.cpp src/cards/attack/hemokinesis.h src/cards/attack/strike.cpp src/cards/attack/strike.h src/cards/attack/twin_strike.cpp src/cards/attack/twin_strike.h src/cards/attack/uppercut.cpp src/cards/attack/uppercut.h
    src/cards/skill/abstractskillcard.cpp src/cards/skill/abstractskillcard.h
    src/cards/skill/abstractskillcard.cpp src/cards/skill/abstractskillcard.h src/cards/skill/defend.cpp src/cards/skill/defend.h
    src/cards/skill/abstractskillcard.cpp src/cards/skill/abstractskillcard.h src/cards/skill/defend.cpp src/cards/skill/defend.h src/cards/skill/limitbreak.cpp src/cards/skill/limitbreak.h
    src/cards/skill/abstractskillcard.cpp src/cards/skill/abstractskillcard.h src/cards/skill/defend.cpp src/cards/skill/defend.h src/cards/skill/impervious.cpp src/cards/skill/impervious.h src/cards/skill/limitbreak.cpp src/cards/skill/limitbreak.h
    src/cards/skill/abstractskillcard.cpp src/cards/skill/abstractskillcard.h src/cards/skill/defend.cpp src/cards/skill/defend.h src/cards/skill/entrench.cpp src/cards/skill/entrench.h src/cards/skill/impervious.cpp src/cards/skill/impervious.h src/cards/skill/limitbreak.cpp src/cards/skill/limitbreak.h
    src/cards/skill/abstractskillcard.cpp src/cards/skill/abstractskillcard.h src/cards/skill/defend.cpp src/cards/skill/defend.h src/cards/skill/disarm.cpp src/cards/skill/disarm.h src/cards/skill/entrench.cpp src/cards/skill/entrench.h src/cards/skill/impervious.cpp src/cards/skill/impervious.h src/cards/skill/limitbreak.cpp src/cards/skill/limitbreak.h
    src/cards/power/abstractpowercard.cpp src/cards/power/abstractpowercard.h
    src/cards/power/inflame.cpp src/cards/power/inflame.h
    src/cards/power/metallicize.cpp src/cards/power/metallicize.h
    src/cards/power/barricade.cpp src/cards/power/barricade.h
    src/cards/status/abstractstatuscard.cpp src/cards/status/abstractstatuscard.h
    src/cards/status/dazed.cpp src/cards/status/dazed.h
    src/cards/status/slimed.cpp src/cards/status/slimed.h src/cards/status/wound.cpp src/cards/status/wound.h
    src/cards/curse/abstractcursecard.cpp src/cards/curse/abstractcursecard.h
    src/cards/curse/curse_of_the_bell.cpp src/cards/curse/curse_of_the_bell.h
    src/cards/skill/jax.cpp src/cards/skill/jax.h
    src/items/powers/demonformpower.cpp src/items/powers/demonformpower.h
    src/cards/power/demon_form.cpp src/cards/power/demon_form.h
    src/categories/intents.h
    src/items/enemyIntent.h
    src/utils/RNG.h
    src/entity/cultist.h src/entity/cultist.cpp
    src/entity/jaw_worm.cpp src/entity/jaw_worm.h
    src/items/powers/curluppower.cpp src/items/powers/curluppower.h
    src/entity/red_louse.cpp src/entity/red_louse.h
    src/entity/green_louse.cpp src/entity/green_louse.h
    src/entity/blue_slaver.cpp src/entity/blue_slaver.h
    src/entity/small_slime.cpp src/entity/small_slime.h
    src/entity/spheric_guardian.cpp src/entity/spheric_guardian.h
    src/entity/the_champ.cpp src/entity/the_champ.h
    src/categories/relics.h

    # Utils
    src/utils/RNG.h

    # Map
    src/map/map.h
    src/map/map.cpp

    src/cards/cardfactory.h src/cards/cardfactory.cpp
    src/combat/manageCombat/combat_manager.h src/combat/manageCombat/combat_manager.cpp
    resources.qrc
    src/cards/attack/abstractattackcard.cpp
    src/cards/attack/abstractattackcard.h
    src/cards/attack/bash.cpp src/cards/attack/bash.h
    src/cards/attack/blood_for_blood.cpp
    src/cards/attack/blood_for_blood.h
    src/cards/attack/bludgeon.cpp
    src/cards/attack/bludgeon.h
    src/cards/attack/carnage.cpp
    src/cards/attack/carnage.h
    src/cards/attack/clash.cpp
    src/cards/attack/clash.h
    src/cards/attack/feed.cpp
    src/cards/attack/feed.h
    src/cards/attack/heavy_blade.cpp
    src/cards/attack/heavy_blade.h
    src/cards/attack/hemokinesis.cpp
    src/cards/attack/hemokinesis.h
    src/cards/attack/immolate.cpp
    src/cards/attack/immolate.h
    src/cards/attack/perfected_strike.cpp
    src/cards/attack/perfected_strike.h
    src/cards/attack/pommel_strike.cpp
    src/cards/attack/pommel_strike.h
    src/cards/attack/reaper.cpp
    src/cards/attack/reaper.h
    src/cards/attack/strike.cpp
    src/cards/attack/strike.h
    src/cards/attack/twin_strike.cpp
    src/cards/attack/twin_strike.h
    src/cards/attack/uppercut.cpp
    src/cards/attack/uppercut.h
    src/cards/attack/whirlwind.cpp
    src/cards/attack/whirlwind.h
    src/cards/curse/abstractcursecard.cpp
    src/cards/curse/abstractcursecard.h
    src/cards/curse/curse_of_the_bell.cpp
    src/cards/curse/curse_of_the_bell.h
    src/cards/curse/pain.cpp
    src/cards/curse/pain.h
    src/cards/curse/regret.cpp
    src/cards/curse/regret.h
    src/cards/curse/writhe.cpp
    src/cards/curse/writhe.h
    src/cards/power/abstractpowercard.cpp
    src/cards/power/abstractpowercard.h
    src/cards/power/barricade.cpp
    src/cards/power/barricade.h
    src/cards/power/berserk.cpp
    src/cards/power/berserk.h
    src/cards/power/brutality.cpp
    src/cards/power/brutality.h
    src/cards/power/dark_embrace.cpp
    src/cards/power/dark_embrace.h
    src/cards/power/demon_form.cpp
    src/cards/power/demon_form.h
    src/cards/power/feel_no_pain.cpp
    src/cards/power/feel_no_pain.h
    src/cards/power/inflame.cpp
    src/cards/power/inflame.h
    src/cards/power/metallicize.cpp
    src/cards/power/metallicize.h
    src/cards/skill/abstractskillcard.cpp
    src/cards/skill/abstractskillcard.h
    src/cards/skill/battle_trance.cpp
    src/cards/skill/battle_trance.h
    src/cards/skill/bloodletting.cpp
    src/cards/skill/bloodletting.h
    src/cards/skill/defend.cpp
    src/cards/skill/defend.h
    src/cards/skill/disarm.cpp
    src/cards/skill/disarm.h
    src/cards/skill/dual_wield.cpp
    src/cards/skill/dual_wield.h
    src/cards/skill/entrench.cpp
    src/cards/skill/entrench.h
    src/cards/skill/exhume.cpp
    src/cards/skill/exhume.h
    src/cards/skill/impervious.cpp
    src/cards/skill/impervious.h
    src/cards/skill/jax.cpp
    src/cards/skill/jax.h
    src/cards/skill/limitbreak.cpp
    src/cards/skill/limitbreak.h
    src/cards/skill/offering.cpp
    src/cards/skill/offering.h
    src/cards/skill/power_through.cpp
    src/cards/skill/power_through.h
    src/cards/skill/rage.cpp
    src/cards/skill/rage.h
    src/cards/skill/shrug_it_off.cpp
    src/cards/skill/shrug_it_off.h
    src/cards/skill/spot_weakness.cpp
    src/cards/skill/spot_weakness.h
    src/cards/skill/true_grit.cpp
    src/cards/skill/true_grit.h
    src/cards/skill/warcry.cpp
    src/cards/skill/warcry.h
    src/cards/status/abstractstatuscard.cpp
    src/cards/status/abstractstatuscard.h
    src/cards/status/burn.cpp
    src/cards/status/burn.h
    src/cards/status/dazed.cpp
    src/cards/status/dazed.h
    src/cards/status/slimed.cpp
    src/cards/status/slimed.h
    src/cards/status/wound.cpp
    src/cards/status/wound.h
    src/cards/abstractcard.cpp
    src/cards/abstractcard.h
    src/cards/cardfactory.cpp
    src/cards/cardfactory.h
    src/categories/cards.h
    src/categories/enemies.h
    src/categories/general.h
    src/categories/intents.h
    src/categories/potions.h
    src/categories/powers.h
    src/categories/relics.h
    src/combat/manageCombat/combat_manager.cpp
    src/combat/manageCombat/combat_manager.h
    src/combat/manageCombat/combatrewards.h
    src/items/relics/black_star_relic.cpp src/items/relics/black_star_relic.h
    src/events/UnknownMap.h
    src/categories/unknowns.h
    src/events/ominousforge.h src/events/ominousforge.cpp
    src/Events/goldenidol.h src/Events/goldenidol.cpp
    src/Events/augmenter.h src/Events/augmenter.cpp
    src/Events/facetrader.h src/Events/facetrader.cpp
    src/Events/goldenshrine.h src/Events/goldenshrine.cpp
    src/Events/lab.h src/Events/lab.cpp
    src/Events/thecleric.h src/Events/thecleric.cpp
    src/Events/shininglight.h src/Events/shininglight.cpp
    src/Events/ancientwriting.h src/Events/ancientwriting.cpp
    src/Events/pleadingvagrant.h src/Events/pleadingvagrant.cpp
    src/items/relics/golden_idol_relic.cpp src/items/relics/golden_idol_relic.h
    src/cards/curse/injury.cpp src/cards/curse/injury.h
    src/cards/curse/shame.cpp src/cards/curse/shame.h
    src/Events/bonfirespirits.h src/Events/bonfirespirits.cpp
    src/Events/thessssserpent.h src/Events/thessssserpent.cpp
    src/Events/joust.h src/Events/joust.cpp
    src/cards/curse/doubt.cpp src/cards/curse/doubt.h



    src/core/login/stats.h src/core/login/stats.cpp
    src/core/login/player.h src/core/login/player.cpp
    src/core/login/leaderboard.h src/core/login/leaderboard.cpp
    src/core/login/filemanager.h src/core/login/filemanager.cpp
    src/ui/loginpage.h src/ui/loginpage.cpp src/ui/loginpage.ui
    src/ui/registerpage.h src/ui/registerpage.cpp src/ui/registerpage.ui
    src/ui/forgotpasswordpage.h src/ui/forgotpasswordpage.cpp src/ui/forgotpasswordpage.ui
    src/core/setting.h

    src/core/menu/menu.h src/core/menu/menu.cpp src/core/menu/menu.ui
    src/core/menu/playmenu.h src/core/menu/playmenu.cpp src/core/menu/playmenu.ui
    src/core/menu/menu.h src/core/menu/menu.cpp
    src/core/menu/menu.h src/core/menu/menu.cpp src/core/menu/menu.ui
    src/core/menu/statisticsmenu.h src/core/menu/statisticsmenu.cpp src/core/menu/statisticsmenu.ui
    src/places/shop/merchant.cpp src/places/shop/merchant.h src/places/shop/shopitem.cpp src/places/shop/shopitem.h


    # Core
    # src/core/...

    # Cards
    # src/cards/...

    # Characters
    # src/characters/...

    # Combat
    # src/combat/...

    # Events
    # src/events/...

    # Items
    # src/items/...

    # Network
    # src/network/...

    # Utils
    # src/utils/...
    src/combat/.gitkeep
    src/combat/attack_info.h
    src/combat/blocking_info.h
    src/combat/combat_event.h
    src/combat/damage_info.h
    src/combat/drink_potion_info.h
    src/combat/game_action.cpp
    src/combat/game_action.h
    src/combat/play_card_info.h
    src/combat/play_info.h
    src/core/.gitkeep
    src/entity/abstractenemy.cpp
    src/entity/abstractenemy.h
    src/entity/abstractentity.cpp
    src/entity/abstractentity.h
    src/entity/blue_slaver.cpp
    src/entity/blue_slaver.h
    src/entity/book_of_stabbing.cpp
    src/entity/book_of_stabbing.h
    src/entity/cultist.cpp
    src/entity/cultist.h
    src/entity/green_louse.cpp
    src/entity/green_louse.h
    src/entity/gremlin_nob.cpp
    src/entity/gremlin_nob.h
    src/entity/hexaghost.cpp
    src/entity/hexaghost.h
    src/entity/ironclad.cpp
    src/entity/ironclad.h
    src/entity/jaw_worm.cpp
    src/entity/jaw_worm.h
    src/entity/large_slime.cpp
    src/entity/large_slime.h
    src/entity/looter.cpp
    src/entity/looter.h
    src/entity/medium_slime.cpp
    src/entity/medium_slime.h
    src/entity/mugger.cpp
    src/entity/mugger.h
    src/entity/red_louse.cpp
    src/entity/red_louse.h
    src/entity/red_slaver.cpp
    src/entity/red_slaver.h
    src/entity/sentry.cpp
    src/entity/sentry.h
    src/entity/slime_boss.cpp
    src/entity/slime_boss.h
    src/entity/small_slime.cpp
    src/entity/small_slime.h
    src/entity/spheric_guardian.cpp
    src/entity/spheric_guardian.h
    src/entity/taskmaster.cpp
    src/entity/taskmaster.h
    src/entity/the_champ.cpp
    src/entity/the_champ.h
    src/events/.gitkeep
    src/items/potions/abstractpotion.cpp
    src/items/potions/abstractpotion.h
    src/items/potions/blockpotion.cpp
    src/items/potions/blockpotion.h
    src/items/potions/cultistpotion.cpp
    src/items/potions/cultistpotion.h
    src/items/potions/dexteritypotion.cpp
    src/items/potions/dexteritypotion.h
    src/items/potions/energypotion.cpp
    src/items/potions/energypotion.h
    src/items/potions/explosivepotion.cpp
    src/items/potions/explosivepotion.h
    src/items/potions/fairyinabottle.cpp
    src/items/potions/fairyinabottle.h
    src/items/potions/fearpotion.cpp
    src/items/potions/fearpotion.h
    src/items/potions/firepotion.cpp
    src/items/potions/firepotion.h
    src/items/potions/potionfactory.cpp
    src/items/potions/potionfactory.h
    src/items/potions/strengthpotion.cpp
    src/items/potions/strengthpotion.h
    src/items/potions/swiftpotion.cpp
    src/items/potions/swiftpotion.h
    src/items/potions/weakpotion.cpp
    src/items/potions/weakpotion.h
    src/items/potions/whitebloodpotion.cpp
    src/items/potions/whitebloodpotion.h
    src/items/powers/abstractpower.cpp
    src/items/powers/abstractpower.h
    src/items/powers/barricadepower.cpp
    src/items/powers/barricadepower.h
    src/items/powers/berserkpower.cpp
    src/items/powers/berserkpower.h
    src/items/powers/brutalitypower.cpp
    src/items/powers/brutalitypower.h
    src/items/powers/curluppower.cpp
    src/items/powers/curluppower.h
    src/items/powers/darkembracepower.cpp
    src/items/powers/darkembracepower.h
    src/items/powers/demonformpower.cpp
    src/items/powers/demonformpower.h
    src/items/powers/dexteritypower.cpp
    src/items/powers/dexteritypower.h
    src/items/powers/enragepower.cpp
    src/items/powers/enragepower.h
    src/items/powers/entangledpower.cpp
    src/items/powers/entangledpower.h
    src/items/powers/feelnopainpower.cpp
    src/items/powers/feelnopainpower.h
    src/items/powers/frailpower.cpp
    src/items/powers/frailpower.h
    src/items/powers/metallicizepower.cpp
    src/items/powers/metallicizepower.h
    src/items/powers/painfulstabpower.cpp
    src/items/powers/painfulstabpower.h
    src/items/powers/powerfactory.cpp
    src/items/powers/powerfactory.h
    src/items/powers/ragepower.cpp
    src/items/powers/ragepower.h
    src/items/powers/ritualpower.cpp
    src/items/powers/ritualpower.h
    src/items/powers/strengthpower.cpp
    src/items/powers/strengthpower.h
    src/items/powers/thieverypower.cpp
    src/items/powers/thieverypower.h
    src/items/powers/vulnerablePower.cpp
    src/items/powers/vulnerablePower.h
    src/items/powers/weakpower.cpp
    src/items/powers/weakpower.h
    src/items/relics/abstractrelic.cpp
    src/items/relics/abstractrelic.h
    src/items/relics/anchor_relic.cpp
    src/items/relics/anchor_relic.h
    src/items/relics/bag_of_marbles_relic.cpp
    src/items/relics/bag_of_marbles_relic.h
    src/items/relics/black_star_relic.cpp
    src/items/relics/black_star_relic.h
    src/items/relics/blood_vial_relic.cpp
    src/items/relics/blood_vial_relic.h
    src/items/relics/burning_blood_relic.cpp
    src/items/relics/burning_blood_relic.h
    src/items/relics/calling_bell_relic.cpp
    src/items/relics/calling_bell_relic.h
    src/items/relics/captains_wheel_relic.cpp
    src/items/relics/captains_wheel_relic.h
    src/items/relics/centennial_puzzle_relic.cpp
    src/items/relics/centennial_puzzle_relic.h
    src/items/relics/girya_relic.cpp
    src/items/relics/girya_relic.h
    src/items/relics/greenback_relic.cpp
    src/items/relics/greenback_relic.h
    src/items/relics/gremlin_horn_relic.cpp
    src/items/relics/gremlin_horn_relic.h
    src/items/relics/gremlin_visage_relic.cpp
    src/items/relics/gremlin_visage_relic.h
    src/items/relics/happy_flower_relic.cpp
    src/items/relics/happy_flower_relic.h
    src/items/relics/helmet_of_the_cleric_relic.cpp
    src/items/relics/helmet_of_the_cleric_relic.h
    src/items/relics/horn_cleat_relic.cpp
    src/items/relics/horn_cleat_relic.h
    src/items/relics/ice_cream_relic.cpp
    src/items/relics/ice_cream_relic.h
    src/items/relics/kunai_relic.cpp
    src/items/relics/kunai_relic.h
    src/items/relics/mark_of_pain_relic.cpp
    src/items/relics/mark_of_pain_relic.h
    src/items/relics/mutagenic_strength_relic.cpp
    src/items/relics/mutagenic_strength_relic.h
    src/items/relics/oddly_smooth_stone_relic.cpp
    src/items/relics/oddly_smooth_stone_relic.h
    src/items/relics/philosophers_stone_relic.cpp
    src/items/relics/philosophers_stone_relic.h
    src/items/relics/preserved_insect_relic.cpp
    src/items/relics/preserved_insect_relic.h
    src/items/relics/red_mask_relic.cpp
    src/items/relics/red_mask_relic.h
    src/items/relics/red_skull_relic.cpp
    src/items/relics/red_skull_relic.h
    src/items/relics/relicfactory.cpp
    src/items/relics/relicfactory.h
    src/items/relics/shuriken_relic.cpp
    src/items/relics/shuriken_relic.h
    src/items/relics/slavers_collar_relic.cpp
    src/items/relics/slavers_collar_relic.h
    src/items/relics/sozu_relic.cpp
    src/items/relics/sozu_relic.h
    src/items/relics/the_boot_relic.cpp
    src/items/relics/the_boot_relic.h
    src/items/relics/tungsten_rod_relic.cpp
    src/items/relics/tungsten_rod_relic.h
    src/items/relics/vajra_relic.cpp
    src/items/relics/vajra_relic.h
    src/items/relics/velvet_choker_relic.cpp
    src/items/relics/velvet_choker_relic.h
    src/items/relics/warped_tongs_relic.cpp
    src/items/relics/warped_tongs_relic.h
    src/items/enemyIntent.h
    src/network/.gitkeep
    src/ui/combatpage.cpp
    src/ui/combatpage.h
    src/ui/mainwindow.cpp
    src/ui/mainwindow.h
    src/ui/mainwindow.ui
    src/utils/.gitkeep
    src/utils/RNG.h
    src/main.cpp
    src/ui/baseitem.h src/ui/baseitem.cpp
    src/ui/imageitem.h src/ui/imageitem.cpp
    src/ui/textitem.h src/ui/textitem.cpp

    src/ui/cards/cardparent.cpp src/ui/cards/cardparent.h
    src/ui/cards/cardtemplatecommon.h src/ui/cards/cardtemplatecommon.cpp

    src/core/setting.h
    src/ui/cards/cardtemplateuncommon.cpp src/ui/cards/cardtemplateuncommon.h
    src/ui/cards/cardtemplaterare.cpp src/ui/cards/cardtemplaterare.h
    src/ui/cards/cardtemplatelegend.cpp src/ui/cards/cardtemplatelegend.h
    src/ui/entities/simplehpbar.h src/ui/entities/simplehpbar.cpp
    src/ui/entities/entityparent.h src/ui/entities/entityparent.cpp
    src/ui/entities/abstractentityitem.h src/ui/entities/abstractentityitem.cpp
    src/ui/entities/ironcladitem.h src/ui/entities/ironcladitem.cpp






    src/ui/entities/getvisualdata.h
    src/ui/entities/enemyitem.cpp src/ui/entities/enemyitem.h

    src/ui/cards/abstractcardtemplate.h src/ui/cards/abstractcardtemplate.cpp
    src/ui/effects/abstracteffect.h
    src/ui/effects/entitycornersframe.h src/ui/effects/entitycornersframe.cpp
    src/ui/effects/getDamageEffect.h
    src/ui/effects/damageeffect.h src/ui/effects/damageeffect.cpp
    src/ui/effects/DamageParticleManager.h src/ui/effects/DamageParticleManager.cpp
    src/ui/topbar/combattopbar.h src/ui/topbar/combattopbar.cpp
    src/items/relics/spirit_poop_relic.cpp src/items/relics/spirit_poop_relic.h
    src/ui/relicbar/relicbar.h src/ui/relicbar/relicbar.cpp

    src/ui/entities/potionparent.h src/ui/entities/potionparent.cpp
    src/ui/infobar/abstractinfobar.h
    src/ui/infobar/infobarparent.h src/ui/infobar/infobarparent.cpp
    src/ui/infobar/combatinfobar.h src/ui/infobar/combatinfobar.cpp
    src/ui/relicbar/relicparent.cpp src/ui/relicbar/relicparent.h
    src/ui/entities/powerparent.cpp src/ui/entities/powerparent.h
    src/ui/selectItem/selectcard.h src/ui/selectItem/selectcard.cpp
    src/ui/selectItem/selectcard.h src/ui/selectItem/selectcard.cpp
    src/ui/selectItem/collectreward.cpp src/ui/selectItem/collectreward.h
    src/assetsManager/imagemanager.h src/assetsManager/imagemanager.cpp
    src/assetsManager/soundmanager.h src/assetsManager/soundmanager.cpp
    src/items/relics/cultist_headpiece_relic.cpp src/items/relics/cultist_headpiece_relic.h
    src/ui/topbar/combatsetting.cpp src/ui/topbar/combatsetting.h
    src/ui/treasure/treasurepage.h src/ui/treasure/treasurepage.cpp
    src/ui/selectItem/selectrelic.cpp src/ui/selectItem/selectrelic.h
    src/ui/store/storepage.cpp src/ui/store/storepage.h
    src/ui/mappage/mappage.cpp src/ui/mappage/mappage.h
    src/ui/mappage/scrollsection.h src/ui/mappage/scrollsection.cpp
    src/ui/mappage/mapItems.h
    src/ui/mappage/sketchline.h src/ui/mappage/sketchline.cpp
    src/ui/unknownpage/unknownpage.cpp src/ui/unknownpage/unknownpage.h
    src/ui/selectItem/selectpotion.cpp src/ui/selectItem/selectpotion.h
    src/ui/restpage/restpage.cpp src/ui/restpage/restpage.h
    src/items/relics/cursed_key_relic.cpp src/items/relics/cursed_key_relic.h src/items/relics/lively_plant_relic.cpp src/items/relics/lively_plant_relic.h
    src/core/gameflowcontroller.h src/core/gameflowcontroller.cpp
    src/ui/selectItem/startingselect.h src/ui/selectItem/startingselect.cpp

)

target_include_directories(SlayTheSpire PRIVATE
    ${CMAKE_SOURCE_DIR}/src
)

target_link_libraries(SlayTheSpire PRIVATE
    Qt6::Widgets
    Qt6::Core
    Qt6::Gui
    Qt6::Network
    Qt6::Multimedia
)
if(WIN32)
    if(MSVC)
        set_target_properties(SlayTheSpire PROPERTIES
            LINK_FLAGS "/SUBSYSTEM:CONSOLE"
        )
    else()
        set_target_properties(SlayTheSpire PROPERTIES
            LINK_FLAGS "-Wl,-subsystem,console"
        )
    endif()
endif()
