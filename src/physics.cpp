#include "physics.h"

void UpdatePhysics(EngineState &config, float dt)
{

    for (size_t i = 0; i < config.BallList.size(); i++)
    {
        config.BallList[i].x += config.BallList[i].velocityX * dt;
        config.BallList[i].y += config.BallList[i].velocityY * dt;
    }
    HandleCollision(config.BallList);
}

void HandleCollision(std::vector<BallObject> &BallList)
{
    size_t Total_size = BallList.size();
    for (size_t i = 0; i < Total_size; i++)
    {
        for (size_t j = i + 1; j < Total_size; j++)
        {
            float dx = BallList[j].x - BallList[i].x;
            float dy = BallList[j].y - BallList[i].y;

            float squaredDistance = (dx * dx) + (dy * dy);
            float radiisum = BallList[j].radius + BallList[i].radius;
            float squaredRadiiSum = radiisum * radiisum;

            if (squaredDistance <= squaredRadiiSum)
            {
            }
        }
    }
}