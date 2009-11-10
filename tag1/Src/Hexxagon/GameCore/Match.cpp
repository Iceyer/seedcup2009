#include "stdafx.h"
#include "Match.hpp"
#include <math.h>
#include "..\SenceRender\SenceRender.hpp"
#include "..\resource.h"

//#define 

using namespace Hexxagon;

Match::Match()
: m_bMatchEnd(false)
, m_pMap(NULL)
, m_pPlayer1(NULL)
, m_pPlayer2(NULL)
, m_pJudge(NULL)
, m_pWiner(NULL)
{
}

Match::Match(Map* map, Player* player1, Player* player2, Judge* judge)
: m_bMatchEnd(false)
, m_pCurActionPlayer(NULL)
, m_pWiner(NULL)
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
    m_bMatchEnd = false;
    m_pMap->ReLoadMap();
    m_pPlayer1->EnterMatch(m_pMap);
    m_pPlayer1->SetPlayerID(MapItem::PLayer1);
    m_pPlayer2->EnterMatch(m_pMap);
    m_pPlayer2->SetPlayerID(MapItem::PLayer2);
    m_pJudge->EnterMatch(m_pMap);

    m_pCurActionPlayer = m_pPlayer1;
    EnterCriticalSection(&m_Critical);
    while (m_pJudge->IsGameEnd() && !Game::HexxagonGame().gbStopMath)
    {
        LeaveCriticalSection(&m_Critical);
        Sleep(Game::HexxagonGame().gbUIEnable ? 200 : 0);
        if (!m_pJudge->IsPlayerCanAction(m_pCurActionPlayer->GetPlayerID()))
        {
            continue;
        }
        //Check Player Can Action
        //bool bCanAction = true;
        //bCanAction = m_pJudge->CheckPlayerEnable(m_pCurActionPlayer->GetPlayerID());
        m_CurAction = m_pCurActionPlayer->GetAction();
        m_ActionType = m_pJudge->CheckAction(m_CurAction, m_pCurActionPlayer->GetPlayerID());
        //m_ActionType 非零时操作合法。
        if (m_ActionType)
        {
            EnterCriticalSection(&m_Critical);
            if (Game::HexxagonGame().gbUIEnable)
            {
                Render::SRender().EnableMoveAction();
                LeaveCriticalSection(&m_Critical);
                EnterCriticalSection(&m_Critical);
                while (Render::SRender().IsMoveActionEnd() && !Game::HexxagonGame().gbStopMath)
                {
                    LeaveCriticalSection(&m_Critical);
                    Sleep(40);
                    UpdateUI();
                    EnterCriticalSection(&m_Critical);
                }
                LeaveCriticalSection(&m_Critical);
            }
            LeaveCriticalSection(&m_Critical);
            m_pMap->UpdateMap(m_CurAction, m_ActionType);
        }
        UpdateUI();
        //轮流调用两个选手的操作函数
        m_pCurActionPlayer = (m_pCurActionPlayer == m_pPlayer1) ? m_pPlayer2 : m_pPlayer1;
        EnterCriticalSection(&m_Critical);
    }
    LeaveCriticalSection(&m_Critical);

    m_pJudge->LogMatch(m_pMap, m_pPlayer1, m_pPlayer2);

    if (m_pJudge->GetScore(m_pPlayer1->GetPlayerID()) == m_pJudge->GetScore(m_pPlayer2->GetPlayerID()))
    {
        m_pPlayer1->DrawMatch();
        m_pPlayer2->DrawMatch();
        m_pWiner = NULL;
    }
    else if (m_pJudge->GetScore(m_pPlayer1->GetPlayerID()) > m_pJudge->GetScore(m_pPlayer2->GetPlayerID()))
    {
        m_pPlayer1->WinMatch();
        m_pPlayer2->LoseMatch();
        m_pWiner = m_pPlayer1;
    }
    else if (m_pJudge->GetScore(m_pPlayer1->GetPlayerID()) < m_pJudge->GetScore(m_pPlayer2->GetPlayerID()))
    {
        m_pPlayer1->LoseMatch();
        m_pPlayer2->WinMatch();
        m_pWiner = m_pPlayer2;
    }

    m_bMatchEnd = true;

    UpdateUI();
    return false;
}

const Player& Match::GetPlayer(int PlayerID)
{
    if (MapItem::PLayer1 == PlayerID)
    {
        return *m_pPlayer1;
    }
    else if (MapItem::PLayer2 == PlayerID)
    {
        return *m_pPlayer2;
    }
}

const Player& Match::GetCurPlayer()
{
    return *m_pCurActionPlayer;
}

const Action& Match::GetCurAction()
{
    return m_CurAction;
}

int Match::GetActionType()
{
    return m_ActionType;
}

const Judge& Match::GetJudge()
{
    return *m_pJudge;
}

const Map& Match::GetMap()
{
    return *m_pMap;
}

bool Match::IsMatchEnd()
{
    return m_bMatchEnd;
}

Player* Match::Winner()
{
    return m_pWiner;
}

void Match::UpdateUI()
{
    if (AfxGetApp() && AfxGetApp()->m_pMainWnd)
    {
        AfxGetApp()->m_pMainWnd->Invalidate();
        return;
    }
}
