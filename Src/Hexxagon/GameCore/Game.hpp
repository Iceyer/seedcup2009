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

        bool LoadPlayer();

        void UpdateUI();

        MapMgr      m_MapMgr;
    public:
        ~Game();
    private:
        Game();
        static Game             m_Game;
        std::vector<Player>     m_PlayerQueue;
    };
}