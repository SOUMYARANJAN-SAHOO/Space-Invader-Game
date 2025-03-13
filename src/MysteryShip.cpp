#include "MysteryShip.hpp"

MysteryShip::MysteryShip()
{
    image = LoadTexture("assets/mystery.png");
    active = false;
}

MysteryShip::~MysteryShip()
{
    UnloadTexture(image);
}

void MysteryShip::Draw()
{
    if(active)
    {
        DrawTextureV(image, position, WHITE);
    }
}

void MysteryShip::Spawn(){
    position.y = 90;
    int side = GetRandomValue(0, 1);

    if(side == 0)
    {
        position.x = 25;
        speed = 3;
    }
    else
    {
        position.x = GetScreenWidth() - image.width -25;
        speed = -3;
    }

    active = true;
}

Rectangle MysteryShip::GetRectangel()
{   
    if(active)
    {
        return {position.x, position.y, static_cast<float>(image.width), static_cast<float>(image.height)};
    }
    return {position.x, position.y, 0, 0};
}

void MysteryShip::Update()
{
    if(active)
    {
        position.x += speed;
        if(position.x > GetScreenWidth() - image.width - 25 || position.x < 25)
        {
            active = false;
        }
    }
}