#pragma once

#include <string>
#include "windows.h"
#include "..\Player\PlayerAction.hpp"
#include "Map.hpp"

namespace Hexxagon
{
<<<<<<< .mine
    enum Direction
    {
        UP,         //上
        DOWN,       //下
        LEFTUP,     //左上
        LEFTDOWN,   //左下
        RIGHTUP,    //右上
        RIGHTDOWN,  //右下
    };
=======
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
>>>>>>> .r8

    class Player
    {
    public:
        Player();

        Player(const Player& player);

        Player(const std::string& DllPath);

        ~Player();

        void SetName(std::string name);

        std::string GetName();

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