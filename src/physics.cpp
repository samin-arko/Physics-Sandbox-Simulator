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
                float pushFactor = 0.0005f;

                BallList[i].x -= dx * pushFactor;
                BallList[i].y -= dy * pushFactor;

                BallList[j].x += dx * pushFactor;
                BallList[j].y += dy * pushFactor;

                float massSum = BallList[i].mass + BallList[j].mass;
                // first object - i
                float DotProduct1 = ((BallList[i].velocityX - BallList[j].velocityX) * (BallList[i].x - BallList[j].x) + (BallList[i].velocityY - BallList[j].velocityY) * (BallList[i].y - BallList[j].y));
                float LineofContact1X = (BallList[i].x - BallList[j].x);
                float LineofContact1Y = (BallList[i].y - BallList[j].y);
                float disSqr1 = (LineofContact1X * LineofContact1X) + (LineofContact1Y * LineofContact1Y);
                float ki = (((2 * BallList[j].mass) / massSum) * DotProduct1 / disSqr1);
                float NewVelocity1X = BallList[i].velocityX - (ki * LineofContact1X);
                float NewVelocity1Y = BallList[i].velocityY - (ki * LineofContact1Y);

                // second object - j
                float DotProduct2 = ((BallList[j].velocityX - BallList[i].velocityX) * (BallList[j].x - BallList[i].x) + (BallList[j].velocityY - BallList[i].velocityY) * (BallList[j].y - BallList[i].y));
                float LineofContact2X = (BallList[j].x - BallList[i].x);
                float LineofContact2Y = (BallList[j].y - BallList[i].y);
                float disSqr2 = (LineofContact2X * LineofContact2X) + (LineofContact2Y * LineofContact2Y);
                float kj = (((2 * BallList[i].mass) / massSum) * DotProduct2 / disSqr2);
                float NewVelocity2X = BallList[j].velocityX - (kj * LineofContact2X);
                float NewVelocity2Y = BallList[j].velocityY - (kj * LineofContact2Y);

                BallList[i].velocityX = NewVelocity1X;
                BallList[i].velocityY = NewVelocity1Y;
                BallList[j].velocityX = NewVelocity2X;
                BallList[j].velocityY = NewVelocity2Y;
            }
        }
    }
}