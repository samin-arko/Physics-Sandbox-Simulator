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

enum editorModes
{
    MODE_DEFAULT,
    MODE_CIRCLE_BRUSH,

    TOTAL_MODES
};

int main(void)
{
    int windowWidth = 1820;
    int windowHeight = 980;
    bool isPlaying = false;
    float editorRadius = 20.0f;
    int editorMode = 0;

    int currentMode = MODE_DEFAULT;

    InitWindow(windowWidth, windowHeight, "RayLib Physics Sandbox");

    SetTargetFPS(60);

    std::vector<BallObject> BallList;
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

        // Toggle Editor Mode (TAB Key)
        if (IsKeyPressed(KEY_TAB))
        {
            currentMode++;
            if (currentMode >= TOTAL_MODES)
            {
                currentMode = 0;
            }
        }

        // Play Button Logic
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

        if (currentMode == MODE_CIRCLE_BRUSH)
        {
            editorRadius = editorRadius + GetMouseWheelMove();

            if (editorRadius < 5.0f)
            {
                editorRadius = 5.0f;
            }
            if (editorRadius > 300.0f)
            {
                editorRadius = 300.0f;
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
        if (currentMode == MODE_DEFAULT)
        {
            DrawText("Mode: Default Cursor (TAB to switch)", 20, 45, 15, GRAY);
        }
        else if (currentMode == MODE_CIRCLE_BRUSH)
        {
            DrawCircleLines(EditormousePos.x, EditormousePos.y, editorRadius, WHITE);
            DrawText("Mode: Circle Brush (Scroll to size, Right-Click to create circular objects)", 20, 45, 15, LIGHTGRAY);
        }

        EndDrawing();
    }

    CloseWindow();

    return 0;
}