#include "imgui.h"
#include "raylib.h"
#include "rlImGui.h"
#include "config.h"
#include "editor.h"
#include "physics.h"
#include <vector>
#include <math.h>

int main(void)
{
    EngineState config;
    config.windowWidth = 1820;
    config.windowHeight = 980;
    config.isPlaying = false;
    config.editorRadius = 20.0f;
    config.editorMode = 0;
    config.currentMode = MODE_DEFAULT;
    config.BallList;

    SetConfigFlags(FLAG_MSAA_4X_HINT);

    InitWindow(config.windowWidth, config.windowHeight, "RayLib Physics Sandbox");

    SetTargetFPS(60);

    while (!WindowShouldClose()) // Detect window close button or ESC key (Main Game Loop)
    {
        // -------------------------------------------------------------------
        //  INPUT, STATE & LOGIC
        // -------------------------------------------------------------------
        int FPS = GetFPS();
        float dt = GetFrameTime();
        Vector2 mousePos = GetMousePosition();
        if (spawnBall(config))
        {
            BallObject newBall;
            newBall.x = mousePos.x;
            newBall.y = mousePos.y;
            newBall.velocityX = GetRandomValue(-5, 5);
            newBall.velocityY = GetRandomValue(-5, 5);
            newBall.AccelerationX = 0;
            newBall.AccelerationY = 0;
            newBall.radius = config.editorRadius;
            newBall.mass = 7 * newBall.radius * newBall.radius;
            newBall.color = (Color){GetRandomValue(50, 255), GetRandomValue(50, 255), GetRandomValue(50, 255), 255};

            config.BallList.push_back(newBall);
        }
        if (config.isPlaying == true)
        {
            UpdatePhysics(config, dt);
        }
        // -------------------------------------------------------------------
        //  Begin Drawing
        // -------------------------------------------------------------------

        BeginDrawing();
        ClearBackground(BLACK);

        for (size_t i = 0; i < config.BallList.size(); i++)
        {
            DrawCircle(config.BallList[i].x, config.BallList[i].y, config.BallList[i].radius, config.BallList[i].color);
        }

        if (config.currentMode == MODE_CIRCLE_BRUSH)
        {
            Vector2 EditormousePos = GetMousePosition();
            DrawCircleLines(EditormousePos.x, EditormousePos.y, config.editorRadius, WHITE);
        }

        UpdateEditorState(config, FPS);

        EndDrawing();
    }

    CloseWindow();

    return 0;
}