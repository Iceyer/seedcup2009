#include "PlayerAction.hpp"
#include "MapStatus.hpp"

/*
** TO-DO :ʹ����Ķ������ƴ��� ���򵥵��ԡ�
*/
const   std::string strTeamName = "�򵥵���";

PLAYER_DLL_API std::string GetPlayerName()
{
    return strTeamName;
}

/*
** MyPlayerID���㵱ǰ��ѡ�ֱ��
** MyPlayerID = 2 ��ʾ���ǲ�����һ������ʱ����
** MyPlayerID = 3 ��ʾ���ǲ����߶�������ʱ����
*/
PLAYER_DLL_API Action GetPlayerAction(int MyPlayerID)
{
    Action action;

    return  action;
}