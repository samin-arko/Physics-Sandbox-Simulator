#pragma once
#include "raylib.h"
#include "config.h"

enum editorModes
{
    MODE_DEFAULT,
    MODE_CIRCLE_BRUSH,

    TOTAL_MODES
};

void UpdateEditorState(EngineState &config, int FPS);
bool spawnBall(EngineState &config);