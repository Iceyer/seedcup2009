#include "stdafx.h"
#include "Match.hpp"

using namespace Hexxagon;

Match::Match()
: m_bStopMath(false)
, m_pMap(NULL)
, m_pPlayer1(NULL)
, m_pPlayer2(NULL)
, m_pJudge(NULL)
{
}

Match::Match(Map* map, Player* player1, Player* player2, Judge* judge)
: m_bStopMath(false)
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
    Player *pCurActionPlayer = m_pPlayer1;
    while (m_pJudge->IsGameEnd() && !m_bStopMath)
    {
        if (!m_pJudge->IsPlayerCanAction(pCurActionPlayer->GetPlayerID()))
        {
            continue;
        }
        action = pCurActionPlayer->GetAction();
        FailorInorOut = m_pJudge->CheckAction(action, pCurActionPlayer->GetPlayerID());
        if (FailorInorOut)
        {
            m_pMap->UpdateMap(action,FailorInorOut);
            UpdateUI();
        }
        //轮流调用两个选手的操作函数
        pCurActionPlayer = (pCurActionPlayer == m_pPlayer1) ? m_pPlayer2 : m_pPlayer1;
        Sleep(500);
    }

    UpdateUI();
    return false;
}

void Match::Stop()
{
    m_bStopMath = true;
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
    if (AfxGetApp()->m_pMainWnd)
    {
        AfxGetApp()->m_pMainWnd->Invalidate();
    }
}