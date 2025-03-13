#pragma once

#include <raylib.h>

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

private:
    Vector2 position;
    Texture2D image;
};