#pragma once

namespace Hexxagon
{
    class Game
    {
    public:

        static Game& HexxagonGame()
        {
            return m_Game;
        }

        void Start();

        void Pause();

        void End();

    public:
        ~Game();
    private:
        Game();
        static Game    m_Game;
    };
}