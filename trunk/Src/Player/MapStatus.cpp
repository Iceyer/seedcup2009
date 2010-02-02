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

int GetMapStatus(int x, int y)
{
    return  gpCurMap->GetMapStatus(x, y).m_Type;
}
