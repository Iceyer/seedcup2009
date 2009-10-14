#include <fstream>
#include "Map.hpp"

using namespace Hexxagon;

MapMgr::MapMgr()
{

}

MapMgr::~MapMgr()
{

}

int MapMgr::MapWidth()
{
    return m_iMapWidth;
}

int MapMgr::MapHeigth()
{
    return m_iMapHeight;
}

const MapItem& MapMgr::GetMapStatus(const int x, const int y) const
{
    return MapStatus[x][y];
}

bool MapMgr::UpdateMap(const Action& action)
{
    return true;
}

bool MapMgr::LoadMap(std::string strMapFileName)
{
    using std::ifstream;
    ifstream    MapFile;
    MapFile.open(strMapFileName.c_str(), std::ios::in);

    MapFile>>m_iMapWidth;
    MapFile>>m_iMapHeight;

    for (int i = 0; i < m_iMapWidth; ++i)
    {
        for (int j = 0; j < m_iMapHeight; ++j)
        {
            MapFile>>MapStatus[i][j].m_Type;
        }
    }
    return true;
}