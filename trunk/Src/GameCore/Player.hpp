#pragma once

#include "..\Player\PlayerAction.hpp"

namespace Hexxagon
{
//     enum Direction
//     {
//         UP,
//         DOWN,
//         LEFT,
//         RIGHT,
//         TOPRIGHT,
//         BUTTONLEFT
//     };
// 
//     struct Action
//     {
//         int         XPos;
//         int         YPos;
//         Direction   Direct;
//     };

    class Player
    {
    public:
        Player();

        Player(const Player& player);

        ~Player();

        void SetName(std::string name);

        std::string GetName();

        int SetPlayerID(int id);

        int GetPlayerID();

        void SetActionFunc(pGetPlayerActionFunc pFunc);

        Action GetAction(void) const;
    private:
        std::string             m_Name;
        int                     m_ID;
        pGetPlayerActionFunc    m_pActionFunc;
    };
}