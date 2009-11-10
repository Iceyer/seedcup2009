#include "MapStatus.hpp"

Hexxagon::Map    *gpCurMap;
Hexxagon::Player *gpPlayer;

PLAYER_DLL_API void SetMap(Hexxagon::Map* pMap)
{
    gpCurMap = pMap;
}

PLAYER_DLL_API void SetPlayer(Hexxagon::Player* pPlayer)
{
    gpPlayer = pPlayer;
}


/*以下为可以使用的API*/

int GetMapWidth()
{
    return  gpCurMap->MapWidth();
}

int GetMapHeight()
{
    return  gpCurMap->MapHeigth();
}

/*
**输入：x、y表示地图上的x、y 坐标
**返回值：0 表示坐标无效
**        1 表示该坐标为空，可以放置棋子
**        2 表示该坐标已被选手一的棋子占据
**        3 表示该坐标已被选手二的棋子占据
*/
int GetMapStatus(int x, int y)
{
    return  gpCurMap->GetMapStatus(x, y).m_Type;
}
