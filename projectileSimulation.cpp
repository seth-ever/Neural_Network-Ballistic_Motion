#include <cmath>
#include <iostream>
#include <fstream>
#include <sstream>

// 42 pounder cannonball
double radius = 0.084836;
double surfaceArea = (radius * radius) * M_PI;
double mass = 19.0509;

double x, y, prevX, prevY;
double cannonHeight = 50;
double vx, vy, velocity;
double deltaT = 0.0001; // 100 micro-seconds step
double g = 9.807;

bool tracking = false;

double angle = 45;
double initial_velocity = 50;

double dragC = 0.5, airDensity = 1.29;
float B2 = 0.5 * dragC * airDensity * surfaceArea;
double horWindVel;

void forces()
{
    double relative_vx = vx - horWindVel; // Calculating velocities relative to the wind. We are only considering horizontal wind.
    double relative_velocity = sqrt(pow(relative_vx, 2) + pow(vy, 2));

    vx -= B2 * relative_velocity * relative_vx * deltaT / mass;
    vy -= (B2 * relative_velocity * vy / mass + g) * deltaT;
}

void updatePosition()
{
    x += vx * deltaT;
    y += vy * deltaT;
}

void updateVelocity()
{
    forces();
    velocity = sqrt(pow(vx, 2) + pow(vy, 2));
}

double lastDeltaT()
{
    return -1 * prevY / vy; // Time from last y to y=0. Neg because velocity is neg
}

void fire()
{
    std::ofstream outfileT;
    if (tracking)
    {
        std::cout << "Tracking\n";
        outfileT.open("simulationData/tracking/trackingSet1/" + std::to_string(angle) + ".csv");
        outfileT << "x,y\n";
    }

    while (true)
    {
        prevX = x, prevY = y; // for use in calculating the y=0 positions
        updatePosition();
        if (tracking)
        {
            outfileT << x << "," << y << "\n";
        }
        if (y <= 0)
            break; // want to break BEFORE the velocity updates in this case
        updateVelocity();
    }
    double timeBeforeImpact = lastDeltaT();
    x = prevX + vx * timeBeforeImpact;

    double relative_vx = vx - horWindVel; // Calculating velocities relative to the wind. We are only considering horizontal wind.
    double relative_velocity = sqrt(pow(relative_vx, 2) + pow(vy, 2));
    vx -= B2 * relative_velocity * relative_vx * timeBeforeImpact / mass;
    vy -= (B2 * relative_velocity * vy / mass + g) * timeBeforeImpact;
    velocity = sqrt(pow(vx, 2) + pow(vy, 2));
    if (tracking)
    {
        outfileT << x << "," << y << "\n";
        outfileT.close();
    }
}

void aim(double angle)
{
    vx = velocity * cosf64(angle * M_PI / 180);
    vy = velocity * sinf64(angle * M_PI / 180);
}

void ready()
{
    x = 0;
    y = cannonHeight;
    velocity = initial_velocity;
    B2 = 0.5 * dragC * airDensity * surfaceArea; // update here since airDensity is variable

    aim(angle);
    fire();
}

void trainingData()
{

    std::ofstream outfile("simulationData/testSet1.csv");
    outfile << "Air Density,Horizontal Wind Velocity,Initial Velocity,Angle,Range,Impact Speed\n";

    long unsigned simCount = 0;

    for (airDensity = 1.0; airDensity < 1.5; airDensity += 0.05)
    {
        for (horWindVel = -100; horWindVel <= 100; horWindVel += 20)
        {
            for (initial_velocity = 10; initial_velocity < 200; initial_velocity += 20)
            {
                for (angle = 0; angle < 20; angle += 0.5)
                {
                    ready();
                    outfile << airDensity << "," << horWindVel << "," << initial_velocity << "," << angle << "," << x << "," << velocity << "\n";
                    simCount++;
                    if (simCount % 1000 == 0)
                    {
                        std::cout << "Sim Count: " << simCount << "\n";
                    }
                }
                for (double angle = 20; angle < 70; angle += 0.2)
                {
                    ready();
                    outfile << airDensity << "," << horWindVel << "," << initial_velocity << "," << angle << "," << x << "," << velocity << "\n";
                    simCount++;
                    if (simCount % 1000 == 0)
                    {
                        std::cout << "Sim Count: " << simCount << "\n";
                    }
                }
                for (double angle = 70; angle <= 90; angle += 0.5)
                {
                    ready();
                    outfile << airDensity << "," << horWindVel << "," << initial_velocity << "," << angle << "," << x << "," << velocity << "\n";
                    simCount++;
                    if (simCount % 1000 == 0)
                    {
                        std::cout << "Sim Count: " << simCount << "\n";
                    }
                }
            }
        }
    }
    outfile.close();
}

void testTrajectory()
{
    tracking = true;

    airDensity = 1.24;
    horWindVel = -10;
    double initial_velocity = 50;
    double angle_list[] = {20, 30, 45, 60, 70};

    for (double theta : angle_list)
    {
        angle = theta;
        ready();
    }

    tracking = false;
}

int main()
{
    // trainingData();
    testTrajectory();
    return 0;
}