#include "game.hpp"

Game::Game()
{
}

Game::~Game()
{
}

void Game::Draw()
{
    spaceShip.Draw();
}

void Game::HandleInput()
{
    if (IsKeyDown(KEY_LEFT))
    {
        spaceShip.MoveLeft();
    }
    else if (IsKeyDown(KEY_RIGHT))
    {
        spaceShip.MoveRight();
    }else if(IsKeyDown(KEY_UP))
    {
        spaceShip.MoveUp();
    }else if(IsKeyDown(KEY_DOWN))
    {
        spaceShip.MoveDown();
    }
    // else if(IsKeyDown(KEY_LEFT))
    // {
    //     spaceShip.FireLaser();
    // }
}