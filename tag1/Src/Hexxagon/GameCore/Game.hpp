#pragma once

#include "..\..\GameCore\Map.hpp"
#include "..\..\GameCore\Player.hpp"
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

        void Prepare();

        void Start();

        void Pause();

        void End();

        Match* CurMatch();

        bool LoadGame(std::string strSaveFileName);

        MapMgr      m_MapMgr;

        ~Game();
    protected:
        bool LoadPlayer(std::string DllPath);

    private:
        typedef std::vector<Player*> PlayerQueue;

        Game();
        static Game     m_Game;
        PlayerQueue     m_PlayerQueue;
        Match*          m_pCurMatch;
    };
}