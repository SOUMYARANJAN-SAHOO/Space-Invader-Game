#pragma once

#include "SpaceShip.hpp"

class Game
{
public:
    Game();
    ~Game();
    void Update();
    void Draw();
    void HandleInput();

private:
    SpaceShip spaceShip;
};