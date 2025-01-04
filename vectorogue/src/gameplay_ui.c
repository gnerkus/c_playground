//
// Created by nanotome on 12/31/2024.
//
#include "main.h"
#include "loading.h"

Font font;

void DrawBackground() {
    // TODO: move the '2' to the constant representing the background texture
    DrawTexture(Textures[2], 0, 0, WHITE);
}

void DrawPlayerHP(int maxHP, int currentHP, int posX, int posY, int barWidth) {
    int empty = maxHP - currentHP;
    for (int i = 0; i < currentHP; ++i) {
        DrawTexture(Textures[3], (i * barWidth) + posX, posY, WHITE);
    }
    for (int i = 0; i < empty; ++i) {
        DrawTexture(Textures[4], (i * barWidth) + posX + (barWidth * currentHP), posY, WHITE);
    }
}

void DrawTurnTimer(int timer, int posX, int posY) {
    Vector2 timerPosition = { posX, posY };
    DrawTextEx(font, TextFormat("%i", timer), timerPosition, font.baseSize * 4.0f, 4.0f, VR_WHITE);
}

void DrawPlayerCoins(int coins, int posX, int posY) {
    Vector2 labelPos = { posX, posY };
    Vector2 coinsPos = { posX + 18, posY + 32 };
    DrawTextEx(font, "coins", labelPos, font.baseSize * 2.0f, 4.0f, VR_DARKGRAY);
    DrawTextEx(font, TextFormat("%i", coins), coinsPos, font.baseSize * 2.0f, 4.0f, VR_GRAY);
}
