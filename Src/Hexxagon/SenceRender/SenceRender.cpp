#include "stdafx.h"

#include "SenceRender.hpp"
#include "../../GameCore/Map.hpp"
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
    
    /*Draw the center point*/
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
            switch (curItem.m_Type)
            {
            case MapItem::INVALID:
                break;
            case MapItem::EMPTY:
                DrawHexagon(iItemX, iItemY, HexgaonSize);
                break;
            case MapItem::PLayer1:
                break;
            case MapItem::PLayer2:
                break;
            default:
                break;
            }
        }
    }

    m_pDC->SelectObject(pOldPen);
}

void Render::DrawHexagon(int cx, int cy, int edgelength, double arc /*= 0*/)
{
    m_pDC->BeginPath();
    m_pDC->MoveTo(cx, cy + edgelength);
    m_pDC->LineTo(cx + edgelength * gdCos30, cy + edgelength / 2);
    m_pDC->LineTo(cx + edgelength * gdCos30, cy - edgelength / 2);
    m_pDC->LineTo(cx , cy - edgelength);
    m_pDC->LineTo(cx - edgelength * gdCos30, cy - edgelength / 2);
    m_pDC->LineTo(cx - edgelength * gdCos30, cy + edgelength / 2);
    m_pDC->LineTo(cx , cy + edgelength);
    m_pDC->EndPath();
    CRgn rgn;
    rgn.CreateFromPath(m_pDC);
    m_pDC->InvertRgn(&rgn);

    CBrush  EmptyItemBrush(gColorGreen);
    m_pDC->FillRgn(&rgn, &EmptyItemBrush);

    m_pDC->MoveTo(cx, cy + edgelength);
    m_pDC->LineTo(cx + edgelength * gdCos30, cy + edgelength / 2);
    m_pDC->LineTo(cx + edgelength * gdCos30, cy - edgelength / 2);
    m_pDC->LineTo(cx , cy - edgelength);
    m_pDC->LineTo(cx - edgelength * gdCos30, cy - edgelength / 2);
    m_pDC->LineTo(cx - edgelength * gdCos30, cy + edgelength / 2);
    m_pDC->LineTo(cx , cy + edgelength);
}
