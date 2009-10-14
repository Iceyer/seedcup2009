#include "stdafx.h"
#include <windows.h>

#include "Game.hpp"
#include "..\..\GameCore\Judge.hpp"
#include "..\..\Player\PlayerAction.hpp"

#include <fstream>

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
    LoadGame("..\\..\\Install\\Save\\Default.sav");
    m_MapMgr.LoadMap("..\\..\\Install\\Map\\Default.map");
}


void Game::Start()
{
    /*GameLoop*/
    Judge   judge;
    Action  action;
    std::vector<Player>::const_iterator      itorCurPlayer;

    itorCurPlayer = m_PlayerQueue.begin();

    for (; itorCurPlayer != m_PlayerQueue.end(); ++itorCurPlayer)
    {
        action = (*itorCurPlayer).GetAction();
        //judge.CheckAction(action, (*itorCurPlayer).;
        m_MapMgr.UpdateMap(action);
        UpdateUI();
    }

}

void Game::Pause()
{

}

void Game::End()
{

}

bool Game::LoadGame(std::string strSaveFileName)
{
    using   std::string;
    //Get GameSave File
    using   std::ifstream;
    ifstream    SaveFile;
    SaveFile.open(strSaveFileName.c_str(), std::ios::in);

    string  key;
    string  val;
    char    buffer[256];

    while (SaveFile.getline(buffer, 255))
    {
        string  line(buffer);
        size_t  pos;
        pos = line.find('=');
        key = line.substr(0, pos);
        val = line.substr(pos + 2, line.length() - pos - 3);
        if (!key.compare("Player1") || !key.compare("Player2"))
        {
            LoadPlayer(val);
        }
    }
    return true;
}

bool Game::LoadPlayer(std::string DllPath)
{
    //Load dll
    HINSTANCE hinst=::LoadLibrary(DllPath.c_str()); 
    if (NULL == hinst)
    {
        return false;
    }
    //Fill the Player Information
    pGetPlayerName pFuncPlayerName = NULL;
    pFuncPlayerName = (pGetPlayerName)GetProcAddress(hinst, strGetPlayerName.c_str());

    pGetPlayerActionFunc pFuncPlayerAction = NULL;
    pFuncPlayerAction = (pGetPlayerActionFunc)GetProcAddress(hinst, strGetPlayerAction.c_str());

    Player NewPlayer;
    NewPlayer.SetName(pFuncPlayerName());
    NewPlayer.SetActionFunc(pFuncPlayerAction);

    //Add a Player
    m_PlayerQueue.push_back(NewPlayer);
    return  true;
}

void Game::UpdateUI()
{

}