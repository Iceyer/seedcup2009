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


/*����Ϊ����ʹ�õ�API*/

int GetMapWidth()
{
    return  gpCurMap->MapWidth();
}

int GetMapHeight()
{
    return  gpCurMap->MapHeigth();
}

/*
**���룺x��y��ʾ��ͼ�ϵ�x��y ����
**����ֵ��0 ��ʾ������Ч
**        1 ��ʾ������Ϊ�գ����Է�������
**        2 ��ʾ�������ѱ�ѡ��һ������ռ��
**        3 ��ʾ�������ѱ�ѡ�ֶ�������ռ��
*/
int GetMapStatus(int x, int y)
{
    return  gpCurMap->GetMapStatus(x, y).m_Type;
}
