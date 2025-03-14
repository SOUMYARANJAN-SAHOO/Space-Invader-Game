#pragma once

#include <raylib.h>

class Laser{
    public:
        Laser(Vector2 pos, int speed, Color color);
        void Update();
        void Draw();
        bool active;
        Rectangle GetRectangle();
    private:
        Vector2 position;
        int speed;
        Color color;
};