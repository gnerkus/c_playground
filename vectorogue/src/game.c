//
// Created by nanotome on 12/23/2024.
//
#include "main.h"
#include "game.h"

#define GRID_WIDTH 3
#define TILE_COUNT GRID_WIDTH * GRID_WIDTH

ActorTypes actors[TILE_COUNT];

static const int initActorCount = 1;

// ----------------------------------------------------------
// PUBLIC (in header file)
// ----------------------------------------------------------
void InitGame() {

}

// ----------------------------------------------------------
// PRIVATE
// ----------------------------------------------------------

// analyze the game state and return a random actor to match
ActorTypes GetRandomActor() {
    // TODO: remove placeholder code below
    return DOWN_ARROW;
}

int GetRandomEmptyTile() {
    // TODO: remove placeholder code below
    return 0;
}

void AddInitialActorsToGrid() {
    for (int i = 0; i < initActorCount; ++i) {
        actors[GetRandomEmptyTile()] = GetRandomActor();
    }
}