QT += widgets opengl multimedia

TARGET = QTGameEngine
TEMPLATE = app
DEFINES += QT_NO_DEBUG_OUTPUT QT_NO_WARNING_OUTPUT

HEADERS  += \
    engine\window\window.h \
    engine\utils\utils.h \
    engine\controls\inputcontroller.h \
    engine\items\item.h \
    engine\utils\timerutils.h \
    engine\constants.h \
    engine\utils\sceneutils.h \
    engine\items\monitoritem.h \
    engine\processors\animationprocessor.h \
    engine\enums\enums.h \
    game\resources.h \
    engine\items\asset.h \
    engine\items\image.h \
    game\fighter.h \
    game\enums\dierctionsEnum.h \
    game\enums\weaponsEnum.h \
    engine\controls\controlable.h \
    game\constants.h \
    engine\window\splash.h \
    engine\processors\particlesprocessor.h \
    engine\items\itemeffect.h \
    game\weapons\weapon.h \
    game\weapons\rocket.h \
    game\enemies\ufo.h \
    engine\items\itemspawner.h \
    engine\utils\itemutils.h \
    engine/items/itemsmodifier.h \
    game/environment/clouds.h \
    game/particles/particleexplosion.h \
    engine/utils/memorymanager.h \
    engine/utils/memorytemplates.h \
    game/environment/stars.h \
    game/weapons/bullet.h \
    engine/items/cacheobject.h \
    engine/utils/cachemanager.h \
    game/enemies/asteroid.h \
    game/particles/particleexplosiondust.h \
    game/enemies/ship.h \
    game/weapons/enemyrocket.h \
    engine/utils/soundutils.h \
    game/enemies/ufo2.h \
    game/enemies/ufo3.h \
    game/environment/moon.h

SOURCES += \
    engine\main.cpp \
    engine\window\window.cpp \
    engine\utils\utils.cpp \
    engine\controls\inputcontroller.cpp \
    engine\items\item.cpp \
    engine\items\itemeffect.cpp \
    engine\utils\timerutils.cpp \
    engine\utils\sceneutils.cpp \
    engine\processors\animationprocessor.cpp \
    game\fighter.cpp \
    engine\window\splash.cpp \
    engine\processors\particlesprocessor.cpp \
    game\weapons\weapon.cpp \
    game\enemies\ufo.cpp \
    engine/utils/memorymanager.cpp \
    game/enemies/asteroid.cpp \
    game/enemies/ship.cpp \
    engine/utils/soundutils.cpp \
    game/enemies/ufo2.cpp \
    game/enemies/ufo3.cpp

RESOURCES += \
    game\GameRes.qrc
