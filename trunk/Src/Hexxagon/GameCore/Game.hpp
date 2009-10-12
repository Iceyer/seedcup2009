#pragma once

#include "Map.hpp"
#include "Player.hpp"

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

    public:
        ~Game();
    private:
        Game();
        static Game             m_Game;
        MapMgr                  m_MapMgr;
        std::vector<Player>     m_PlayerQueue;
    };
}