#pragma once

#include "PlayerDLLAPI.hpp"
#include <string>

PLAYER_DLL_API typedef struct _Action 
{
    int PiecePosX;
    int PiecePosY;
    int DesPosX;
    int DesPosY;
}Action;

PLAYER_DLL_API std::string GetPlayerName();

PLAYER_DLL_API Action GetPlayerAction();

typedef std::string (*pGetPlayerName)(void);

typedef Action (*pGetPlayerActionFunc)(void);

const std::string strGetPlayerName = "GetPlayerName";

const std::string strGetPlayerAction = "GetPlayerAction";