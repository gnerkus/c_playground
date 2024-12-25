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
static int tempEmpty[TILE_COUNT];

static int timer = 0;

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

void DebugPlayerState() {
    printf("PLAYER STATE: START\n");
    printf("HP: %d\n", playerHP);
    printf("coins: %d\n", playerCoins);
    printf("PLAYER STATE: END");
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

    // keep track of empty tiles when handling arrow actors
    for (int i = 0; i < TILE_COUNT; ++i) {
        tempEmpty[i] = -1;
    }

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

    timer = INIT_DELAY;
    currentState = RUNNING;
}

int GetIdxFromRowCol(int row, int col) {
    return row * GRID_WIDTH + col;
}

int GetRowFromIdx(int idx) {
    return idx / GRID_WIDTH;
}

int GetColFromIdx(int idx) {
    return idx % GRID_WIDTH;
}

void HandleUpArrow() {
    for (int i = 0; i < TILE_COUNT; ++i) {
        tempEmpty[i] = i;
        ActorTypes currentActor = actors[i];
        int row = GetRowFromIdx(i);
        int col = GetColFromIdx(i);
        if (row > 0) {
            int new_pos = GetIdxFromRowCol(row - 1, col);
            actors[new_pos] = currentActor;
            // current position is now occupied
            tempEmpty[new_pos] = -1;
        }
        actors[i] = EMPTY;
    }
}

void HandleTurn() {
    for (int i = 0; i < TILE_COUNT; ++i) {
        ActorTypes currentActor = actors[i];
        switch (currentActor) {
            case UP_ARROW:
                HandleUpArrow();
                break;
            case ACTIVE_MONSTER:
                playerHP -= 1;
                break;
            case ACTIVE_COINS:
                playerCoins += 1;
                break;
            case ACTIVE_POTION:
                playerHP += 1;
                break;
            case INERT_POTION:
            case INERT_MONSTER:
            case INERT_COINS:
            case EMPTY:
            case LAST:
            default:
                break;
        }
        if (playerHP <= 0) {
            currentState = GAMEOVER;
            break;
        }
    }

    // update empty tiles
    for (int i = 0; i < TILE_COUNT; ++i) {
        if (tempEmpty[i] > -1) {
            pushToEmpty(tempEmpty[i]);
            tempEmpty[i] = -1;
        }
    }

    shuffleEmpty();
}

void UpdateGame() {
    if (currentState != GAMEOVER) {
        if (currentState != PAUSED) {
            // timer; runs every 1/turnSpeed seconds
            if ((timer % (60 / turnSpeed)) == 0) {
                HandleTurn();
            }

            framesCounter++;
            timer++;
        }
    }

}

void DrawGame() {

}
