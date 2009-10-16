#pragma once

#include "..\Player\PlayerAction.hpp"
#include "Map.hpp"

namespace Hexxagon
{
    class Judge
    {
    public:
        Judge();
        Judge(Map* pMapMgr);
        ~Judge();

        void Prepare(Map* pMap);

        int CheckAction(const Action& action, int PlayerType);

        int GetScore(int PlayerID) const;

        bool IsGameEnd();
    private:
        Map  *m_pMap;
        int  m_totalHoles;
        int  m_stonesOfPlayer1;
        int  m_stonesOfPlayer2;
    };
}