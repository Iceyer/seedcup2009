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


/*����Ϊ����ʹ�õ�API*/

/*!
 * @brief ��õ�ͼ�Ŀ��
 * ��ͼ�����ָ��ͼ��X���ϵĳ���
 * @prama void
 * @return ��ͼ���
 */
int GetMapWidth();

/*!
 * @brief ��õ�ͼ�ĸ߶�
 * �߶���ָ��ͼ��Y����ĳ���
 * @prama void
 * @return ��ͼ�߶�
 */
int GetMapHeight();

/*!
 * @brief ��õ�ͼ������Ϊ(x,y)�ĸ��ӵ�״̬��
 * @prama x intger X���λ������
 * @prama y intger Y���λ������
 * @return intger ���ӵ�״̬
 *  ���ӵ�״̬�����֣��ɷ���ֵ0��1��2��3����ʾ���京�����£�
 *  0 ��ʾ������Ч
 *  1 ��ʾ������Ϊ�գ����Է�������
 *  2 ��ʾ�������ѱ�������һ������ռ��
 *  3 ��ʾ�������ѱ������߶�������ռ��
 */
int GetMapStatus(const int x, const int y);
