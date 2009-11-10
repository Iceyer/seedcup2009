#pragma once

#include "PlayerDLLAPI.hpp"
#include <string>

/*
**PiecePosX  需要行动动的棋子在棋盘上的X坐标
**PiecePosY  需要行动的棋子在棋盘上的Y坐标
**DesPosX    需要行动的棋子的目的X坐标
**DesPosY    需要行动的棋子的目的Y坐标
**行动包括复制与移动
*/
PLAYER_DLL_API typedef struct _Action 
{
    int PiecePosX;
    int PiecePosY;
    int DesPosX;
    int DesPosY;
}Action;

PLAYER_DLL_API std::string GetPlayerName();

PLAYER_DLL_API Action GetPlayerAction(int MyPlayerID);

typedef std::string (*pGetPlayerName)(void);

typedef Action (*pGetPlayerActionFunc)(int);

const std::string strGetPlayerName = "GetPlayerName";

const std::string strGetPlayerAction = "GetPlayerAction";

