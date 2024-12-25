//
// Created by nanotome on 12/23/2024.
//
#include "main.h"
#include "game.h"

#include "raylib.h"
#include <stdlib.h>
#include <stdio.h>

#define GRID_WIDTH 3
#define TILE_COUNT GRID_WIDTH * GRID_WIDTH
#define ACTOR_TYPE_COUNT LAST - EMPTY

// ----------------------------------------------------
// CONSTANTS
// ----------------------------------------------------
static const int INIT_ACTOR_COUNT = 4;
static const int INIT_PLAYER_HP = 10;
static const int INIT_TURN_SPEED = 1;
static const int INIT_DELAY = 1;

// -----------------------------------------------------
// VARIABLES
// -----------------------------------------------------
/**
 * stack of positions on the board not occupied by an actor
 */
static int emptyTiles[TILE_COUNT];
static int top = -1;

/**
 * keeps track of the actors on the board
 */
static ActorTypes actors[TILE_COUNT];
/**
 * keeps track of the number of each type of actor on the board.
 * useful for determining which type of actor can be added to the board
 */
static int actorCounts[ACTOR_TYPE_COUNT];

static int framesCounter = 0;
static int timer = 0;
static bool pause = false;
static bool gameOver = false;

static int playerHP = 0;
static int playerCoins = 0;
static int turnSpeed = 0;

// ----------------------------------------------------------
// PRIVATE
// ----------------------------------------------------------
// TODO: extract utility functions into own file
void pushToEmpty(int tilePosition) {
    top = top + 1;
    emptyTiles[top] = tilePosition;
}

int popFromEmpty() {
    int val = emptyTiles[top];
    top = top - 1;
    return val;
}

int rand_comparison(const void *a, const void *b)
{
    (void)a; (void)b;

    return rand() % 2 ? +1 : -1;
}

void shuffle(void *base, size_t nmemb, size_t size)
{
    qsort(base, nmemb, size, rand_comparison);
}

void shuffleEmpty() {
    shuffle(emptyTiles, sizeof(emptyTiles) / sizeof(int), sizeof(int));
}

// analyze the game state and return a random actor to match
ActorTypes GetRandomActor() {
    return GetRandomValue(0, ACTOR_TYPE_COUNT);
}

int GetRandomEmptyTile() {
    return popFromEmpty();
}

void AddInitialActorsToGrid(int actorCount) {
    for (int i = 0; i < actorCount; ++i) {
        actors[GetRandomEmptyTile()] = GetRandomActor();
    }
}

void DebugBoard() {
    printf("BOARD PRINTING: START\n");
    for (int i = 0; i < TILE_COUNT; ++i) {
        printf("%d\n", actors[i]);
    }
    printf("BOARD PRINTED: END");
}

// ----------------------------------------------------------
// PUBLIC (in header file)
// ----------------------------------------------------------
void InitGame() {
    // initialize actor counts
    for (int i = 0; i < ACTOR_TYPE_COUNT; ++i) {
        actorCounts[i] = 0;
    }
    // initialize grid tiles
    for (int i = 0; i < TILE_COUNT; ++i) {
        actors[i] = EMPTY;
    }

    // grid is full of empty tiles at start
    actorCounts[EMPTY] = TILE_COUNT;

    // add indices of empty tile slots to list of empty tiles
    for (int i = 0; i < TILE_COUNT; ++i) {
        pushToEmpty(i);
    }

    // shuffle list of empty tile indices
    shuffleEmpty();

    // add random actors to grid
    AddInitialActorsToGrid(INIT_ACTOR_COUNT);

    playerHP = INIT_PLAYER_HP;
    playerCoins = 0;
    turnSpeed = INIT_TURN_SPEED;

    framesCounter = 0;
    timer = framesCounter + INIT_DELAY;
}

void UpdateGame() {
    if (!gameOver) {
        if (!pause) {
            // timer; runs every 1/turnSpeed seconds
            if ((timer % (60 / turnSpeed)) == 0) {
            }

            framesCounter++;
            timer++;
        }
    }

}

void DrawGame() {

}
