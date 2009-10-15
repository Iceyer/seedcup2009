#pragma once

#include "..\..\GameCore\Map.hpp"
#include "..\..\GameCore\Player.hpp"

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

        bool LoadGame(std::string strSaveFileName);

        bool LoadPlayer(std::string DllPath);

        MapMgr      m_MapMgr;
    public:
        ~Game();
    private:
        typedef std::vector<Player*> PlayerQueue;

        Game();
        static Game     m_Game;
        PlayerQueue     m_PlayerQueue;
    };
}