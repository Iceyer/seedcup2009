#include "stdafx.h"
#include <process.h>

#include "Game.hpp"
#include "..\..\Player\PlayerAction.hpp"


#include <fstream>

using namespace Hexxagon;

Game Game::m_Game;

Game::Game()
{
}

Game::~Game()
{
    if (m_pCurMatch)
    {
        delete m_pCurMatch;
        m_pCurMatch = NULL;
    }
    if (m_pJudge)
    {
        delete m_pJudge; 
        m_pJudge = NULL;
    }
    /*The Code below would case memory problem*/
//     while(m_PlayerQueue.back())
//     {
//         delete m_PlayerQueue.back();
//         m_PlayerQueue.pop_back();
//     }
    PlayerQueue::iterator itor = m_PlayerQueue.begin();
    for (; itor != m_PlayerQueue.end(); ++itor)
    {
        delete *itor;
    }
}

Match* Game::CurMatch() const
{
    return m_pCurMatch;
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
    m_pJudge = new Judge(*m_MapMgr.Begin());
    PlayerQueue::iterator      itorCurPlayer;
    itorCurPlayer = m_PlayerQueue.begin();
    Player* pPlayer1 = (*itorCurPlayer++);
    Player* pPlayer2 = (*itorCurPlayer);

    m_pCurMatch = new Match(*m_MapMgr.Begin(), pPlayer1, pPlayer2, m_pJudge);
    m_MatchHandle = reinterpret_cast<HANDLE>(_beginthread(Hexxagon::RunMatch, 0 , m_pCurMatch));
}

void Game::Pause()
{
}

void Game::End()
{
    m_pCurMatch->Stop();
    WaitForSingleObject(m_MatchHandle, INFINITE);
}

bool Game::LoadGame(std::string strSaveFileName)
{
    using   std::string;
    using   std::ifstream;
    //Get GameSave File
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
          m_MapMgr.AddMap(val);
        }
    }

    SaveFile.close();
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
