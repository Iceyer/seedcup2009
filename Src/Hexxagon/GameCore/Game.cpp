#include "stdafx.h"
#include "Game.hpp"
#include "..\..\GameCore\Judge.hpp"

using namespace Hexxagon;

Game Game::m_Game;

Game::Game()
{
}

Game::~Game()
{
}

void Game::Prepare()
{
    m_MapMgr.LoadMap("..\\..\\Install\\Map\\Default.map");
    LoadPlayer();
}


void Game::Start()
{
    /*GameLoop*/
    //Judge   judge;
    std::vector<Player>::const_iterator      itorCurPlayer;

    itorCurPlayer = m_PlayerQueue.begin();

    for (; itorCurPlayer != m_PlayerQueue.end(); ++itorCurPlayer)
    {
        (*itorCurPlayer).GetAction();
        //m_MapMgr.UpdateMap();
        UpdateUI();
    }

}

void Game::Pause()
{

}

void Game::End()
{

}

bool Game::LoadPlayer()
{
    return false;
}

void Game::UpdateUI()
{

}