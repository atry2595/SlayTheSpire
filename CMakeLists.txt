cmake_minimum_required(VERSION 3.16)
project(SlayTheSpire VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUROUIC ON)

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
    src/main.cpp
    src/ui/mainwindow.h
    src/ui/mainwindow.cpp
    src/ui/mainwindow.ui
    src/ui/mainwindow.cpp src/ui/mainwindow.h src/ui/mainwindow.ui src/main.cpp
    resources.qrc
    src/combat/attack_info.h
    src/combat/damage_info.h
    src/combat/combat_event.h
    src/combat/game_action.h src/combat/game_action.cpp
    src/cards/abstractcard.h src/cards/abstractcard.cpp
    src/cards/attack/abstractattackcard.h src/cards/attack/abstractattackcard.cpp
    src/cards/attack/strike.h src/cards/attack/strike.cpp
    src/cards/attack/abstractattackcard.cpp src/cards/attack/abstractattackcard.h src/cards/attack/bludgeon.cpp src/cards/attack/bludgeon.h src/cards/attack/carnage.cpp src/cards/attack/carnage.h src/cards/attack/strike.cpp src/cards/attack/strike.h src/cards/attack/twin_strike.cpp src/cards/attack/twin_strike.h src/cards/abstractcard.cpp src/cards/abstractcard.h
    src/combat/play_info.h
    src/entity/abstractentity.h src/entity/abstractentity.cpp
    src/entity/abstractenemy.h src/entity/abstractenemy.cpp
    src/entity/ironclad.h src/entity/ironclad.cpp
    src/combat/play_info.h
    src/items/powers/abstractpower.h src/items/powers/abstractpower.cpp
    src/items/powers/abstractpower.h
    src/items/powers/abstractpower.cpp src/items/powers/abstractpower.h
    src/items/powers/abstractpower.cpp
    src/items/powers/abstractpower.cpp
    src/items/powers/strengthpower.h src/items/powers/strengthpower.cpp
    src/combat/blocking_info.h
    src/items/powers/dexteritypower.h src/items/powers/dexteritypower.cpp
    src/items/powers/abstractpower.cpp src/items/powers/abstractpower.h src/items/powers/dexteritypower.cpp src/items/powers/dexteritypower.h src/items/powers/metallicizePower.cpp src/items/powers/metallicizePower.h src/items/powers/strengthpower.cpp src/items/powers/strengthpower.h
    src/items/powers/abstractpower.cpp src/items/powers/abstractpower.h src/items/powers/dexteritypower.cpp src/items/powers/dexteritypower.h src/items/powers/metallicizePower.cpp src/items/powers/metallicizePower.h src/items/powers/strengthpower.cpp src/items/powers/strengthpower.h src/items/powers/vulnerablePower.cpp src/items/powers/vulnerablePower.h
    src/items/powers/abstractpower.cpp src/items/powers/abstractpower.h src/items/powers/dexteritypower.cpp src/items/powers/dexteritypower.h src/items/powers/metallicizePower.cpp src/items/powers/metallicizePower.h src/items/powers/strengthpower.cpp src/items/powers/strengthpower.h src/items/powers/vulnerablePower.cpp src/items/powers/vulnerablePower.h src/items/powers/weakpower.cpp src/items/powers/weakpower.h
    src/items/powers/abstractpower.cpp src/items/powers/abstractpower.h src/items/powers/dexteritypower.cpp src/items/powers/dexteritypower.h src/items/powers/frailpower.cpp src/items/powers/frailpower.h src/items/powers/metallicizePower.cpp src/items/powers/metallicizePower.h src/items/powers/strengthpower.cpp src/items/powers/strengthpower.h src/items/powers/vulnerablePower.cpp src/items/powers/vulnerablePower.h src/items/powers/weakpower.cpp src/items/powers/weakpower.h
    src/items/powers/abstractpower.cpp src/items/powers/abstractpower.h src/items/powers/dexteritypower.cpp src/items/powers/dexteritypower.h src/items/powers/frailPower.cpp src/items/powers/frailPower.h src/items/powers/metallicizePower.cpp src/items/powers/metallicizePower.h src/items/powers/ritualpower.cpp src/items/powers/ritualpower.h src/items/powers/strengthpower.cpp src/items/powers/strengthpower.h src/items/powers/vulnerablePower.cpp src/items/powers/vulnerablePower.h src/items/powers/weakpower.cpp src/items/powers/weakpower.h
    src/categories/powers.h
    src/items/powers/powerfactory.h src/items/powers/powerfactory.cpp
    src/items/powers/abstractpower.cpp src/items/powers/abstractpower.h src/items/powers/barricadepower.cpp src/items/powers/barricadepower.h src/items/powers/dexteritypower.cpp src/items/powers/dexteritypower.h src/items/powers/frailPower.cpp src/items/powers/frailPower.h src/items/powers/metallicizePower.cpp src/items/powers/metallicizePower.h src/items/powers/powerfactory.cpp src/items/powers/powerfactory.h src/items/powers/ritualpower.cpp src/items/powers/ritualpower.h src/items/powers/strengthpower.cpp src/items/powers/strengthpower.h src/items/powers/vulnerablePower.cpp src/items/powers/vulnerablePower.h src/items/powers/weakpower.cpp src/items/powers/weakpower.h
    src/items/powers/abstractpower.cpp src/items/powers/abstractpower.h src/items/powers/barricadepower.cpp src/items/powers/barricadepower.h src/items/powers/dexteritypower.cpp src/items/powers/dexteritypower.h src/items/powers/frailPower.cpp src/items/powers/frailPower.h src/items/powers/metallicizePower.cpp src/items/powers/metallicizePower.h src/items/powers/powerfactory.cpp src/items/powers/powerfactory.h src/items/powers/ritualpower.cpp src/items/powers/ritualpower.h src/items/powers/strengthpower.cpp src/items/powers/strengthpower.h src/items/powers/vulnerablePower.cpp src/items/powers/vulnerablePower.h src/items/powers/weakpower.cpp src/items/powers/weakpower.h
    src/items/powers/frailpower.h src/items/powers/frailpower.cpp
    src/categories/cards.h
    src/categories/enemies.h
    src/categories/relics.h
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

    src/cards/cardfactory.h src/cards/cardfactory.cpp
    src/combat/manageCombat/combat_manager.h src/combat/manageCombat/combat_manager.cpp
    src/categories/general.h

    src/combat/play_card_info.h
    src/combat/drink_potion_info.h
    src/cards/attack/reaper.cpp src/cards/attack/reaper.h
    src/cards/attack/feed.cpp src/cards/attack/reaper.cpp
    src/cards/attack/feed.h
    src/cards/attack/immolate.cpp src/cards/attack/immolate.h
    src/cards/attack/whirlwind.cpp src/cards/attack/whirlwind.h
    src/cards/attack/blood_for_blood.cpp src/cards/attack/blood_for_blood.h
    src/cards/attack/perfected_strike.cpp src/cards/attack/perfected_strike.h
    src/cards/attack/clash.cpp src/cards/attack/clash.h
    src/cards/attack/heavy_blade.cpp src/cards/attack/heavy_blade.h
    src/cards/attack/pommel_strike.cpp src/cards/attack/pommel_strike.h
    src/cards/skill/exhume.cpp src/cards/skill/exhume.h
    src/cards/skill/offering.cpp src/cards/skill/offering.h
    src/cards/skill/dual_wield.cpp src/cards/skill/dual_wield.h
    src/cards/skill/warcry.cpp src/cards/skill/warcry.h
    src/cards/skill/true_grit.cpp src/cards/skill/true_grit.h
    src/cards/skill/shrug_it_off.cpp src/cards/skill/shrug_it_off.h
    src/cards/skill/power_through.cpp src/cards/skill/power_through.h
    src/cards/skill/bloodletting.cpp src/cards/skill/bloodletting.h
    src/cards/skill/battle_trance.cpp src/cards/skill/battle_trance.h
    src/cards/skill/spot_weakness.cpp src/cards/skill/spot_weakness.h
    src/cards/skill/rage.cpp src/cards/skill/rage.h
    src/items/powers/ragepower.cpp src/items/powers/ragepower.h
    src/items/powers/brutalitypower.cpp src/items/powers/brutalitypower.h
    src/cards/power/brutality.cpp src/cards/power/brutality.h
    src/items/powers/feelnopainpower.cpp src/items/powers/feelnopainpower.h
    src/cards/power/feel_no_pain.cpp src/cards/power/feel_no_pain.h
    src/items/powers/darkembracepower.cpp src/items/powers/darkembracepower.h
    src/cards/power/dark_embrace.cpp src/cards/power/dark_embrace.h
    src/items/powers/berserkpower.cpp src/items/powers/berserkpower.h
    src/cards/power/berserk.cpp src/cards/power/berserk.h
    src/cards/status/burn.cpp src/cards/status/burn.h
    src/cards/curse/regret.cpp src/cards/curse/regret.h
    src/cards/curse/writhe.cpp src/cards/curse/writhe.h
    src/cards/curse/pain.cpp src/cards/curse/pain.h
    src/items/powers/enragepower.cpp src/items/powers/enragepower.h
    src/items/powers/entangledpower.cpp src/items/powers/entangledpower.h
    src/items/powers/painfulstabpower.cpp src/items/powers/painfulstabpower.h
    src/items/powers/thieverypower.cpp src/items/powers/thieverypower.h
    src/items/potions/dexteritypotion.cpp src/items/potions/dexteritypotion.h
    src/items/potions/energypotion.cpp src/items/potions/energypotion.h
    src/items/potions/explosivepotion.cpp src/items/potions/explosivepotion.h
    src/items/potions/fearpotion.cpp src/items/potions/fearpotion.h




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