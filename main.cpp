#include "rock_paper_scissors.h"

#include "raylib.h"
#include <string>

int main() {
    SetConfigFlags(FLAG_MSAA_4X_HINT);
    InitWindow(960, 720, "Rock, Paper, Scissors - doodle edition");
    SetWindowMinSize(800, 680);
    SetTargetFPS(60);
    initializeGameUi();

    GameState game;
    float elapsedTime = 0.0f;

    while (!WindowShouldClose()) {
        const float deltaTime = GetFrameTime();
        elapsedTime += deltaTime;
        updateGameUi(game, deltaTime);

        BeginDrawing();
        drawGameUi(game, elapsedTime);
        EndDrawing();
    }

    shutdownGameUi();
    CloseWindow();
    return 0;
}