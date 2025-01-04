//
// Created by nanotome on 12/22/2024.
//

#ifndef VECTOROGUE_MAIN_H
#define VECTOROGUE_MAIN_H

#include "raylib.h"
#define RAYLIB_TILESON_IMPLEMENTATION
#include "raylib-tileson.h"

#define VR_WHITE (Color){ 250, 255, 247, 255 }
#define VR_GRAY (Color) { 125, 139, 144, 255 }
#define VR_DARKGRAY (Color) { 32, 53, 68, 255 }

void LoadComplete();
void StartGame();

typedef enum {
    STARTUP = 0,
    LOADING,
    MENU,
    RUNNING,
    PAUSED,
    GAMEOVER,
    QUITTING
} ApplicationStates;

extern ApplicationStates currentState;
extern int framesCounter;

extern int screenWidth;
extern int screenHeight;
extern int fps;

extern Map map;
extern Font font;

#endif //VECTOROGUE_MAIN_H
