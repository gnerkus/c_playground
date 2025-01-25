//
// Created by nanotome on 1/22/2025.
//

#include "loading.h"
#include "main.h"

Rectangle playBtnBounds = { 48, 338, 196, 83};
Rectangle exitBtnBounds = { 48, 470, 121, 41};
bool playAction = false;
bool exitAction = false;
Vector2 mousePoint = {0.0f, 0.0f};

// ----------------------------------------------------------
// PUBLIC (in header file)
// ----------------------------------------------------------
void InitMainMenu() {
    // TODO: play menu music
}

void UpdateMainMenu() {
    mousePoint = GetMousePosition();
    playAction = false;
    exitAction = false;

    if (CheckCollisionPointRec(mousePoint, playBtnBounds)) {
        if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) playAction = true;
    }

    if (CheckCollisionPointRec(mousePoint, exitBtnBounds)) {
        if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) exitAction = true;
    }

    if (playAction) {
        StartGame();
    }

    if (exitAction) {
        exitWindow = true;
    }
}

void DrawMainMenu() {
    ClearBackground(BLACK);
    DrawTexture(Textures[5], 0, 0, WHITE);
    DrawTexture(Textures[6], 723, 211, WHITE);
    DrawTexture(Textures[7], 48, 96, WHITE);
    // draw play button
    DrawTexture(Textures[8], 48, 338, WHITE);
    // draw exit button
    DrawTexture(Textures[9], 48, 470, WHITE);
}
