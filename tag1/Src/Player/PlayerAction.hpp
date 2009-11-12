#pragma once

#include "PlayerDLLAPI.hpp"
#include <string>

/*!
 *  PiecePosX  ��Ҫ�ж��������������ϵ�X����
 *  PiecePosY  ��Ҫ�ж��������������ϵ�Y����
 *  DesPosX    ��Ҫ�ж������ӵ�Ŀ��X����
 *  DesPosY    ��Ҫ�ж������ӵ�Ŀ��Y����
 *  �ж������������ƶ�������ݱ����ĵ��ϵ�˵�����øýṹ���ֵ��
 *  ���ڷǷ���ȡֵ������Ϊ�ô��ж���Ч��������ʧȥ�����ж�Ȩ��
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

