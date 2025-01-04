//
// Created by nanotome on 12/31/2024.
//
#include "main.h"
#include "loading.h"

Font font;

void DrawBackground() {
    DrawTexture(Textures[2], 0, 0, WHITE);
}

void DrawPlayerHP() {

}

void DrawTurnTimer(int timer) {
    Vector2 timerPosition = { 0.0f, 0.0f };
    DrawTextEx(font, TextFormat("%i", timer), timerPosition, font.baseSize * 4.0f, 4.0f, VR_WHITE);
}

void DrawPlayerCoins() {

}
