#pragma once
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

struct EngineState
{
    bool isPlaying;
    int currentMode;
    float editorRadius;
    int editorMode;
    Color playbuttonColor;
    int windowWidth;
    int windowHeight;
    std::vector<BallObject> BallList;
};
