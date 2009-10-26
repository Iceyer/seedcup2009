#include "stdafx.h"
#include "Match.hpp"
#include <math.h>
#include "..\SenceRender\SenceRender.hpp"
#include "..\resource.h"

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
, m_pCurActionPlayer(NULL)
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

    m_pCurActionPlayer = m_pPlayer1;
    while (m_pJudge->IsGameEnd() && !m_bStopMath)
    {
        Sleep(200);
        if (!m_pJudge->IsPlayerCanAction(m_pCurActionPlayer->GetPlayerID()))
        {
            continue;
        }
        m_CurAction = m_pCurActionPlayer->GetAction();
        m_ActionType = m_pJudge->CheckAction(m_CurAction, m_pCurActionPlayer->GetPlayerID());
        if (m_ActionType)
        {
            Render::SRender().EnableMoveAction();
            while (Render::SRender().IsMoveActionEnd() && !m_bStopMath)
            {
                Sleep(40);
                UpdateUI();
            }
            m_pMap->UpdateMap(m_CurAction,m_ActionType);
            UpdateUI();
            AfxGetApp()->m_pMainWnd->UpdateWindow();
        }
        //������������ѡ�ֵĲ�������
        m_pCurActionPlayer = (m_pCurActionPlayer == m_pPlayer1) ? m_pPlayer2 : m_pPlayer1;

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

void Match::UpdateUI()
{
    if (AfxGetApp()->m_pMainWnd)
    {
        AfxGetApp()->m_pMainWnd->Invalidate();
    }
}