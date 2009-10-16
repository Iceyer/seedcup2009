#include <fstream>
#include "Map.hpp"

using namespace Hexxagon;

Map::Map()
{
}

Map::~Map()
{
    delete []m_pData;
}

int Map::MapWidth()
{
    return m_iMapWidth;
}

int Map::MapHeigth()
{
    return m_iMapHeight;
}

const MapItem& Map::GetMapStatus(const int x, const int y) const
{
    return m_pData[x * m_iMapWidth + y];
}

bool Map::UpdateMap(const Action& action)
{
    return true;
}

bool Map::LoadMap(std::string strMapFileName)
{
    using std::ifstream;
    ifstream    MapFile;
    MapFile.open(strMapFileName.c_str(), std::ios::in);

    MapFile>>m_iMapWidth;
    MapFile>>m_iMapHeight;

    m_pData = new MapItem[m_iMapWidth * m_iMapHeight];

    for (int i = 0; i < m_iMapWidth; ++i)
    {
        for (int j = 0; j < m_iMapHeight; ++j)
        {
            MapFile>>m_pData[i * m_iMapWidth + j].m_Type;
        }
    }
    MapFile.close();
    return true;
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
Map* MapMgr::CurMap()
{
    return m_pCurMap;
}

void MapMgr::SetCurMap(Map* map)
{
    m_pCurMap = map;
}

Map* MapMgr::AddMap(std::string strMapFileName)
{
    Map* pNewMap = new Map;
    pNewMap->LoadMap(strMapFileName);
    m_MapList.push_back(pNewMap);
    return pNewMap;
}