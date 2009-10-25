#pragma once

#include "..\..\GameCore\Judge.hpp"
#include "..\..\GameCore\Map.hpp"
#include "..\..\GameCore\Player.hpp"


namespace Hexxagon
{
    //CMutex g_Mutex(FALSE, NULL);
    class Match
    {
    public:
        Match();

        Match(Map* map, Player* player1, Player* player2, Judge* judge);

        ~Match();

        bool Run();

        void Stop();

        void UpdateUI();

        const Player& GetPlayer(int PlayerID);

        const Player& GetCurPlayer();

        const Action& GetCurAction();

        const Judge& GetJudge();

        const Map&  GetMap();

    private:
        Map*        m_pMap;
        Player*     m_pPlayer1;
        Player*     m_pPlayer2;
        Player*     m_pCurActionPlayer;
        Judge*      m_pJudge;
        bool        m_bStopMath;
        Action      m_CurAction;
    };

    static void RunMatch(void* pMatch)
    {
        Match* pCurMatch = static_cast<Match*>(pMatch);
        if (NULL != pCurMatch)
        {
            pCurMatch->Run();
        }
    }
}