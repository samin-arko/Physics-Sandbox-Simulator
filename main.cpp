#include "raylib.h"
#include <vector>

struct BallObject
{
    int x;
    int y;
    float velocityX;
    float velocityY;
    float radius;
    Color color;
};

int main(void)
{
    int windowWidth = 1820;
    int windowHeight = 980;
    bool isPlaying = false;
    float editorRadius = 1;
    int editorMode = 0;

    InitWindow(windowWidth, windowHeight, "RayLib Physics Engine");

    SetTargetFPS(60);

    std::vector<BallObject> BallList;
    Rectangle playButton = {680, 20, 100, 40};
    Color buttonColor = GREEN;
    while (!WindowShouldClose()) // Detect window close button or ESC key (Main Game Loop)
    {
        int FPS = GetFPS();

        Vector2 mousePos = GetMousePosition();
        editorRadius = editorRadius + GetMouseWheelMove();
        bool mouseOverButton = CheckCollisionPointRec(mousePos, playButton);
        if (mouseOverButton)
        {
            if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
            {
                if (isPlaying == false)
                {
                    isPlaying = true;
                    buttonColor = RED;
                }
                else
                {
                    isPlaying = false;
                    buttonColor = GREEN;
                }
            }
        }

        if (isPlaying == false)
        {
            if (IsMouseButtonReleased(MOUSE_BUTTON_RIGHT))
            {
                BallObject newBall;
                newBall.x = mousePos.x;
                newBall.y = mousePos.y;
                newBall.velocityX = GetRandomValue(-3, 3); // Random horizontal direction
                newBall.velocityY = GetRandomValue(-3, 3); // Random vertical direction
                newBall.radius = editorRadius;             // Random size
                newBall.color = (Color){GetRandomValue(50, 255), GetRandomValue(50, 255), GetRandomValue(50, 255), 255};

                BallList.push_back(newBall);
            }
        }
        BeginDrawing();
        ClearBackground(BLACK);
        for (size_t i = 0; i < BallList.size(); i++)
        {
            DrawCircle(BallList[i].x, BallList[i].y, BallList[i].radius, BallList[i].color);
        }

        // DrawText(TextFormat("FPS: %i", FPS), (windowWidth / 45), (windowHeight / 35), 15, WHITE);
        DrawText(TextFormat("FPS: %i", FPS), 20, 20, 15, WHITE);

        DrawRectangleRec(playButton, buttonColor);

        Vector2 EditormousePos = GetMousePosition();
        DrawCircleLines(EditormousePos.x, EditormousePos.y, editorRadius, WHITE);
        EndDrawing();
    }

    CloseWindow();

    return 0;
}