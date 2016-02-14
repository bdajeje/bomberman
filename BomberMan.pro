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
    graphics/animation.cpp

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
    graphics/animation.hpp
