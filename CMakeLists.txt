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
    src/combat/.gitkeep src/core/.gitkeep src/events/.gitkeep src/items/buffs/.gitkeep src/items/potions/.gitkeep src/items/relics/.gitkeep src/network/.gitkeep src/ui/mainwindow.cpp src/ui/mainwindow.h src/ui/mainwindow.ui src/utils/.gitkeep src/main.cpp
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
    src/core/menu/menu.h src/core/menu/menu.cpp

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