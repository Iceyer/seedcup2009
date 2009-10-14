#include "Player.hpp"

using namespace Hexxagon;

Player::Player()
{
}

Player::Player(const Player &player)
{
    m_Name = player.m_Name;
    m_pActionFunc = player.m_pActionFunc;
}

Player::~Player()
{
}

void Player::SetName(std::string name)
{
    m_Name = name;
}

std::string Player::GetName()
{
    return m_Name;
}

void Player::SetActionFunc(pGetPlayerActionFunc pFunc)
{
    m_pActionFunc = pFunc;
}


Action Player::GetAction(void) const
{
    return m_pActionFunc();
}
