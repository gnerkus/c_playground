//
// Created by nanotome on 12/23/2024.
//

#ifndef VECTOROGUE_GAME_H
#define VECTOROGUE_GAME_H

void InitGame();
void DrawGame();
void UpdateGame();
void QuitGame();

typedef enum {
    EMPTY = 0,
    UP_ARROW,
    RIGHT_ARROW,
    DOWN_ARROW,
    LEFT_ARROW,
    INERT_MONSTER,
    ACTIVE_MONSTER,
    INERT_POTION,
    ACTIVE_POTION,
    INERT_COINS,
    ACTIVE_COINS
} ActorTypes;

#endif //VECTOROGUE_GAME_H
