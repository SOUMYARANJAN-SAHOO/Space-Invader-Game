#include "Block.hpp"

Block::Block(Vector2 position)
{
    this->position = position;
}

void Block::Draw()
{
    DrawRectangle(position.x, position.y, 3, 3, YELLOW);
}

Rectangle Block::GetRectangle()
{
    return {position.x, position.y, 3, 3};
}
