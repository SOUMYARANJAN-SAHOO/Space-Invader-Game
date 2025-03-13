#pragma once
#include <raylib.h>

class MysteryShip
{
    public:
        MysteryShip();
        ~MysteryShip();
        void Draw();
        void Update();
        void Spawn();
        Rectangle GetRectangel();
        bool active;

    private:
        Texture2D image;
        Vector2 position;
        float speed;
};