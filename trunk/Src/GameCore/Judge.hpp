#pragma once

#include "..\Player\PlayerAction.hpp"
#include "Map.hpp"

namespace Hexxagon
{
    class Judge
    {
    public:
        Judge();
        Judge(MapMgr* pMapMgr);
        ~Judge();

        bool CheckAction(const Action& action, int PlayerType);
    private:
        MapMgr  *m_pMapMgr;
    };
}