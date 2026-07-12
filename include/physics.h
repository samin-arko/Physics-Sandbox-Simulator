#pragma once
#include "raylib.h"
#include "config.h"
#include "editor.h"

void UpdatePhysics(EngineState &config);
void HandleCollision(std::vector<BallObject> &BallList);