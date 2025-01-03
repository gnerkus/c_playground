//
// Created by nanotome on 12/22/2024.
//

#ifndef VECTOROGUE_MAIN_H
#define VECTOROGUE_MAIN_H

#define RAYLIB_TILESON_IMPLEMENTATION
#include "raylib-tileson.h"

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

extern Map map;

#endif //VECTOROGUE_MAIN_H
