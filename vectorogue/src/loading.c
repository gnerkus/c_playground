//
// Created by nanotome on 12/27/2024.
//
#include <stdio.h>

#include "loading.h"
#include "main.h"
#include "resource_ids.h"

#include "raylib.h"

// texture IDs
const int TILESET_TEXTURE = 0;
const int ACTORS_TEXTURE = 1;

const char *itemsToLoad[MAX_TEXTURES_TO_LOAD];

static int loadedCount = 0;
static bool mapLoaded = false;

// loot sprites
int EMPTY_LOOT_SPRITE;
int POTION_LOOT_SPRITE;
int COIN_LOOT_SPRITE;

// arrow sprites
int DOWN_ARROW_SPRITE;
int RIGHT_ARROW_SPRITE;
int UP_ARROW_SPRITE;
int LEFT_ARROW_SPRITE;

// mob sprites
int ACTIVE_SLIME_SPRITE;
int IDLE_SLIME_SPRITE;

// load resources
void InitResources() {
    currentState = LOADING;

    itemsToLoad[TILESET_TEXTURE] = "resources/vectorogue_floor.png";
    itemsToLoad[ACTORS_TEXTURE] = "resources/vectorogue_actors.png";

    // loot sprites
    EMPTY_LOOT_SPRITE = 2;
    POTION_LOOT_SPRITE = 3;
    COIN_LOOT_SPRITE = 8;

    // arrow sprites
    DOWN_ARROW_SPRITE = 4;
    RIGHT_ARROW_SPRITE = 5;
    UP_ARROW_SPRITE = 10;
    LEFT_ARROW_SPRITE = 11;

    // mob sprites
    ACTIVE_SLIME_SPRITE = 6;
    IDLE_SLIME_SPRITE = 7;
}

void CleanupResources() {
    currentState = QUITTING;
    // unload resources
    for (int i = 0; i < loadedCount; ++i) {
        UnloadTexture(Textures[loadedCount]);
        // todo: empty Textures array
    }
    loadedCount = 0;

    UnloadMap(map);
    mapLoaded = false;
}

void FinalizeLoad() {
    // MOBS
    // active slime
    Sprites[ACTIVE_SLIME_SPRITE].TextureId = ACTORS_TEXTURE;
    Sprites[ACTIVE_SLIME_SPRITE].originX = 0;
    Sprites[ACTIVE_SLIME_SPRITE].originY = 1;
    Sprites[ACTIVE_SLIME_SPRITE].width = 32;
    Sprites[ACTIVE_SLIME_SPRITE].height = 32;
    // idle slime
    Sprites[IDLE_SLIME_SPRITE].TextureId = ACTORS_TEXTURE;
    Sprites[IDLE_SLIME_SPRITE].originX = 1;
    Sprites[IDLE_SLIME_SPRITE].originY = 1;

    // LOOT
    // empty loot
    Sprites[EMPTY_LOOT_SPRITE].TextureId = ACTORS_TEXTURE;
    Sprites[EMPTY_LOOT_SPRITE].originX = 2;
    Sprites[EMPTY_LOOT_SPRITE].originY = 0;
    // potion loot
    Sprites[POTION_LOOT_SPRITE].TextureId = ACTORS_TEXTURE;
    Sprites[POTION_LOOT_SPRITE].originX = 3;
    Sprites[POTION_LOOT_SPRITE].originY = 0;
    // coin loot
    Sprites[COIN_LOOT_SPRITE].TextureId = ACTORS_TEXTURE;
    Sprites[COIN_LOOT_SPRITE].originX = 2;
    Sprites[COIN_LOOT_SPRITE].originY = 1;

    // ARROWS
    // down arrow
    Sprites[DOWN_ARROW_SPRITE].TextureId = ACTORS_TEXTURE;
    Sprites[DOWN_ARROW_SPRITE].originX = 4;
    Sprites[DOWN_ARROW_SPRITE].originY = 0;
    // right arrow
    Sprites[RIGHT_ARROW_SPRITE].TextureId = ACTORS_TEXTURE;
    Sprites[RIGHT_ARROW_SPRITE].originX = 5;
    Sprites[RIGHT_ARROW_SPRITE].originY = 0;
    // up arrow
    Sprites[UP_ARROW_SPRITE].TextureId = ACTORS_TEXTURE;
    Sprites[UP_ARROW_SPRITE].originX = 4;
    Sprites[UP_ARROW_SPRITE].originY = 1;
    // left arrow
    Sprites[LEFT_ARROW_SPRITE].TextureId = ACTORS_TEXTURE;
    Sprites[LEFT_ARROW_SPRITE].originX = 5;
    Sprites[LEFT_ARROW_SPRITE].originY = 1;
}

void UpdateLoad() {
    if (loadedCount >= MAX_TEXTURES_TO_LOAD) {
        if (!mapLoaded) {
            map = LoadTiled("resources/floor.json");
            mapLoaded = true;
        }
    }

    if (mapLoaded) {
        FinalizeLoad();
        LoadComplete();
        return;
    }

    Textures[loadedCount] = LoadTexture(itemsToLoad[loadedCount]);
    loadedCount++;
}
