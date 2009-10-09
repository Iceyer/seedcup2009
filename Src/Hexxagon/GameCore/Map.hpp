#pragma once

#include <vector>

namespace Hexxagon
{
    const unsigned int MaxMapLength = 100;
    class MapItem
    {
        enum ItemType
        {
            EMPTY,
            PLAYER,
            INVALID,
        };
        ItemType m_Type;
        unsigned int X;
        unsigned int Y;
    };

    class MapMgr
    {
        typedef std::vector<MapItem>    MapItemList;

    public:

    private:
        unsigned int MapStatus[MaxMapLength][MaxMapLength];
    };
}