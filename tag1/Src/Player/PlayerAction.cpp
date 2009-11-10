#include "PlayerAction.hpp"
#include "MapStatus.hpp"

/*
** TO-DO :使用你的队伍名称代替 “简单电脑”
*/
const   std::string strTeamName = "简单电脑";

PLAYER_DLL_API std::string GetPlayerName()
{
    return strTeamName;
}

/*
** MyPlayerID是你当前的选手编号
** MyPlayerID = 2 表示你是参赛者一，开局时先手
** MyPlayerID = 3 表示你是参赛者二，开局时后手
*/
PLAYER_DLL_API Action GetPlayerAction(int MyPlayerID)
{
    Action action;

    return  action;
}