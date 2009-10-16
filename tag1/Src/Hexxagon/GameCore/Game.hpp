#pragma once

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

        Match* CurMatch();

        void Prepare();

        void Start();

        void Pause();

        void End();

        bool LoadGame(std::string strSaveFileName);

        bool LoadPlayer(std::string DllPath);

        MapMgr      m_MapMgr;
    public:
        ~Game();
    private:
        Game();
        static Game             m_Game;
        Hexxagon::Match*        m_pCurMatch;
        Hexxagon::Judge*        m_pJudge;
        std::vector<Player*>    m_PlayerQueue;
    };
}