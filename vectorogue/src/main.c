#include "main.h"
#include "game.h"
#include "loading.h"
#include "mainmenu.h"

//------------------------------------------------------------------------------------------
// Types and Structures Definition
//------------------------------------------------------------------------------------------

ApplicationStates currentState = STARTUP;
int framesCounter = 0;
Map map;
int screenWidth = 1280;
int screenHeight = 720;
int fps = 60;

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    InitWindow(screenWidth, screenHeight, "Vectorogue");

    InitAudioDevice();

    InitResources();

    SetTargetFPS(fps);               // Set desired framerate (frames-per-second)
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        switch(currentState)
        {
            case STARTUP:
            {
                currentState = LOADING;
            } break;
            case LOADING:
            {
                UpdateLoad();
            } break;
            case MENU:
            {
                // TODO: Update TITLE screen variables here!

                // Press enter to change to GAMEPLAY screen
                if (IsKeyPressed(KEY_ENTER) || IsGestureDetected(GESTURE_TAP))
                {
                    StartGame();
                }
            } break;
            case RUNNING:
            {
                UpdateGame();

                // Press enter to change to ENDING screen
                if (IsKeyPressed(KEY_ENTER) || IsGestureDetected(GESTURE_TAP))
                {
                    currentState = QUITTING;
                }
            } break;
            case QUITTING:
            {
                // TODO: Update ENDING screen variables here!

                // Press enter to return to TITLE screen
                if (IsKeyPressed(KEY_ENTER) || IsGestureDetected(GESTURE_TAP))
                {
                    currentState = MENU;
                }
            } break;
            default: break;
        }
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(RAYWHITE);

            switch(currentState)
            {
                case STARTUP:
                {
                    // TODO: Draw LOGO screen here!
                    DrawText("LOGO SCREEN", 20, 20, 40, LIGHTGRAY);
                    DrawText("WAIT for 1 SECOND...", 290, 220, 20, GRAY);

                } break;
                case LOADING:
                {
                    DrawRectangle(0, 0, screenWidth, screenHeight, PURPLE);
                    DrawText("LOADING SCREEN", 20, 20, 40, MAROON);
                    DrawText("PRESS ENTER or TAP to JUMP to MENU SCREEN", 120, 220, 20, MAROON);

                } break;
                case MENU:
                {
                    DrawMainMenu();
                } break;
                case RUNNING:
                {
                    DrawGame();
                } break;
                case QUITTING:
                {
                    // TODO: Draw ENDING screen here!
                    DrawRectangle(0, 0, screenWidth, screenHeight, BLUE);
                    DrawText("ENDING SCREEN", 20, 20, 40, DARKBLUE);
                    DrawText("PRESS ENTER or TAP to RETURN to TITLE SCREEN", 120, 220, 20, DARKBLUE);

                } break;
                default: break;
            }

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------

    // unload resources
    CleanupResources();

    CloseAudioDevice();

    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}

void LoadComplete() {
    currentState = MENU;
}

void StartGame() {
    InitGame();
    currentState = RUNNING;
}