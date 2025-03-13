#include "SpaceShip.hpp"

SpaceShip::SpaceShip()
{
    image = LoadTexture("assests/spaceship.png");
    position.x = (GetScreenWidth() - image.width) / 2;
    position.y = GetScreenHeight() - image.height;
}

SpaceShip::~SpaceShip()
{
    UnloadTexture(image);
}

void SpaceShip::Draw()
{
    DrawTextureV(image, position, WHITE);
}

void SpaceShip::MoveRight()
{
    position.x += 7;
    if(position.x < 0)
    {
        position.x = 0;
    }
    else if(position.x > GetScreenWidth() - image.width)
    {
        position.x = GetScreenWidth() - image.width;
    }
}

void SpaceShip::MoveLeft()
{
    position.x -= 7;
    if(position.x < 0)
    {
        position.x = 0;
    }
    else if(position.x > GetScreenWidth() - image.width)
    {
        position.x = GetScreenWidth() - image.width;
    }
}

void SpaceShip::MoveUp()
{
    position.y -= 7;
    if (position.y < 30)
    {
        position.y = 30;
    }
    else if (position.y > GetScreenHeight() - image.height)
    {
        position.y = GetScreenHeight() - image.height;
    }
}

void SpaceShip::MoveDown()
{
    position.y += 7;
    if (position.y < 0)
    {
        position.y = 0;
    }
    else if (position.y > GetScreenHeight() - image.height)
    {
        position.y = GetScreenHeight() - image.height;
    }
}