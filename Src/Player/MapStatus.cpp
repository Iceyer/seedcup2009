#include "MapStatus.hpp"

Hexxagon::MapMgr    *gpCurMapMgr;

PLAYER_DLL_API void SetMapMgr(Hexxagon::MapMgr* pMapMgr)
{
    gpCurMapMgr = pMapMgr;
}

PLAYER_DLL_API int GetMapWidth()
{
    return  gpCurMapMgr->MapWidth();
}

PLAYER_DLL_API int GetMapHeight()
{
    return  gpCurMapMgr->MapHeigth();
}

PLAYER_DLL_API int GetMapStatus(int x, int y)
{
    return  gpCurMapMgr->GetMapStatus(x, y).m_Type;
}