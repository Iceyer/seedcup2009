#pragma once
#include <windows.h>
#include "..\..\GameCore\Map.hpp"
#include "..\..\GameCore\Player.hpp"
#include "..\..\GameCore\Judge.hpp"
#include "Match.hpp"

namespace Hexxagon
{
    class Game
    {
    public:

        static Game& HexxagonGame()
        {
            return m_Game;
        }

        Match* CurMatch() const;

        bool Prepare();

        void Start();

        void Pause();

        void End();

        static void MatchLoop(void* pGame);

        bool LoadGame(std::string strSaveFileName);

        bool LoadPlayer(std::string DllPath);

    public:
        ~Game();
    private:
        typedef std::vector<Player*> PlayerQueue;

        Game();
        static Game             m_Game;
        Hexxagon::Match*        m_pCurMatch;
        Hexxagon::Judge*        m_pJudge;
        PlayerQueue             m_PlayerQueue;
        MapMgr                  m_MapMgr;
        HANDLE                  m_MatchHandle;
    };
}