//
// Created by nanotome on 12/31/2024.
//

#ifndef VECTOROGUE_GAMEPLAY_UI_H
#define VECTOROGUE_GAMEPLAY_UI_H

void DrawBackground();
void DrawPlayerHP(int maxHP, int currentHP, int posX, int posY, int hpBarWidth);
void DrawTurnTimer(int timer, int posX, int posY);
void DrawPlayerCoins(int coins, int posX, int posY);

#endif //VECTOROGUE_GAMEPLAY_UI_H
