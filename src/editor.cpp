#include "editor.h"

void UpdateEditorState(EngineState &config, int FPS)
{

    DrawText(TextFormat("FPS: %i", FPS), 20, 20, 15, WHITE);

    // Toggle Editor Mode (TAB Key)
    if (config.isPlaying == false)
    {
        if (IsKeyPressed(KEY_TAB))
        {
            config.currentMode++;
            if (config.currentMode >= TOTAL_MODES)
            {
                config.currentMode = 0;
            }
        }
    }
    else
    {
        config.currentMode = 0;
    }

    // Play Button Logic
    if (IsKeyReleased(KEY_SPACE))
    {
        config.isPlaying = !config.isPlaying;
    }

    if (config.isPlaying == true)
    {
        DrawText("Playing", 860, 20, 15, GREEN);
    }
    else
    {
        DrawText("Not Playing", 850, 20, 15, RED);
    }

    if (config.currentMode == MODE_DEFAULT)
    {
        DrawText("Mode: Default Cursor (TAB to switch)", 20, 45, 15, GRAY);
    }
    else if (config.currentMode == MODE_CIRCLE_BRUSH)
    {
        config.editorRadius = config.editorRadius + GetMouseWheelMove() * 1.5f;

        if (config.editorRadius < 5.0f)
        {
            config.editorRadius = 5.0f;
        }
        if (config.editorRadius > 300.0f)
        {
            config.editorRadius = 300.0f;
        }

        DrawText("Mode: Circle Brush (Scroll to size, Right-Click to create circular objects)", 20, 45, 15, LIGHTGRAY);
    }
};

bool spawnBall(EngineState &config)
{
    if (config.currentMode == MODE_CIRCLE_BRUSH && config.isPlaying == false)
    {
        if (IsMouseButtonReleased(MOUSE_BUTTON_RIGHT))
        {
            return true;
        }
    }
    return false;
};
