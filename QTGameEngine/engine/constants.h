#ifndef CONSTANTS_H
#define CONSTANTS_H
#include <QString>
#include <QRectF>
#include <QPoint>
#include <QColor>
#include "enums/enums.h"

const bool USE_OPENGL = true;
const bool USE_ANTYALIASING = false;
const int WINDOW_TIMER_MSEC = 30;

// BACKGROUND
const QColor BG_COLOR(200,200,200);

// STRINGS
const QString STRING_SLASH = "/";
const QString STRING_COLON = ":";
const QString STRING_DOT = ".";
const QString STRING_EXT_MP3 = ".mp3";
const QString STRING_EXT_PNG = ".png";

// DIGITS
const int THOUSAND = 1000;

// CODES
const int CODE_NOT_INITIALIZED = -1;
const int CODE_ERROR = -99;

// PATHS
const QString PATH_RESOURCES = STRING_COLON + STRING_SLASH + "resources" + STRING_SLASH;
const QString PATH_ANIMATIONS = PATH_RESOURCES + "animations" + STRING_SLASH;
const QString PATH_SPRITES = PATH_RESOURCES + "sprites" + STRING_SLASH;
const QString PATH_SOUNDS = "qrc" + PATH_RESOURCES + "sounds" + STRING_SLASH;

// ITEM CONSTS
const int ITEM_MAX_HEALTH = 100;
const int ITEM_HEALTH_NOT_INIT = -99;
const QPoint ITEM_ZERO_POS(0,0);
const QRectF ITEM_ZERO_SQUARE(0,0,0,0);
const qreal PARTICLE_MIN_SCALE = 1e-320;

// MOVING CONST
const QPointF MOVE_LEFT_02(-0.2, 0);
const QPointF MOVE_LEFT_03(-0.3, 0);
const QPointF MOVE_LEFT_05(-0.5, 0);
const QPointF MOVE_LEFT_07(-0.7, 0);
const QPointF MOVE_LEFT_1(-1, 0);
const QPointF MOVE_LEFT_2(-2, 0);
const QPointF MOVE_LEFT_3(-3, 0);

#endif // CONSTANTS_H
