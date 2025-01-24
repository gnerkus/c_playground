//
// Created by nanotome on 1/22/2025.
//

#include "loading.h"

// ----------------------------------------------------------
// PUBLIC (in header file)
// ----------------------------------------------------------
void InitMainMenu() {

    // TODO: play menu music
}

void UpdateMainMenu() {

}

void DrawMainMenu() {
    ClearBackground(BLACK);
    DrawTexture(Textures[5], 0, 0, WHITE);
    DrawTexture(Textures[6], 723, 211, WHITE);
    DrawTexture(Textures[7], 48, 96, WHITE);
    DrawTexture(Textures[8], 48, 338, WHITE);
    DrawTexture(Textures[9], 48, 470, WHITE);
}
