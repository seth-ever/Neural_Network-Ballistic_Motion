#include <cmath>
#include <fstream>
#include <sstream>

// 42 pounder cannonball
double radius = 0.084836;
double surfaceArea = (radius * radius) * M_PI;
double mass = 19.0509;

double x, y, prevX, prevY;
double cannonHeight = 50;
double vx, vy, velocity;
double deltaT = 0.00001; // 10 micro-seconds step
double g = -9.807;

double dragC = 0.5, airDensity = 1.29;
float B2 = 0.5 * dragC * airDensity * surfaceArea;
double horWindVel;

void fire()
{
}

void ready()
{
    x, prevX, prevY = 0;
    y = cannonHeight;
    B2 = 0.5 * dragC * airDensity * surfaceArea; // update here since airDensity is variable
}

void aim(double angle)
{
    vx = velocity * cosf64(angle * M_PI / 180);
    vy = velocity * sinf64(angle * M_PI / 180);
}

void trainingData()
{

    // TOTAL SIMULATIONS =

    for (airDensity = 1.0; airDensity < 1.5; airDensity += 0.05)
    {
        for (horWindVel = -100; horWindVel <= 100; horWindVel += 20)
        {
            for (double initial_velocity = 10; initial_velocity < 200; initial_velocity += 20)
            {
                for (double angle = 0; angle < 20; angle += 0.5)
                {
                    ready();
                    aim(angle);
                    fire();
                }
                for (double angle = 20; angle < 70; angle += 0.2)
                {
                    ready();
                    aim(angle);
                    fire();
                }
                for (double angle = 70; angle <= 90; angle += 0.5)
                {
                    ready();
                    aim(angle);
                    fire();
                }
            }
        }
    }
}

int main()
{

    return 0;
}