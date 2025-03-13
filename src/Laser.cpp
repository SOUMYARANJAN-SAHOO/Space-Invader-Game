#include "Laser.hpp"

Laser::Laser(Vector2 pos, int speed)
{
    this->position = pos;
    this->speed = 10;
}

void Laser::Update()
{
}

void Laser::Draw()
{
    DrawRectangle(position.x, position.y, 4, 15, YELLOW);
}
