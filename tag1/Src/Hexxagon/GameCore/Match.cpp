#include "stdafx.h"
#include "Match.hpp"

using namespace Hexxagon;

Match::Match()
{
}

Match::Match(Map* map, Player* player1, Player* player2, Judge* judge)
{
    m_pMap = map;
    m_pPlayer1 = player1;
    m_pPlayer2 = player2;
    m_pJudge = judge;
}

Match::~Match()
{
}

bool Match::Run()
{
    m_pPlayer1->Prepare(m_pMap);
    m_pPlayer1->SetPlayerID(MapItem::PLayer1);
    m_pPlayer2->Prepare(m_pMap);
    m_pPlayer2->SetPlayerID(MapItem::PLayer2);

    m_pJudge->Prepare(m_pMap);

    Action  action;
    int FailorInorOut; //0表示检查结果为失败，1表示移动到内环，2表示移动到外环
    while (m_pJudge->IsGameEnd())
    {
        action = (*m_pPlayer1).GetAction();
        FailorInorOut = m_pJudge->CheckAction(action, (*m_pPlayer1).GetPlayerID());
        if (FailorInorOut)
        {
            m_pMap->UpdateMap(action,FailorInorOut);
            UpdateUI();
        }
        Sleep(200);
        if (!m_pJudge->IsGameEnd())
        {
            break;
        }
        action = (*m_pPlayer2).GetAction();
        FailorInorOut = m_pJudge->CheckAction(action, (*m_pPlayer2).GetPlayerID());
        if (FailorInorOut)
        {
            m_pMap->UpdateMap(action,FailorInorOut);
            UpdateUI();
        }
        Sleep(200);
    }

    return false;
}

const Player& Match::GetPlayer(int PlayerID)
{
    if (MapItem::PLayer1 == PlayerID)
    {
        return *m_pPlayer1;
    }
    else
    {
        return *m_pPlayer2;
    }
}

const Judge& Match::GetJudge()
{
    return *m_pJudge;
}

const Map& Match::GetMap()
{
    return *m_pMap;
}

void Match::UpdateUI()
{
    AfxGetApp()->m_pMainWnd->Invalidate();
}