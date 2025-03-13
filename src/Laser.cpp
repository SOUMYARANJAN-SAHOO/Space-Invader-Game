#include "Laser.hpp"

Laser::Laser(Vector2 pos, int speed)
{
    this->position = pos;
    this->speed = speed;
    active = true;
}

void Laser::Update()
{
    position.y += speed;
    if(active){
        if(position.y > GetScreenHeight() - 100 || position.y < 25)
        {
            active = false;
        }
    }
}

void Laser::Draw()
{
    DrawRectangle(position.x, position.y, 4, 15, YELLOW);
}

Rectangle Laser::GetRectangle()
{
    return {position.x, position.y, 4, 15};
}
