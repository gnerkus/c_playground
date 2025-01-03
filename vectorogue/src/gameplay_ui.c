//
// Created by nanotome on 12/31/2024.
//

#include "loading.h"
#include "raylib.h"
#include <math.h>
#include <stdio.h>

Font font;

void DrawBackground() {
    DrawTexture(Textures[2], 0, 0, WHITE);
}

void DrawPlayerHP() {

}

void DrawTurnTimer(int timer) {
    Vector2 timerPosition = { 0.0f, 0.0f };
    int enough = (int)((ceil(log10(timer))+1)*sizeof(char));
    char timerString[enough];
    //DrawTextEx(font, (const char *) timer, timerPosition, font.baseSize * 1.0f, 2.0f, WHITE);
    DrawTextEx(font, sprintf(timerString, "%d", timer), timerPosition, font.baseSize * 1.0f, 2.0f, WHITE);
}

void DrawPlayerCoins() {

}
