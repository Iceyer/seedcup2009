#pragma once

#include "..\Player\PlayerAction.hpp"
#include "Player.hpp"
#include "Map.hpp"

namespace Hexxagon
{
    class Judge
    {
    public:
        Judge();

        ~Judge();

        void Prepare();

        void EnterMatch(Map* pMap);

        int CheckAction(const Action& action, int PlayerID);

        bool IsPlayerCanAction(int PlayerID);

        int GetScore(int PlayerID) const;

        bool IsGameEnd();

        void LogMatch(Map* pMap, Player* pPlayer1, Player* pPlayer2);

        void LogGame(const PlayerQueue& playerQueue);
    private:
        Map  *m_pMap;
        int  m_totalHoles;
        int  m_stonesOfPlayer1;
        int  m_stonesOfPlayer2;
    };
}