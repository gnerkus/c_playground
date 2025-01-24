//
// Created by nanotome on 12/27/2024.
//

#ifndef VECTOROGUE_LOADING_H
#define VECTOROGUE_LOADING_H

#include "raylib.h"

#define MAX_TEXTURES_TO_LOAD 10

struct SpriteInfo {
    int TextureId;
    int originX;
    int originY;
};

extern struct SpriteInfo Sprites[32];
extern Texture2D Textures[MAX_TEXTURES_TO_LOAD];
extern Music gameplayMusic;

void InitResources();
void CleanupResources();

void UpdateLoad();

#endif //VECTOROGUE_LOADING_H
