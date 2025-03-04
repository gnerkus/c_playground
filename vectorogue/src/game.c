//
// Created by nanotome on 12/23/2024.
//
#include "main.h"
#include "game.h"
#include "loading.h"
#include "resource_ids.h"
#include "gameplay_ui.h"

#include "raylib.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define GRID_WIDTH 3
#define TILE_COUNT GRID_WIDTH * GRID_WIDTH
#define ACTOR_TYPE_COUNT LAST - EMPTY

// ----------------------------------------------------
// CONSTANTS
// ----------------------------------------------------
static const int INIT_ACTOR_COUNT = 4;
static const int MAX_PLAYER_HP = 6;
static const int TURN_SIZE = 240;
static const int INIT_TURN_SPEED = 1;
static const int INIT_DELAY = 1;
static const int TIME_UNTIL_NEXT_INPUT = 15;
static const int MAX_NEW_ACTOR = 2;
static const int SPRITE_SCALE = 2;
int X_OFFSET;
int Y_OFFSET;
static const int TIMER_X_OFFSET = 21;
static const int TIMER_Y_OFFSET = 64;
static const int STATS_X_OFFSET = 96;
static const int HP_Y_OFFSET = 60;
static const int HP_BAR_WIDTH = 21;

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
static bool allowInput = false;
static int timeSinceLastInput = 0;

static int playerHP = 0;
static int playerCoins = 0;
static int turnSpeed = 0;

struct SpriteInfo Sprites[32];
Texture2D Textures[MAX_TEXTURES_TO_LOAD];
Music gameplayMusic;

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

void AddRandomActorsToGrid(int actorCount) {
    for (int i = 0; i < actorCount; ++i) {
        ActorTypes randomActor = GetRandomActor();
        actors[GetRandomEmptyTile()] = randomActor;
        actorCounts[randomActor] += 1;
        actorCounts[EMPTY] -= 1;
    }
}

void EnableInput() {
    allowInput = true;
    timeSinceLastInput = 0;
}

void DisableInput() {
    allowInput = false;
}

void DebugBoard() {
    printf("BOARD PRINTING: START\n");
    for (int i = 0; i < TILE_COUNT; ++i) {
        printf("%d\n", actors[i]);
    }
    printf("BOARD PRINTED: END\n");
}

void DebugPlayerState() {
    printf("PLAYER STATE: START\n");
    printf("HP: %d\n", playerHP);
    printf("coins: %d\n", playerCoins);
    printf("PLAYER STATE: END\n");
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

void MoveUp(int row, int col, ActorTypes currentActor) {
    if (row > 0) {
        int new_pos = GetIdxFromRowCol(row - 1, col);
        actors[new_pos] = currentActor;
        // current position is now occupied
        tempEmpty[new_pos] = -1;
    } else {
        actorCounts[currentActor] -= 1;
    }
}

void MoveRight(int row, int col, ActorTypes currentActor) {
    if (col < GRID_WIDTH - 1) {
        int new_pos = GetIdxFromRowCol(row, col + 1);
        actors[new_pos] = currentActor;
        // current position is now occupied
        tempEmpty[new_pos] = -1;
    } else {
        actorCounts[currentActor] -= 1;
    }
}

void MoveDown(int row, int col, ActorTypes currentActor) {
    if (row < GRID_WIDTH - 1) {
        int new_pos = GetIdxFromRowCol(row + 1, col);
        actors[new_pos] = currentActor;
        // current position is now occupied
        tempEmpty[new_pos] = -1;
    } else {
        actorCounts[currentActor] -= 1;
    }
}

void MoveLeft(int row, int col, ActorTypes currentActor) {
    if (col > 0) {
        int new_pos = GetIdxFromRowCol(row, col - 1);
        actors[new_pos] = currentActor;
        // current position is now occupied
        tempEmpty[new_pos] = -1;
    } else {
        actorCounts[currentActor] -= 1;
    }
}

void HandleArrow(ActorTypes arrowType) {
    for (int i = 0; i < TILE_COUNT; ++i) {
        tempEmpty[i] = i;
        ActorTypes currentActor = actors[i];
        int row = GetRowFromIdx(i);
        int col = GetColFromIdx(i);

        switch (arrowType) {
            case UP_ARROW:
                MoveUp(row, col, currentActor);
                break;
            case RIGHT_ARROW:
                MoveRight(row, col, currentActor);
                break;
            case DOWN_ARROW:
                MoveDown(row, col, currentActor);
                break;
            case LEFT_ARROW:
                MoveLeft(row, col, currentActor);
                break;
            default:
                break;
        }

        actors[i] = EMPTY;
    }
}

void HandleTurn() {
    for (int i = 0; i < TILE_COUNT; ++i) {
        ActorTypes currentActor = actors[i];
        switch (currentActor) {
            case UP_ARROW:
                HandleArrow(UP_ARROW);
                break;
            case RIGHT_ARROW:
                HandleArrow(RIGHT_ARROW);
                break;
            case DOWN_ARROW:
                HandleArrow(DOWN_ARROW);
                break;
            case LEFT_ARROW:
                HandleArrow(LEFT_ARROW);
                break;
            case ACTIVE_MONSTER:
                playerHP -= 1;
                break;
            case ACTIVE_COINS:
                playerCoins += 1;
                break;
            case ACTIVE_POTION:
                playerHP = (int)fmin(playerHP + 1, MAX_PLAYER_HP);
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

    // TODO: add random actors based on the types of actors already on the board; game design
    // add random actors to the board at the end of a turn
    int emptyCount = top + 1;
    if (emptyCount > 0) {
        int min = emptyCount > MAX_NEW_ACTOR ? MAX_NEW_ACTOR : emptyCount;
        AddRandomActorsToGrid(min);
    }
}

void HandleTransform() {
    for (int i = 0; i < TILE_COUNT; ++i) {
        ActorTypes currentActor = actors[i];
        switch (currentActor) {
            case UP_ARROW:
                actors[i] = RIGHT_ARROW;
                break;
            case RIGHT_ARROW:
                actors[i] = DOWN_ARROW;
                break;
            case DOWN_ARROW:
                actors[i] = LEFT_ARROW;
                break;
            case LEFT_ARROW:
                actors[i] = UP_ARROW;
                break;
            case INERT_MONSTER:
                actors[i] = ACTIVE_MONSTER;
                break;
            case ACTIVE_MONSTER:
                actors[i] = INERT_MONSTER;
                break;
            case INERT_POTION:
                actors[i] = ACTIVE_POTION;
                break;
            case ACTIVE_POTION:
                actors[i] = INERT_POTION;
                break;
            case INERT_COINS:
                actors[i] = ACTIVE_COINS;
                break;
            case ACTIVE_COINS:
                actors[i] = INERT_COINS;
                break;
            case EMPTY:
            case LAST:
            default:
                break;
        }
    }
}

void DrawActor(int actorID, int row, int col, Vector2 origin) {
    struct SpriteInfo actorInfo = Sprites[actorID];
    Texture2D spriteTexture = Textures[actorInfo.TextureId];
    Rectangle srcRect = {
            actorInfo.originX * SPRITE_WIDTH,
            actorInfo.originY * SPRITE_HEIGHT,
            SPRITE_WIDTH,
            SPRITE_HEIGHT
    };
    Rectangle destRect = {
            col * SPRITE_WIDTH * SPRITE_SCALE + X_OFFSET,
            row * SPRITE_HEIGHT * SPRITE_SCALE + Y_OFFSET,
            SPRITE_WIDTH * SPRITE_SCALE,
            SPRITE_WIDTH * SPRITE_SCALE
    };
    DrawTexturePro(spriteTexture, srcRect, destRect, origin, 0, WHITE);
}

void DrawActors() {
    for (int i = 0; i < TILE_COUNT; ++i) {
        ActorTypes currentActor = actors[i];
        Texture2D actorTexture = Textures[Sprites[EMPTY_LOOT_SPRITE].TextureId];
        int row = GetRowFromIdx(i);
        int col = GetColFromIdx(i);
        Vector2 origin = {0.0f, 0.0f};
        switch (currentActor) {
            case UP_ARROW:
                DrawActor(UP_ARROW_SPRITE, row, col, origin);
                break;
            case RIGHT_ARROW:
                DrawActor(RIGHT_ARROW_SPRITE, row, col, origin);
                break;
            case DOWN_ARROW:
                DrawActor(DOWN_ARROW_SPRITE, row, col, origin);
                break;
            case LEFT_ARROW:
                DrawActor(LEFT_ARROW_SPRITE, row, col, origin);
                break;
            case INERT_MONSTER:
                DrawActor(IDLE_SLIME_SPRITE, row, col, origin);
                break;
            case ACTIVE_MONSTER:
                DrawActor(ACTIVE_SLIME_SPRITE, row, col, origin);
                break;
            case INERT_POTION:
                DrawActor(EMPTY_LOOT_SPRITE, row, col, origin);
                break;
            case ACTIVE_POTION:
                DrawActor(POTION_LOOT_SPRITE, row, col, origin);
                break;
            case INERT_COINS:
                DrawActor(EMPTY_LOOT_SPRITE, row, col, origin);
                break;
            case ACTIVE_COINS:
                DrawActor(COIN_LOOT_SPRITE, row, col, origin);
                break;
            default:
                break;
        }
    }
}

// ----------------------------------------------------------
// PUBLIC (in header file)
// ----------------------------------------------------------
void InitGame() {
    X_OFFSET = screenWidth / 2 - (GRID_WIDTH * SPRITE_WIDTH);
    Y_OFFSET = screenHeight / 2 - (GRID_WIDTH * SPRITE_HEIGHT);

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
    AddRandomActorsToGrid(INIT_ACTOR_COUNT);

    playerHP = MAX_PLAYER_HP;
    playerCoins = 0;
    turnSpeed = INIT_TURN_SPEED;

    timer = INIT_DELAY;
    EnableInput();

    PlayMusicStream(gameplayMusic);
}

void UpdateGame() {
    if (currentState != GAMEOVER) {
        UpdateMusicStream(gameplayMusic);
        if (currentState != PAUSED) {
            if (timeSinceLastInput >= TIME_UNTIL_NEXT_INPUT && !allowInput) {
                EnableInput();
            }

            if (IsKeyPressed(KEY_SPACE) && allowInput) {
                HandleTransform();
                DisableInput();
            }

            // timer; runs every 1/turnSpeed seconds
            if ((timer % (TURN_SIZE / turnSpeed)) == 0) {
                DisableInput();
                HandleTurn();
                timer = 0;
                EnableInput();
            }

            framesCounter++;
            timer++;
            timeSinceLastInput++;
        }
    }
}

void DrawGame() {
    ClearBackground(BLACK);
    DrawBackground();
    DrawTiled(map, X_OFFSET, Y_OFFSET, WHITE);
    DrawTurnTimer(
            (TURN_SIZE - timer) / fps + 1,
            X_OFFSET + (GRID_WIDTH * SPRITE_WIDTH * 2) - TIMER_X_OFFSET,
            Y_OFFSET - TIMER_Y_OFFSET
    );
    DrawPlayerHP(
            MAX_PLAYER_HP,
            playerHP,
            X_OFFSET,
            Y_OFFSET - HP_Y_OFFSET,
            HP_BAR_WIDTH
    );
    DrawPlayerCoins(
            playerCoins,
            X_OFFSET - STATS_X_OFFSET,
            Y_OFFSET
    );
    DrawActors();
}
