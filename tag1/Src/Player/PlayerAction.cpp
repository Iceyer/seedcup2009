#include "PlayerAction.hpp"
#include "MapStatus.hpp"

/*!
 * TO-DO :ʹ����Ķ������ƴ��� ���򵥵��ԡ�
*/
std::string strTeamName = "�򵥵���";

PLAYER_DLL_API const char* GetPlayerName()
{
    return strTeamName.c_str();
}

/*!
 * @brief ��ò�������һ�������Ļص�����
 * @prama MyPlayerID intger 
 *  MyPlayerID���㵱ǰ��ѡ�ֱ��
 *  ��MyPlayerID = 2 ��ʾ���ǲ�����һ
 *  ��MyPlayerID = 3 ��ʾ���ǲ����߶�
 *  ��һ�ֱ����У�ѡ�ֱ�Ų���ı䣬����ͬ�ֱ����п��ܲ�ͬ��
 *  һ�ֱ�����ʼʱ��������һ����
 * @return Action �������������Ĳ���
 *  �뽫�������Ĳ���д�����action�з���
 */


PLAYER_DLL_API Action GetPlayerAction(int MyPlayerID)
{
    Action action;

    return  action;
}