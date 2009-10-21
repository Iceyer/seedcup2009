#include "Judge.hpp"

using namespace Hexxagon;

Judge::Judge()
: m_pMap(NULL)
, m_totalHoles(0)
, m_stonesOfPlayer1(0)
, m_stonesOfPlayer2(0)
{
}

Judge::Judge(Map* pMapMgr)
:m_pMap(pMapMgr),m_totalHoles(0),m_stonesOfPlayer1(0),m_stonesOfPlayer2(0)
{
}

Judge::~Judge()
{
}

void Judge::Prepare(Map* pMap)
{
    m_pMap = pMap;
}

int Judge::CheckAction(const Action& action, int PlayerType)
{
    int     MapWidth = m_pMap->MapWidth();
    int     MapHeigth = m_pMap->MapHeigth();

    //粗略判断目标位置是否合法
    if (action.PiecePosX < 0 
        || action.PiecePosX >= MapWidth
        || action.PiecePosY < 0
        || action.PiecePosY >= MapHeigth
        || PlayerType != m_pMap->GetMapStatus(action.PiecePosX, action.PiecePosY).m_Type)
    {
        return 0;
    }

    if (action.DesPosX < 0 
        || action.DesPosX >= MapWidth
        || action.DesPosY < 0
        || action.DesPosY >= MapHeigth
        || MapItem::EMPTY != m_pMap->GetMapStatus(action.DesPosX, action.DesPosY).m_Type)
    {
        return 0;
    }

    //具体判断目标位置是在内环还是在外环，还是不合法
    if (   action.DesPosX <= action.PiecePosX+1 
        && action.DesPosX >= action.PiecePosX-1
        && action.DesPosY <= action.PiecePosY+1
        && action.DesPosY >= action.PiecePosY-1
        && action.DesPosX+action.DesPosY != action.PiecePosX+action.PiecePosY)
    {
        return 1;
    }
    else if (action.DesPosX <= action.PiecePosX+2 
          && action.DesPosX >= action.PiecePosX-2
          && action.DesPosY <= action.PiecePosY+2
          && action.DesPosY >= action.PiecePosY-2
          && (   action.DesPosX+action.DesPosY >= action.PiecePosX+action.PiecePosY+2
              || action.DesPosX+action.DesPosY <= action.PiecePosX+action.PiecePosY-2))
    {
        return 2;
    }
    return 0;
}

bool Judge::IsPlayerCanAction(int PlayerID)
{
    return true;
}

int Judge::GetScore(int PlayerID) const
{
    return PlayerID == int(MapItem::PLayer1) ? m_stonesOfPlayer1 : m_stonesOfPlayer2;
}

bool Judge::IsGameEnd()
{
    //计算选手1和选手2所拥有的石子数，以及一共能有多少个放石子的hole
    int     MapWidth = m_pMap->MapWidth();
    int     MapHeigth = m_pMap->MapHeigth();
    m_totalHoles = m_stonesOfPlayer1 = m_stonesOfPlayer2 = 0;
    for (int i = 0; i != MapWidth; i++)
    {
        for (int j = 0;j != MapHeigth; j++)
        {
            switch (m_pMap->GetMapStatus(i,j).m_Type)
            {
            case MapItem::EMPTY:
                m_totalHoles++;
                break;
            case MapItem::PLayer1:
                m_stonesOfPlayer1++;
                break;
            case MapItem::PLayer2:
                m_stonesOfPlayer2++;
                break;
            default:
                break;
            }
        }
    }
    m_totalHoles += (m_stonesOfPlayer1+m_stonesOfPlayer2);
    //如果所有hole都有石子占领了，则游戏结束
    if (m_totalHoles == m_stonesOfPlayer1 + m_stonesOfPlayer2)
    {
        return false;
    }
    return true;
}