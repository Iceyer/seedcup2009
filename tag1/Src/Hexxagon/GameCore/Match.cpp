#include "stdafx.h"
#include "Match.hpp"
#include "..\HexxagonDlg.h"

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
    while (m_pJudge->IsGameEnd())
    {
        action = (*m_pPlayer1).GetAction();
        if (m_pJudge->CheckAction(action, (*m_pPlayer1).GetPlayerID()))
        {
            m_pMap->UpdateMap(action);
            //m_pJudge
            UpdateUI();
        }
        Sleep(500);
        action = (*m_pPlayer2).GetAction();
        if (m_pJudge->CheckAction(action, (*m_pPlayer1).GetPlayerID()))
        {
            m_pMap->UpdateMap(action);
            UpdateUI();
        }
        Sleep(500);
    }

    delete m_pJudge;
    return false;
}

void Match::UpdateUI()
{
    CHexxagonDlg::Myself()->Invalidate();
}