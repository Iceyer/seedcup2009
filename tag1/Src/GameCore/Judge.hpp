#pragma once

#include "..\Player\PlayerAction.hpp"
#include "Map.hpp"

namespace Hexxagon
{
    class Judge
    {
    public:
        Judge();
        Judge(Map* pMapMgr);
        ~Judge();

        void Prepare(Map* pMap);

        bool CheckAction(const Action& action, int PlayerType);

        bool IsGameEnd();
    private:
        Map  *m_pMap;
    };
}