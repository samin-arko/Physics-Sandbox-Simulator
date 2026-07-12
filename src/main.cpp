#include "raylib.h"
#include "config.h"
#include "editor.h"
#include "physics.h"
#include <vector>

int main(void)
{
    EngineState config;
    config.windowWidth = 1820;
    config.windowHeight = 980;
    config.isPlaying = false;
    config.editorRadius = 20.0f;
    config.editorMode = 0;
    config.currentMode = MODE_DEFAULT;
    config.playbuttonColor = GREEN;
    config.BallList;

    InitWindow(config.windowWidth, config.windowHeight, "RayLib Physics Sandbox");

    SetTargetFPS(60);

    Rectangle playButton = {680, 20, 100, 40};
    Color buttonColor = GREEN;

    while (!WindowShouldClose()) // Detect window close button or ESC key (Main Game Loop)
    {
        // -------------------------------------------------------------------
        //  INPUT, STATE & LOGIC
        // -------------------------------------------------------------------
        int FPS = GetFPS();
        Vector2 mousePos = GetMousePosition();
        bool mouseOverButton = CheckCollisionPointRec(mousePos, playButton);

        HandleEditorChanges(config, mouseOverButton);
        if (spawnBall(config))
        {
            BallObject newBall;
            newBall.x = mousePos.x;
            newBall.y = mousePos.y;
            newBall.velocityX = GetRandomValue(-5, 5); // Random horizontal direction
            newBall.velocityY = GetRandomValue(-5, 5); // Random vertical direction
            newBall.radius = config.editorRadius;      // Random size
            newBall.color = (Color){GetRandomValue(50, 255), GetRandomValue(50, 255), GetRandomValue(50, 255), 255};

            config.BallList.push_back(newBall);
        }

        BeginDrawing();
        ClearBackground(BLACK);
        if (config.isPlaying == true)
        {
            UpdatePhysics(config);
        }
        for (size_t i = 0; i < config.BallList.size(); i++)
        {
            DrawCircle(config.BallList[i].x, config.BallList[i].y, config.BallList[i].radius, config.BallList[i].color);
        }

        // DrawText(TextFormat("FPS: %i", FPS), (windowWidth / 45), (windowHeight / 35), 15, WHITE);
        DrawText(TextFormat("FPS: %i", FPS), 20, 20, 15, WHITE);

        DrawRectangleRec(playButton, config.playbuttonColor);

        Vector2 EditormousePos = GetMousePosition();
        if (config.currentMode == MODE_DEFAULT)
        {
            DrawText("Mode: Default Cursor (TAB to switch)", 20, 45, 15, GRAY);
        }
        else if (config.currentMode == MODE_CIRCLE_BRUSH)
        {
            DrawCircleLines(EditormousePos.x, EditormousePos.y, config.editorRadius, WHITE);
            DrawText("Mode: Circle Brush (Scroll to size, Right-Click to create circular objects)", 20, 45, 15, LIGHTGRAY);
        }

        EndDrawing();
    }

    CloseWindow();

    return 0;
}