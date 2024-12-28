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

    // LOOT
    // empty loot
    Sprites[EMPTY_LOOT_SPRITE].TextureId = ACTORS_TEXTURE;
    Sprites[EMPTY_LOOT_SPRITE].SourceRec.x = 2;
    Sprites[EMPTY_LOOT_SPRITE].SourceRec.y = 0;
    // potion loot
    Sprites[POTION_LOOT_SPRITE].TextureId = ACTORS_TEXTURE;
    Sprites[POTION_LOOT_SPRITE].SourceRec.x = 3;
    Sprites[POTION_LOOT_SPRITE].SourceRec.y = 0;
    // coin loot
    Sprites[COIN_LOOT_SPRITE].TextureId = ACTORS_TEXTURE;
    Sprites[COIN_LOOT_SPRITE].SourceRec.x = 2;
    Sprites[COIN_LOOT_SPRITE].SourceRec.y = 1;

    // ARROWS
    // down arrow
    Sprites[DOWN_ARROW_SPRITE].TextureId = ACTORS_TEXTURE;
    Sprites[DOWN_ARROW_SPRITE].SourceRec.x = 4;
    Sprites[DOWN_ARROW_SPRITE].SourceRec.y = 0;
    // right arrow
    Sprites[RIGHT_ARROW_SPRITE].TextureId = ACTORS_TEXTURE;
    Sprites[RIGHT_ARROW_SPRITE].SourceRec.x = 5;
    Sprites[RIGHT_ARROW_SPRITE].SourceRec.y = 0;
    // up arrow
    Sprites[UP_ARROW_SPRITE].TextureId = ACTORS_TEXTURE;
    Sprites[UP_ARROW_SPRITE].SourceRec.x = 4;
    Sprites[UP_ARROW_SPRITE].SourceRec.y = 1;
    // left arrow
    Sprites[LEFT_ARROW_SPRITE].TextureId = ACTORS_TEXTURE;
    Sprites[LEFT_ARROW_SPRITE].SourceRec.x = 5;
    Sprites[LEFT_ARROW_SPRITE].SourceRec.y = 1;
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
