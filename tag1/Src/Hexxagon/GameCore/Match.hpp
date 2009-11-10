#pragma once

#include "..\..\GameCore\Judge.hpp"
#include "..\..\GameCore\Map.hpp"
#include "..\..\GameCore\Player.hpp"


namespace Hexxagon
{
    class Match
    {
    public:
        Match();

        Match(Map* map, Player* player1, Player* player2, Judge* judge);

        ~Match();

        bool Run();

        void UpdateUI();

        const Player& GetPlayer(int PlayerID);

        const Player& GetCurPlayer();

        const Action& GetCurAction();

        /*
         * out @ 0 = Invade
         *       1 = Copy
                 2 = Move
         */
        int GetActionType();

        const Judge& GetJudge();

        const Map&  GetMap();

        bool IsMatchEnd();

        Player* Winner();

    private:
        Map*        m_pMap;
        Player*     m_pPlayer1;
        Player*     m_pPlayer2;
        Player*     m_pWiner;
        Player*     m_pCurActionPlayer;
        Judge*      m_pJudge;
        int         m_ActionType; /*! 0 = Invade, 1 =  copy 2 Move*/
        Action      m_CurAction;

        bool        m_bMatchEnd;
    };
}