#pragma once

#include "PlayerDLLAPI.hpp"
#include <string>

/*!
 *  PiecePosX  需要行动的棋子在棋盘上的X坐标
 *  PiecePosY  需要行动的棋子在棋盘上的Y坐标
 *  DesPosX    需要行动的棋子的目的X坐标
 *  DesPosY    需要行动的棋子的目的Y坐标
 *  行动包括复制与移动，请根据比赛文档上的说明设置该结构体的值，
 *  对于非法的取值，则视为该次行动无效，参赛者失去本次行动权。
 *  比赛中可能会出现虽有空格子，却无子可下的情况，此时将无论Action返回任何值，
 *  均被视为无效行动，实际上此时也无法计算出合法的Action值。
 */
PLAYER_DLL_API typedef struct _Action 
{
    int PiecePosX;
    int PiecePosY;
    int DesPosX;
    int DesPosY;
}Action;

PLAYER_DLL_API const char* GetPlayerName();

PLAYER_DLL_API Action GetPlayerAction(int MyPlayerID);

typedef const char* (*pGetPlayerName)(void);

typedef Action (*pGetPlayerActionFunc)(int);

const std::string strGetPlayerName = "GetPlayerName";

const std::string strGetPlayerAction = "GetPlayerAction";

