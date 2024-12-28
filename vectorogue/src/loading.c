//
// Created by nanotome on 12/27/2024.
//

#include "loading.h"
#include "main.h"
#include "resource_ids.h"

#include "raylib.h"

ApplicationStates currentState;
Map map;

const char *itemsToLoad[MAX_TEXTURES_TO_LOAD];

static int loadedCount = 0;
static bool mapLoaded = false;

// load resources
void InitResources() {
    currentState = LOADING;

    itemsToLoad[TILESET_TEXTURE] = "resources/vectorogue_floor.png";
    itemsToLoad[ACTORS_TEXTURE] = "resources/vectorogue_actors.png";
}

void CleanupResources() {
    currentState = QUITTING;
    // unload resources
    for (int i = 0; i < loadedCount; ++i) {
        UnloadTexture(Textures[loadedCount]);
        // todo: empty Textures array
    }
    loadedCount = 0;
}

void FinalizeLoad() {
    // MOBS
    // active slime
    Sprites[ACTIVE_SLIME_SPRITE].TextureId = ACTORS_TEXTURE;
    Sprites[ACTIVE_SLIME_SPRITE].SourceRec.x = 0;
    Sprites[ACTIVE_SLIME_SPRITE].SourceRec.y = 1;
    // idle slime
    Sprites[IDLE_SLIME_SPRITE].TextureId = ACTORS_TEXTURE;
    Sprites[IDLE_SLIME_SPRITE].SourceRec.x = 1;
    Sprites[IDLE_SLIME_SPRITE].SourceRec.y = 1;
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
