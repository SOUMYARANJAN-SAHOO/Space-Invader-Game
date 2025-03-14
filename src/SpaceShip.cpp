#include "SpaceShip.hpp"

SpaceShip::SpaceShip()
{
    image = LoadTexture("assets/spaceship.png");
    position.x = (GetScreenWidth() - image.width) / 2;
    position.y = GetScreenHeight() - image.height - 100;
    lastFire = 0.0;
    LaserSound = LoadSound("assets/laser.ogg");
}

SpaceShip::~SpaceShip()
{
    UnloadSound(LaserSound);
    UnloadTexture(image);
}

void SpaceShip::Draw()
{
    DrawTextureV(image, position, WHITE);
}

void SpaceShip::MoveRight()
{
    position.x += 7;
    if(position.x > GetScreenWidth() - image.width)
    {
        position.x = GetScreenWidth() - image.width;
    }
}

void SpaceShip::MoveLeft()
{
    position.x -= 7;
    if(position.x < 25)
    {
        position.x = 25;
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

void SpaceShip::FireLaser()
{
    if(GetTime() - lastFire >= 0.35)
    {
        PlaySound(LaserSound);
        Laser laserBullet = Laser(Vector2{position.x + image.width / 2 - 2, position.y}, -6, GREEN);
        laser.push_back(laserBullet);
        lastFire = GetTime();
    }
    
}
Rectangle SpaceShip::GetRectangle()
{
    return {position.x, position.y, static_cast<float>(image.width), static_cast<float>(image.height)};
}

void SpaceShip::Reset()
{
    position.x = (GetScreenWidth() - image.width) / 2;
    position.y = GetScreenHeight() - image.height - 100;
    laser.clear();
}
