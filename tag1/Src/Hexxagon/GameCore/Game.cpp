#include "stdafx.h"
#include <process.h>

#include "Game.hpp"
#include "..\..\Player\PlayerAction.hpp"

CRITICAL_SECTION m_Critical;

#include <fstream>

using namespace Hexxagon;

Game Game::m_Game;

Game::Game()
{
    gbStopMath = false;
    gbUIEnable = true;
    gDelay = 200;
}

Game::~Game()
{
    m_pCurMatch = NULL;
    MatchQueue::iterator    itorMatch;
    itorMatch = m_MatchQueue.begin();
    for (; itorMatch != m_MatchQueue.end(); ++itorMatch)
    {
        delete *itorMatch;
    }

    if (m_pJudge)
    {
        delete m_pJudge; 
        m_pJudge = NULL;
    }

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

bool Game::Prepare()
{
#ifdef _DEBUG
    return LoadGame("..\\..\\Install\\Save\\DefaultDebug.sav");
#else
    return LoadGame(".\\Save\\Default.sav");
#endif
}

void Game::Start()
{
    //InitMatchQueue
    m_pJudge = new Judge;
    m_pJudge->Prepare();

    PlayerQueue::iterator      itorPlayer1;
    PlayerQueue::iterator      itorPlayer2;
    MapMgr::MapItor             itorMap;
    for (itorMap = m_MapMgr.Begin(); itorMap != m_MapMgr.End(); ++itorMap)
    {
        itorPlayer1 = m_Game.m_PlayerQueue.begin();
        for (; itorPlayer1 != m_PlayerQueue.end(); ++itorPlayer1)
        {
            itorPlayer2 = itorPlayer1;
            ++itorPlayer2;
            for (; itorPlayer2 != m_PlayerQueue.end(); ++itorPlayer2)
            {
                m_pCurMatch = new Match(*itorMap,
                                        *itorPlayer1,
                                        *itorPlayer2,
                                        m_pJudge);
                m_MatchQueue.push_back(m_pCurMatch);
                m_pCurMatch = new Match(*itorMap,
                                        *itorPlayer2,
                                        *itorPlayer1,
                                        m_pJudge);
                m_MatchQueue.push_back(m_pCurMatch);
            }
        }
    }

    m_pCurMatch = *m_MatchQueue.begin();
    m_MatchLoopHandle = reinterpret_cast<HANDLE>(_beginthread(Hexxagon::Game::MatchLoop, 0 , NULL));
}

void Game::MatchLoop(void* /*pGame*/)
{
    MatchQueue::iterator    itorMatch;
    for (itorMatch = m_Game.m_MatchQueue.begin(); itorMatch != m_Game.m_MatchQueue.end(); ++itorMatch)
    {
        m_Game.m_pCurMatch = *itorMatch;
        m_Game.m_pCurMatch->Run();
    }
    m_Game.m_pJudge->LogGame(m_Game.m_PlayerQueue);
}

void Game::Pause()
{
}

void Game::End()
{
    if (m_pCurMatch)
    {
        WaitForSingleObject(m_MatchLoopHandle, INFINITE);
    }
}

bool Game::LoadGame(std::string strSaveFileName)
{
    using   std::string;
    using   std::ifstream;
    //Get GameSave File
    ifstream    SaveFile;

    SaveFile.open(strSaveFileName.c_str(), std::ios::in);
    if (!SaveFile.is_open())
    {
        return false;
    }

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

        if (!key.compare("Player"))
        {
            LoadPlayer(val);
        }

        if (!key.compare("Map"))
        {
          m_MapMgr.AddMap(val);
        }
    }
    SaveFile.close();

    //Player cnt must >= 2
    //Map cnt must >= 1
    if (m_MapMgr.MapCnt() < 1 || m_PlayerQueue.size() < 2)
    {
        MessageBox(NULL, _T("加载地图或选手AI失败"), NULL, 0);
        return false;
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
