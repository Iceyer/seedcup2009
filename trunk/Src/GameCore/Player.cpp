#include "Player.hpp"
#include "..\Player\MapStatus.hpp"

using namespace Hexxagon;

Player::Player()
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
{
    m_HINST =::LoadLibrary(DllPath.c_str());
    if (NULL == m_HINST)
    {
        return;
    }
    //Fill the Player Information
    pGetPlayerName pFuncPlayerName = NULL;
    pFuncPlayerName = (pGetPlayerName)GetProcAddress(m_HINST, strGetPlayerName.c_str());
    m_Name = pFuncPlayerName();

    pGetPlayerActionFunc pFuncPlayerAction = NULL;
    m_pActionFunc = (pGetPlayerActionFunc)GetProcAddress(m_HINST, strGetPlayerAction.c_str());
}

Player::~Player()
{
    ::FreeLibrary(m_HINST);
    m_HINST = NULL;
}

void Player::SetName(std::string name)
{
    m_Name = name;
}

std::string Player::GetName()
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

void Player::Prepare(Map* pMap)
{
    pSetMap pFuncSetMap = NULL;
    pFuncSetMap = (pSetMap)GetProcAddress(m_HINST, strSetMapFunc.c_str());
    pFuncSetMap(pMap);
}

void Player::SetActionFunc(pGetPlayerActionFunc pFunc)
{
    m_pActionFunc = pFunc;
}


Action Player::GetAction(void) const
{
    return m_pActionFunc();
}
