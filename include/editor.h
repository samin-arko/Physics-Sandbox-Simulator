#pragma once
#include "raylib.h"
#include "config.h"

enum editorModes
{
    MODE_DEFAULT,
    MODE_CIRCLE_BRUSH,

    TOTAL_MODES
};

void HandleEditorChanges(EngineState &config, bool &mouseOverButton);
bool spawnBall(EngineState &config);