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
    int mass;
    Color color;
};

struct EngineState
{
    bool isPlaying;
    int currentMode;
    float editorRadius;
    int editorMode;
    int windowWidth;
    int windowHeight;
    std::vector<BallObject> BallList;
};
