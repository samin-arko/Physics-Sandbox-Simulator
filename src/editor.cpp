#include "editor.h"

void HandleEditorChanges(EngineState &config, bool &mouseOverButton)
{
    // Toggle Editor Mode (TAB Key)
    if (IsKeyPressed(KEY_TAB))
    {
        config.currentMode++;
        if (config.currentMode >= TOTAL_MODES)
        {
            config.currentMode = 0;
        }
    }

    // Play Button Logic
    if (mouseOverButton)
    {
        if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
        {
            if (config.isPlaying == false)
            {
                config.isPlaying = true;
                config.playbuttonColor = RED;
            }
            else
            {
                config.isPlaying = false;
                config.playbuttonColor = GREEN;
            }
        }
    }

    if (config.currentMode == MODE_CIRCLE_BRUSH)
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
