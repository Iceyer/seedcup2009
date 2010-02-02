#include "Player.hpp"
#include "..\Player\MapStatus.hpp"

using namespace Hexxagon;

Player::Player()
: m_Name("")
, m_pActionFunc(NULL)
, m_HINST(0)
, m_WinMatchCnt(0)
, m_LoseMatchCnt(0)
, m_DrawMatchCnt(0)
, m_TotalMatchCnt(0)
{
}

Player::Player(const Player &player)
{
    m_ID = player.m_ID;
    m_Name = player.m_Name;
    m_pActionFunc = player.m_pActionFunc;
    m_HINST = player.m_HINST;
}

Player::Player(const std::string& DllPath)
: m_Name("")
, m_pActionFunc(NULL)
, m_HINST(0)
, m_WinMatchCnt(0)
, m_LoseMatchCnt(0)
, m_DrawMatchCnt(0)
, m_TotalMatchCnt(0)
{
    m_HINST =::LoadLibrary(DllPath.c_str());
    if (NULL == m_HINST)
    {
        std::string strError = "无法找到选手的DLl: " + DllPath;
        if (MessageBox(NULL, strError.c_str(), "加载DLL错误", MB_OK) == IDOK)
        {
            return;
        }
    }
    //Fill the Player Information
    pGetPlayerName pFuncPlayerName = NULL;
    pFuncPlayerName = (pGetPlayerName)GetProcAddress(m_HINST, strGetPlayerName.c_str());
    m_Name = pFuncPlayerName();

    m_pActionFunc = (pGetPlayerActionFunc)GetProcAddress(m_HINST, strGetPlayerAction.c_str());

    pSetPlayer pSetPlayerFunc = NULL;
    pSetPlayerFunc = (pSetPlayer)GetProcAddress(m_HINST, strSetPlayerFunc.c_str());
    if(pSetPlayerFunc)
    {
        pSetPlayerFunc(this);
    }
}

Player::~Player()
{
    if (m_HINST)
    {  
        ::FreeLibrary(m_HINST);
        m_HINST = NULL;
    }
}

void Player::SetName(std::string name)
{
    m_Name = name;
}

const std::string& Player::GetName() const
{
    return m_Name;
}

void Player::SetPlayerID(int id)
{
    m_ID = id;
}

int Player::GetPlayerID() const
{
    return m_ID;
}

void Player::EnterMatch(Map* pMap)
{
    pSetMap pFuncSetMap = NULL;
    pFuncSetMap = (pSetMap)GetProcAddress(m_HINST, strSetMapFunc.c_str());
    pFuncSetMap(pMap);
    ++m_TotalMatchCnt;
}

void Player::WinMatch()
{
    ++m_WinMatchCnt;
}

void Player::LoseMatch()
{
    ++m_LoseMatchCnt;
}

void Player::DrawMatch()
{
    ++m_DrawMatchCnt;
}

int Player::WinMatchCnt()
{
    return m_WinMatchCnt;
}

int Player::LoseMatchCnt()
{
    return m_LoseMatchCnt;
}

int Player::DrawMatchCnt()
{
    return m_DrawMatchCnt;
}

int Player::TotalMatchCnt()
{
    return m_TotalMatchCnt;
}

void Player::SetActionFunc(pGetPlayerActionFunc pFunc)
{
    m_pActionFunc = pFunc;
}

Action Player::GetAction(void) const
{
    return m_pActionFunc(m_ID);
}
