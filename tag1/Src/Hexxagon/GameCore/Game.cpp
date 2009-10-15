#include "stdafx.h"
#include <process.h>
#include <windows.h>

#include "Game.hpp"
#include "..\..\GameCore\Judge.hpp"
#include "..\..\Player\PlayerAction.hpp"
#include "Match.hpp"

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
#ifdef _DEBUG
    LoadGame("..\\..\\Install\\Save\\DefaultDebug.sav");
#else
    LoadGame(".\\Save\\Default.sav");
#endif
}


void Game::Start()
{
    /*GameLoop*/
    Judge* pJudge = new Judge(m_MapMgr.CurMap());
    std::vector<Player*>::iterator      itorCurPlayer;
    itorCurPlayer = m_PlayerQueue.begin();
    Player* pPlayer1 = (*itorCurPlayer++);
    Player* pPlayer2 = (*itorCurPlayer);

    Match* pCurMatch = new Match(m_MapMgr.CurMap(), pPlayer1, pPlayer2, pJudge);
    _beginthread(Hexxagon::RunMatch, 0 , pCurMatch);
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

        if (!key.compare("Map"))
        {
          m_MapMgr.SetCurMap(m_MapMgr.AddMap(val));
        }
    }
    return true;
}

bool Game::LoadPlayer(std::string DllPath)
{
    //Load dll
    Player* pNewPlayer = new Player(DllPath);
    //Add a Player
    m_PlayerQueue.push_back(pNewPlayer);
    return  true;
}
