#include "PlayerAction.hpp"
#include "MapStatus.hpp"

const   std::string strTeamName = "TestPlayer";

PLAYER_DLL_API std::string GetPlayerName()
{
    return strTeamName;
}

PLAYER_DLL_API Action GetPlayerAction()
{
    return  Action();
}