#include "Judge.hpp"

using namespace Hexxagon;

Judge::Judge()
:m_pMap(NULL)
{
}

Judge::Judge(Map* pMapMgr)
:m_pMap(pMapMgr)
{
}

Judge::~Judge()
{
}

void Judge::Prepare(Map* pMap)
{
    m_pMap = pMap;
}

bool Judge::CheckAction(const Action& action, int PlayerType)
{
    int     MapWidth = m_pMap->MapWidth();
    int     MapHeigth = m_pMap->MapHeigth();

    if (action.PiecePosX < 0 
        || action.PiecePosX >= MapWidth
        || action.PiecePosY < 0
        || action.PiecePosY >= MapHeigth
        || PlayerType != m_pMap->GetMapStatus(action.PiecePosX, action.PiecePosY).m_Type)
    {
        return false;
    }

    if (action.DesPosX < 0 
        || action.DesPosX >= MapWidth
        || action.DesPosY < 0
        || action.DesPosY >= MapHeigth
        || MapItem::EMPTY != m_pMap->GetMapStatus(action.DesPosX, action.DesPosY).m_Type)
    {
        return false;
    }
    return true;
}

int Judge::GetScore(int PlayerID) const
{
    return 0;
}


bool Judge::IsGameEnd() const
{
    return true;
}