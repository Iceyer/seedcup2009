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

        const std::string& GetName() const;

        void SetPlayerID(int id);

        int GetPlayerID() const;

        void EnterMatch(Map* pMap);

        void WinMatch();

        void LoseMatch();

        void DrawMatch();

        int WinMatchCnt();

        int LoseMatchCnt();

        int DrawMatchCnt();

        int TotalMatchCnt();

        Action GetAction(void) const;

    protected:
        void SetActionFunc(pGetPlayerActionFunc pFunc);

    private:
        HINSTANCE               m_HINST;
        std::string             m_Name;
        int                     m_ID;
        pGetPlayerActionFunc    m_pActionFunc;

        unsigned int            m_WinMatchCnt;      ///< the win match count
        unsigned int            m_LoseMatchCnt;     ///< the lose count
        unsigned int            m_DrawMatchCnt;     ///< the draw match count
        unsigned int            m_TotalMatchCnt;    ///< the total count
    };

    typedef std::vector<Player*>    PlayerQueue;
}
