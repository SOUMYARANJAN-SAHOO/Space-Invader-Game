#include "game.hpp"
#include <algorithm>
#include <iostream>
#include <fstream>

Game::Game()
{
    music = LoadMusicStream("assets/music.ogg");
    explosionSound = LoadSound("assets/explosion.ogg");
    PlayMusicStream(music);
    InitGame();
}

Game::~Game()
{
    UnloadMusicStream(music);
    UnloadSound(explosionSound);
    Alien::UnloadImages();
}

void Game::Update()
{

    if (run)
    {
        double currentTime = GetTime();
        if (currentTime - timeLastMysteryShipSpawned > mysteryShipSpawnInterval)
        {
            mysteryShip.Spawn();
            timeLastMysteryShipSpawned = currentTime;
            mysteryShipSpawnInterval = GetRandomValue(10, 20);
        }

        for (auto &laser : spaceShip.laser)
        {
            laser.Update();
        }

        MoveAliens();

        AlienShootLaser();
        for (auto &laser : alienLasers)
        {
            laser.Update();
        }

        DeleteInactiveLasers();
        mysteryShip.Update();

        CheckCollisions();
    }
    else
    {
        if (IsKeyDown(KEY_ENTER))
        {
            ResetGame();
            InitGame();
        }
    }
}

void Game::Draw()
{
    spaceShip.Draw();
    for (auto &laser : spaceShip.laser)
    {
        laser.Draw();
    }
    for (auto &obstacle : obstacles)
    {
        obstacle.Draw();
    }
    for (auto &alien : aliens)
    {
        alien.Draw();
    }
    for (auto &laser : alienLasers)
    {
        laser.Draw();
    }
    mysteryShip.Draw();
}

void Game::HandleInput()
{
    if (run)
    {
        if (IsKeyDown(KEY_LEFT))
        {
            spaceShip.MoveLeft();
        }
        if (IsKeyDown(KEY_RIGHT))
        {
            spaceShip.MoveRight();
        }
        if (IsKeyDown(KEY_UP))
        {
            spaceShip.MoveUp();
        }
        if (IsKeyDown(KEY_DOWN))
        {
            spaceShip.MoveDown();
        }
        if (IsKeyDown(KEY_SPACE))
        {
            spaceShip.FireLaser();
        }
    }
}

int Game::GetLives()
{
    return lives;
}

void Game::DeleteInactiveLasers()
{
    spaceShip.laser.erase(std::remove_if(spaceShip.laser.begin(), spaceShip.laser.end(), [](Laser &laser)
                                         { return !laser.active; }),
                          spaceShip.laser.end());
    alienLasers.erase(std::remove_if(alienLasers.begin(), alienLasers.end(), [](Laser &laser)
                                     { return !laser.active; }),
                      alienLasers.end());
}

std::vector<Obstacle> Game::GenerateObstacles()
{

    int obstacleWidth = Obstacle::grid[0].size() * 3;
    float gap = (GetScreenWidth() - 3 * obstacleWidth) / 4;

    for (int i = 0; i < 3; i++)
    {
        float offsetx = (i + 1) * gap + i * obstacleWidth;
        Vector2 position = {offsetx, GetScreenHeight() - 250};
        Obstacle obstacle = Obstacle(position);
        obstacles.push_back(obstacle);
    }

    return obstacles;
}

std::vector<Alien> Game::GenerateAliens()
{
    std::vector<Alien> aliens;

    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 11; j++)
        {
            int alienType;
            if (i == 0)
            {
                alienType = 3;
            }
            else if (i == 1 || i == 2)
            {
                alienType = 2;
            }
            else
            {
                alienType = 1;
            }

            Vector2 position = {static_cast<float>(55 + j * 60), static_cast<float>(110 + i * 60)};
            Alien alien = Alien(alienType, position);
            aliens.push_back(alien);
        }
    }

    return aliens;
}
void Game::CheckCollisions()
{
    // space ship laser
    for (auto &laser : spaceShip.laser)
    {
        // vs alien
        for (auto it = aliens.begin(); it != aliens.end();)
        {
            if (CheckCollisionRecs(laser.GetRectangle(), it->GetRectangle()))
            {
                PlaySound(explosionSound);
                if (it->type == 1)
                {
                    score += 100;
                }
                else if (it->type == 2)
                {
                    score += 200;
                }
                else if (it->type == 3)
                {
                    score += 300;
                }
                checkHighScore();
                laser.active = false;
                it = aliens.erase(it);
            }
            else
            {
                ++it;
            }
        }

        // vs obstacle
        for (auto &obstacle : obstacles)
        {
            for (auto it = obstacle.blocks.begin(); it != obstacle.blocks.end();)
            {
                if (CheckCollisionRecs(laser.GetRectangle(), it->GetRectangle()))
                {
                    laser.active = false;
                    it = obstacle.blocks.erase(it);
                }
                else
                {
                    ++it;
                }
            }
        }

        // vs mystery ship
        if (CheckCollisionRecs(laser.GetRectangle(), mysteryShip.GetRectangel()))
        {
            laser.active = false;
            mysteryShip.active = false;
            score += 500;
            checkHighScore();
            PlaySound(explosionSound);
        }
    }

    // alien laser
    for (auto &laser : alienLasers)
    {
        if (CheckCollisionRecs(laser.GetRectangle(), spaceShip.GetRectangle()))
        {
            laser.active = false;
            lives--;
            if (lives == 0)
            {
                GameOver();
            }
        }

        for (auto &obstacle : obstacles)
        {
            for (auto it = obstacle.blocks.begin(); it != obstacle.blocks.end();)
            {
                if (CheckCollisionRecs(laser.GetRectangle(), it->GetRectangle()))
                {
                    laser.active = false;
                    it = obstacle.blocks.erase(it);
                }
                else
                {
                    ++it;
                }
            }
        }
    }

    // alien collision with obstacles
    for (auto &alien : aliens)
    {
        for (auto &obstacle : obstacles)
        {
            for (auto it = obstacle.blocks.begin(); it != obstacle.blocks.end();)
            {
                if (CheckCollisionRecs(alien.GetRectangle(), it->GetRectangle()))
                {
                    it = obstacle.blocks.erase(it);
                }
                else
                {
                    ++it;
                }
            }
        }

        if (CheckCollisionRecs(alien.GetRectangle(), spaceShip.GetRectangle()))
        {
            GameOver();
        }
    }
}

void Game::MoveAliens()
{
    for (auto &alien : aliens)
    {
        if (alien.position.x + alien.alienImages[alien.type - 1].width > GetScreenWidth() - 25)
        {
            aliensDirection = -1;
            MoveDownAliens(4);
        }
        if (alien.position.x < 25)
        {
            aliensDirection = 1;
            MoveDownAliens(4);
        }
        alien.Update(aliensDirection);
    }
}

void Game::MoveDownAliens(int distance)
{
    for (auto &alien : aliens)
    {
        alien.position.y += distance;
    }
}

void Game::AlienShootLaser()
{
    double currentTime = GetTime();
    if (currentTime - timeLastAlienFired >= alienLaserShootInterval && !aliens.empty())
    {
        int randomAlienIndex = GetRandomValue(0, aliens.size() - 1);
        Alien &alien = aliens[randomAlienIndex];
        Vector2 laserPosition = {alien.position.x + alien.alienImages[alien.type - 1].width / 2, alien.position.y + alien.alienImages[alien.type - 1].height};
        alienLasers.push_back(Laser(laserPosition, 6));

        timeLastAlienFired = GetTime();
    }
}

void Game::GameOver()
{
    run = false;
}

void Game::InitGame()
{
    run = true;
    obstacles = GenerateObstacles();
    aliens = GenerateAliens();
    aliensDirection = 1;
    timeLastAlienFired = 0.0;
    mysteryShip.Spawn();
    timeLastMysteryShipSpawned = 0.0;
    mysteryShipSpawnInterval = GetRandomValue(10, 20);
    lives = 3;
    score = 0;
    highsScore = loadHighScore();
}

void Game::ResetGame()
{
    spaceShip.Reset();
    aliens.clear();
    alienLasers.clear();
    obstacles.clear();
}

void Game::checkHighScore()
{
    if (score > highsScore)
    {
        highsScore = score;
        saveHighScore(highsScore);
    }
}

void Game::saveHighScore(int highscore)
{
    std::ofstream highscoreFile("highscore.txt");
    if (highscoreFile.is_open())
    {
        highscoreFile << highscore;
        highscoreFile.close();
    }
    else
    {
        std::cerr << "Failed to save highscore to file" << std::endl;
    }
}

int Game::loadHighScore()
{
    int loadedHighscore = 0;
    std::ifstream highscoreFile("highscore.txt");
    if (highscoreFile.is_open())
    {
        highscoreFile >> loadedHighscore;
        highscoreFile.close();
    }
    else
    {
        std::cerr << "Failed to load highscore from file." << std::endl;
    }
    return loadedHighscore;
}
