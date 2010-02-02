#pragma once
#include <windows.h>
#include "..\..\GameCore\Map.hpp"
#include "..\..\GameCore\Player.hpp"
#include "..\..\GameCore\Judge.hpp"
#include "Match.hpp"

extern CRITICAL_SECTION m_Critical;

namespace Hexxagon
{

    class Game
    {
    public:
        typedef std::vector<Match*>     MatchQueue;

        static Game& HexxagonGame()
        {
            return m_Game;
        }

        Match* CurMatch() const;

        bool Prepare();

        void Start();

        void NextMatch();

        void Pause();

        void End();

        static void MatchLoop(void* pGame);

        bool LoadGame(std::string strSaveFileName);

        bool LoadPlayer(std::string DllPath);

    public:
        ~Game();

        ///<Data Contral Match and Game
        volatile bool   gbGameStarted;
        volatile bool   gbGameOver;
        volatile bool   gbStopMath;
        volatile bool   gbUIEnable;
        volatile int    gDelay;

    private:
        Game();
        static Game             m_Game;
        Hexxagon::Match*        m_pCurMatch;
        Hexxagon::Judge*        m_pJudge;
        PlayerQueue             m_PlayerQueue;
        MatchQueue              m_MatchQueue;
        MapMgr                  m_MapMgr;
        HANDLE                  m_MatchLoopHandle;

        MatchQueue::iterator    itorMatch;
    };
}
