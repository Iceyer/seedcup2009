#include "stdafx.h"

#include "SenceRender.hpp"
#include "../GameCore/Map.hpp"
#include "../GameCore/Game.hpp"

const double gdCos30 = 0.86602540378443864676372317075294;
const double HexgaonSize = 20;
const double HexgaonSizeB = HexgaonSize * gdCos30;

Render Render::m_Render;

Render::Render()
{
}

Render::~Render()
{

}

void Render::SetDC(CDC *pdc)
{
    m_pDC = pdc;
}

void Render::SetSenceSize(int width, int height)
{
    m_Width = width;
    m_Height = height;
}

void Render::RenderSence()
{
    using namespace Hexxagon;
    CPen RedPen(PS_SOLID, 1, gColorRed);
    CPen* pOldPen = m_pDC->SelectObject(&RedPen);

    /*Draw Game Information*/
    m_pDC->MoveTo(200,0);
    m_pDC->LineTo(200, m_Height);

    /*Draw Map*/

    /*Calc The Start Point*/
    /*The background center is (500, 300)*/
    int     iMapWidth = Game::HexxagonGame().m_MapMgr.MapWidth();
    int     iMapHeight = Game::HexxagonGame().m_MapMgr.MapHeigth();
    
    DrawHexagon(500, 300, 10);

    int     iStartX = 500 - (iMapWidth - 1) * HexgaonSizeB + (iMapHeight - 1 ) * HexgaonSizeB / 2;
    int     iStartY = 300 + (iMapHeight - 1) * 3 * HexgaonSize / 4;

    int     iItemX;
    int     iItemY;
    for (int i =0; i < iMapWidth; ++i)
    {
        for (int j = 0; j < iMapHeight; ++j)
        {
            MapItem curItem = Game::HexxagonGame().m_MapMgr.GetMapStatus(i, j);
            iItemX  = iStartX + 2 * i * HexgaonSizeB - j * HexgaonSizeB;
            iItemY  = iStartY - 3 * j * HexgaonSize / 2;
            DrawHexagon(iItemX, iItemY, HexgaonSize);
        }
    }

/*
    for (int i = 0; i < 16; i += 2)
    {
        for (int j = 0; j < 12; ++j)
        {
            DrawHexagon(300 + 20 * gdCos30 * 2 * j, 50 + 30 * i, 20);
        }
    }

    for (int i = 1; i < 16; i += 2)
    {
        for (int j = 0; j < 12; ++j)
        {
            DrawHexagon(300 + 20 * gdCos30 + 20 * gdCos30 * 2 * j, 50 + 30 * i, 20);
        }
    }*/


    m_pDC->SelectObject(pOldPen);
}

void Render::DrawHexagon(int cx, int cy, int edgelength, double arc /*= 0*/)
{
    m_pDC->MoveTo(cx, cy + edgelength);
    m_pDC->LineTo(cx + edgelength * gdCos30, cy + edgelength / 2);
    m_pDC->LineTo(cx + edgelength * gdCos30, cy - edgelength / 2);
    m_pDC->LineTo(cx , cy - edgelength);
    m_pDC->LineTo(cx - edgelength * gdCos30, cy - edgelength / 2);
    m_pDC->LineTo(cx - edgelength * gdCos30, cy + edgelength / 2);
    m_pDC->LineTo(cx , cy + edgelength);
}
