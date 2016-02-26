TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    utils/timer.cpp \
    models/map.cpp \
    utils/file.cpp \
    models/tile.cpp \
    managers/texturemanager.cpp \
    utils/directory.cpp \
    models/player.cpp \
    models/ia.cpp \
    models/bomberman.cpp \
    utils/graphics.cpp \
    models/bomb.cpp \
    graphics/animation.cpp \
    managers/fontmanager.cpp \
    models/bonus.cpp \
    models/bonuspower.cpp \
    models/bonuskick.cpp \
    models/bonusspeed.cpp \
    models/bonusthrow.cpp \
    models/bonusbomb.cpp \
    graphics/hud.cpp \
    managers/soundmanager.cpp \
    graphics/effects/effect_core.cpp \
    graphics/effects/blink_effect.cpp \
    graphics/drawable.cpp \
    utils/time_trigger.cpp \
    models/game.cpp \
    graphics/main_menu.cpp \
    utils/key_limitor.cpp

QMAKE_CXXFLAGS += -std=c++11

LIBS += -lsfml-audio -lsfml-graphics -lsfml-window -lsfml-system \
        -lboost_regex -lboost_filesystem -lboost_system

HEADERS += \
    utils/timer.hpp \
    models/map.hpp \
    utils/file.hpp \
    utils/position.hpp \
    models/tile.hpp \
    managers/texturemanager.hpp \
    utils/directory.hpp \
    models/player.hpp \
    utils/graphics.hpp \
    models/ia.hpp \
    models/bomberman.hpp \
    models/bomb.hpp \
    graphics/animation.hpp \
    managers/fontmanager.hpp \
    models/bonus.hpp \
    models/bonuspower.hpp \
    models/bonuskick.hpp \
    models/bonusspeed.hpp \
    models/bonusthrow.hpp \
    models/bonusbomb.hpp \
    models/bonus_types.hpp \
    graphics/hud.hpp \
    defines.hpp \
    managers/soundmanager.hpp \
    graphics/effects/effect_interface.hpp \
    graphics/effects/effect_core.hpp \
    graphics/effects/effect.hpp \
    graphics/effects/blink_effect.hpp \
    graphics/drawable.hpp \
    utils/time_trigger.hpp \
    models/game.hpp \
    graphics/main_menu.hpp \
    utils/key_limitor.hpp
