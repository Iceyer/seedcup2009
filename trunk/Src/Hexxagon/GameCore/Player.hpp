#pragma once

namespace Hexxagon
{
    enum Direction
    {
        UP,
        DOWN,
        LEFT,
        RIGHT,
        TOPRIGHT,
        BUTTONLEFT
    };

    struct Action
    {
        int         XPos;
        int         YPos;
        Direction   Direct;
    };

    class Player
    {
    public:
        Player();

        ~Player();

        void GetAction(void) const;
    };
}