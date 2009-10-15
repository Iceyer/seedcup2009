#include "MapStatus.hpp"

Hexxagon::Map    *gpCurMap;

PLAYER_DLL_API void SetMap(Hexxagon::Map* pMap)
{
    gpCurMap = pMap;
}

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