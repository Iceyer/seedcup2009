#pragma once

#include "PlayerDLLAPI.hpp"
#include "..\GameCore\Map.hpp"
#include "..\GameCore\Player.hpp"

PLAYER_DLL_API void SetMap(Hexxagon::Map* pMap);

typedef void (*pSetMap) (Hexxagon::Map*);

const std::string strSetMapFunc = "SetMap";

PLAYER_DLL_API void SetPlayer(Hexxagon::Player* pPlayer);

typedef void (*pSetPlayer) (Hexxagon::Player*);

const std::string strSetPlayerFunc = "SetPlayer";


/*以下为可以使用的API*/

/*!
 * @brief 获得地图的宽度
 * 地图宽度是指地图在X轴上的长度
 * @prama void
 * @return 地图宽度
 */
int GetMapWidth();

/*!
 * @brief 获得地图的高度
 * 高度是指地图在Y方向的长度
 * @prama void
 * @return 地图高度
 */
int GetMapHeight();

/*!
 * @brief 获得地图上坐标为(x,y)的格子的状态。
 * @prama x intger X轴的位置坐标
 * @prama y intger Y轴的位置坐标
 * @return intger 格子的状态
 *  格子的状态有四种，由返回值0、1、2、3来表示，其含义如下：
 *  0 表示坐标无效
 *  1 表示该坐标为空，可以放置棋子
 *  2 表示该坐标已被参赛者一的棋子占据
 *  3 表示该坐标已被参赛者二的棋子占据
 */
int GetMapStatus(const int x, const int y);
