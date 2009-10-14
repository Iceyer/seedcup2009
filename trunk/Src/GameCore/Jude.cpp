#include "Judge.hpp"

using namespace Hexxagon;

Judge::Judge()
:m_pMapMgr(NULL)
{
}

Judge::Judge(MapMgr* pMapMgr)
:m_pMapMgr(pMapMgr)
{
}

Judge::~Judge()
{
}

bool Judge::CheckAction(const Action& action, int PlayerType)
{
    int     MapWidth = m_pMapMgr->MapWidth();
    int     MapHeigth = m_pMapMgr->MapHeigth();

    if (action.PiecePosX < 0 
        || action.PiecePosX >= MapWidth
        || action.PiecePosY < 0
        || action.PiecePosY >= MapHeigth
        || PlayerType != m_pMapMgr->GetMapStatus(action.PiecePosX, action.PiecePosY).m_Type)
    {
        return false;
    }

    if (action.DesPosX < 0 
        || action.DesPosX >= MapWidth
        || action.DesPosY < 0
        || action.DesPosY >= MapHeigth
        || MapItem::EMPTY != m_pMapMgr->GetMapStatus(action.DesPosX, action.DesPosY).m_Type)
    {
        return false;
    }
}