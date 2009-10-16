#pragma once

#include <string>
#include "windows.h"
#include "..\Player\PlayerAction.hpp"
#include "Map.hpp"

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

        Player(const std::string& DllPath);

        ~Player();

        void SetName(std::string name);

        std::string GetName() const;

        void SetPlayerID(int id);

        int GetPlayerID() const;

        void Prepare(Map* pMap);

        Action GetAction(void) const;

    protected:
        void SetActionFunc(pGetPlayerActionFunc pFunc);

    private:
        HINSTANCE m_HINST;
        std::string             m_Name;
        int                     m_ID;
        pGetPlayerActionFunc    m_pActionFunc;
    };
}