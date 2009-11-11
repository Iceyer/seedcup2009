#include "Judge.hpp"
#include <fstream>

using namespace Hexxagon;

Judge::Judge()
: m_pMap(NULL)
, m_totalHoles(0)
, m_stonesOfPlayer1(0)
, m_stonesOfPlayer2(0)
{
}

Judge::~Judge()
{
}

void Judge::EnterMatch(Map* pMap)
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


bool Judge::CheckPlayerEnable(int PlayerID)
{
    bool ret = false;
    PlayerID;
    return ret;
}

bool Judge::IsPlayerCanAction(int PlayerID)
{
    PlayerID;
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

void Judge::Prepare()
{
    std::ofstream ofResultFile;

    ofResultFile.open(".\\Log.txt", std::ios::out | std::ios::ate);

    if (!ofResultFile.is_open())
    {
        return;
    }
    ofResultFile.close();
}

void Judge::LogMatch(Map* pMap, Player* pPlayer1, Player* pPlayer2)
{
    std::ofstream ofResultFile;

    ofResultFile.open(".\\Log.txt", std::ios::out | std::ios::app);

    if (!ofResultFile.is_open())
    {
        return;
    }

    ofResultFile<<"Map:"<<pMap->MapFilePath()<<std::endl
                <<"Player1:"<<pPlayer1->GetName()<<std::endl
                <<"Score:"<<GetScore(MapItem::PLayer1)<<std::endl
                <<"Player2:"<<pPlayer2->GetName()<<std::endl
                <<"Score:"<<GetScore(MapItem::PLayer2)<<std::endl;
    if (GetScore(MapItem::PLayer1) > GetScore(MapItem::PLayer2))
    {
        ofResultFile<<"Winner:"<<std::endl
                    <<"Player1"<<pPlayer1->GetName()<<std::endl<<std::endl;
    } 
    else
    {
        ofResultFile<<"Winner:"<<std::endl
                    <<"Player2:"<<pPlayer2->GetName()<<std::endl<<std::endl;
    }
    ofResultFile.close();
}

void Judge::LogGame(const PlayerQueue& playerQueue)
{
    std::ofstream ofResultFile;

    ofResultFile.open(".\\Log.txt", std::ios::out | std::ios::app);

    if (!ofResultFile.is_open())
    {
        return;
    }

    PlayerQueue::const_iterator     itorpPlayer;

    for (itorpPlayer = playerQueue.begin(); itorpPlayer != playerQueue.end(); ++itorpPlayer)
    {
        ofResultFile<<(*itorpPlayer)->GetName()<<std::endl
                    <<"TotalMatchCnt :  "<<(*itorpPlayer)->TotalMatchCnt()<<std::endl
                    <<"WinMatchCnt :    "<<(*itorpPlayer)->WinMatchCnt()<<std::endl
                    <<"LoseMatchCnt :   "<<(*itorpPlayer)->LoseMatchCnt()<<std::endl
                    <<"DrawMatchCnt :   "<<(*itorpPlayer)->DrawMatchCnt()<<std::endl
                    <<std::endl;
    }

    ofResultFile.close();
}
