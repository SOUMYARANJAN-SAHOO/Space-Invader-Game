#pragma once

#include "SpaceShip.hpp"
#include "Obstacle.hpp"
#include "Alien.hpp"
#include "MysteryShip.hpp"

class Game
{
public:
    Game();
    ~Game();
    void Update();
    void Draw();
    void HandleInput();
    bool run;
    int GetLives();
    int score;
    int highsScore;
    Music music;
private:
    void DeleteInactiveLasers();
    std::vector<Obstacle> GenerateObstacles();
    std::vector<Alien> GenerateAliens();
    void CheckCollisions();
    SpaceShip spaceShip;
    std::vector<Obstacle> obstacles;
    std::vector<Alien> aliens;
    void MoveAliens();
    int aliensDirection;
    void MoveDownAliens(int distance);
    std::vector<Laser> alienLasers;
    void AlienShootLaser();
    constexpr static float alienLaserShootInterval = 0.35;
    float timeLastAlienFired;
    MysteryShip mysteryShip;
    float mysteryShipSpawnInterval;
    float timeLastMysteryShipSpawned;
    int lives;
    void GameOver();
    void ResetGame();
    void InitGame();
    void checkHighScore();
    void saveHighScore(int highScore);
    int loadHighScore();
    Sound explosionSound;
};