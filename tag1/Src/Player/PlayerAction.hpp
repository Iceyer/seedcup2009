#pragma once

#include "PlayerDLLAPI.hpp"
#include <string>

/*
**PiecePosX  ��Ҫ�ж����������������ϵ�X����
**PiecePosY  ��Ҫ�ж��������������ϵ�Y����
**DesPosX    ��Ҫ�ж������ӵ�Ŀ��X����
**DesPosY    ��Ҫ�ж������ӵ�Ŀ��Y����
**�ж������������ƶ�
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

