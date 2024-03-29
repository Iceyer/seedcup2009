#include <fstream>
#include "Map.hpp"

using namespace Hexxagon;

MapItem Invalid;

//Invalid.m_Type = MapItem::INVALID;

Map::Map()
{
}

Map::~Map()
{
    if (m_pData)
    {
        delete[] m_pData;
        m_pData = NULL;
    }
    if (m_pOrgData)
    {
        delete[] m_pOrgData;
        m_pOrgData = NULL;
    }
}

int Map::MapWidth() const
{
    return m_iMapWidth;
}

int Map::MapHeigth() const
{
    return m_iMapHeight;
}

const std::string& Map::MapFilePath() const
{
    return m_strMapFileName;
}

const MapItem& Map::GetMapStatus(const int x, const int y) const
{
    if(x < 0 || x > m_iMapWidth || y < 0 || y > m_iMapHeight)
    {
        return Invalid;
    }
    return m_pData[x + y * m_iMapHeight];
}

bool Map::CheckEmptyAround(const int x, const int y) const
{
    //Not work now
    bool ret = true;
    x,y;
//     if (x - 1 > 0)
//     {
//         ret |= m_pData[x - 1 + y * m_iMapHeight].m_Type == MapItem::EMPTY;
//     }
    return ret;
}


bool Map::UpdateMap(const Action& action, int FailorInorOut)
{
    //将目标位置的状态设置为与起始位置状态一样
    m_pData[action.DesPosX + action.DesPosY * m_iMapHeight].m_Type = \
        m_pData[action.PiecePosX + action.PiecePosY * m_iMapHeight].m_Type;

    if (FailorInorOut == 2)
    {
        m_pData[action.PiecePosX + action.PiecePosY * m_iMapHeight].m_Type = MapItem::EMPTY;
    }

    MapItem::ItemType myType = m_pData[action.DesPosX + action.DesPosY * m_iMapHeight].m_Type;
    MapItem::ItemType enemyType = myType == MapItem::PLayer1 ? MapItem::PLayer2 : MapItem::PLayer1;
    if (   action.DesPosX+1 < m_iMapWidth
        && m_pData[action.DesPosX+1 + action.DesPosY * m_iMapHeight].m_Type == enemyType)
    {//right
        m_pData[action.DesPosX+1 + action.DesPosY * m_iMapHeight].m_Type = myType;
    }
    if (   action.DesPosX+1 < m_iMapWidth
        && action.DesPosY+1 <m_iMapHeight
        && m_pData[action.DesPosX+1 + (action.DesPosY+1) * m_iMapHeight].m_Type == enemyType)
    {//right down
        m_pData[action.DesPosX+1 + (action.DesPosY+1) * m_iMapHeight].m_Type = myType;
    }
    if (   action.DesPosY+1 <m_iMapHeight
        && m_pData[action.DesPosX + (action.DesPosY+1) * m_iMapHeight].m_Type == enemyType)
    {//down
        m_pData[action.DesPosX + (action.DesPosY+1) * m_iMapHeight].m_Type = myType;
    }
    if (   action.DesPosX-1 >= 0
        && m_pData[(action.DesPosX-1) + action.DesPosY * m_iMapHeight].m_Type == enemyType)
    {//left
        m_pData[(action.DesPosX-1) + action.DesPosY * m_iMapHeight].m_Type = myType;
    }
    if (   action.DesPosY-1 >= 0
        && m_pData[action.DesPosX + (action.DesPosY-1) * m_iMapHeight].m_Type == enemyType)
    {//up
        m_pData[action.DesPosX + (action.DesPosY-1) * m_iMapHeight].m_Type = myType;
    }
    if (   action.DesPosX-1 >= 0
        && action.DesPosY-1 >= 0
        && m_pData[(action.DesPosX-1) + (action.DesPosY-1) * m_iMapHeight].m_Type == enemyType)
    {//left up
        m_pData[(action.DesPosX-1) + (action.DesPosY-1) * m_iMapHeight].m_Type = myType;
    }
    return true;
}

bool Map::LoadMap(std::string strMapFileName)
{
    using std::ifstream;
    ifstream    MapFile;
    MapFile.open(strMapFileName.c_str(), std::ios::in);
    if (!MapFile.is_open())
    {
        return false;
    }
    m_strMapFileName = strMapFileName;
    MapFile>>m_iMapWidth;
    MapFile>>m_iMapHeight;

    m_pData = new MapItem[m_iMapWidth * m_iMapHeight];

    m_pOrgData = new MapItem[m_iMapWidth * m_iMapHeight];

    int ntemp;
    for (int i = 0; i < m_iMapHeight; ++i)
    {
        for (int j = 0; j < m_iMapWidth; ++j)
        {
            MapFile>>ntemp;
            m_pOrgData[i * m_iMapHeight + j].m_Type = static_cast<MapItem::ItemType>(ntemp);
        }
    }
    MapFile.close();
    ReLoadMap();
    return true;
}

void Map::ReLoadMap()
{
    memcpy_s(m_pData, m_iMapWidth * m_iMapHeight * sizeof(MapItem),
             m_pOrgData, m_iMapWidth * m_iMapHeight * sizeof(MapItem));
}

MapMgr::MapMgr()
{

}

MapMgr::~MapMgr()
{
    MapList::iterator   itor = m_MapList.begin();
    for (; itor != m_MapList.end(); ++itor)
    {
        delete *itor;
    }
}

MapMgr::MapItor MapMgr::Begin()
{
    return m_MapList.begin();
}

MapMgr::MapItor MapMgr::End()
{
    return  m_MapList.end();
}

int MapMgr::MapCnt() const
{
    return m_MapList.size();
}

Map* MapMgr::AddMap(std::string strMapFileName)
{
    Map* pNewMap = new Map;
    if(!pNewMap->LoadMap(strMapFileName))
    {
        return NULL;
    }
    m_MapList.push_back(pNewMap);
    return pNewMap;
}