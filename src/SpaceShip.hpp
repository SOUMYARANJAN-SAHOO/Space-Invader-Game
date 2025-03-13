#pragma once

#include <raylib.h>
#include "Laser.hpp"
#include <vector>

class SpaceShip
{
public:
    SpaceShip();
    ~SpaceShip();
    void Draw();
    void MoveLeft();
    void MoveRight();
    void MoveUp();
    void MoveDown();
    void FireLaser();
    std::vector<Laser> laser;
    Rectangle GetRectangle();
    void Reset();
private:
    Vector2 position;
    Texture2D image;
    double lastFire;
    Sound LaserSound;
};