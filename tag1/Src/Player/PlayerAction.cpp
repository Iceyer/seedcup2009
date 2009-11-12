#include "PlayerAction.hpp"
#include "MapStatus.hpp"

/*!
 * TO-DO :使用你的队伍名称代替 “简单电脑”
*/
std::string strTeamName = "简单电脑";

PLAYER_DLL_API const char* GetPlayerName()
{
    return strTeamName.c_str();
}

/*!
 * @brief 获得参赛者下一步操作的回调函数
 * @prama MyPlayerID intger 
 *  MyPlayerID是你当前的选手编号
 *  当MyPlayerID = 2 表示你是参赛者一
 *  当MyPlayerID = 3 表示你是参赛者二
 *  在一局比赛中，选手编号不会改变，但不同局比赛中可能不同，
 *  一局比赛开始时，参赛者一先手
 * @return Action 参赛者所决定的操作
 *  请将所决定的操作写入变量action中返回
 */


PLAYER_DLL_API Action GetPlayerAction(int MyPlayerID)
{
    Action action;

    return  action;
}