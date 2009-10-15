#include "stdafx.h"
#include "../../Hexxagon/resource.h"

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
    CPen RedPen(PS_SOLID, 3, gColorRed);
    CPen* pOldPen = m_pDC->SelectObject(&RedPen);

    /*Draw Game Information*/
    m_pDC->MoveTo(198,0);
    m_pDC->LineTo(198, m_Height);

    /*Draw Map*/

    /*Calc The Start Point*/
    /*The background center is (500, 300)*/
    int     iMapWidth = Game::HexxagonGame().m_MapMgr.CurMap()->MapWidth();
    int     iMapHeight = Game::HexxagonGame().m_MapMgr.CurMap()->MapHeigth();
    //int     iStartX = 500 - (iMapWidth - 1) * HexgaonSizeB + (iMapHeight - 1 ) * HexgaonSizeB / 2;
    //int     iStartY = 300 - (iMapHeight - 1) * 3 * HexgaonSize / 4;

    int     iItemX;
    int     iItemY;
    for (int i =0; i < iMapWidth; ++i)
    {
        for (int j = 0; j < iMapHeight; ++j)
        {
            MapItem curItem = Game::HexxagonGame().m_MapMgr.CurMap()->GetMapStatus(i, j);
            iItemX  = 200 + i*36;
            iItemY  = i%2*15 + j*30;
            switch (curItem.m_Type)
            {
            case MapItem::INVALID:
                break;
            case MapItem::EMPTY:
                DrawHexagon(iItemX,iItemY);//,0,curItem.m_Type);
                //DrawHexagon(iItemX, iItemY, 0);
                break;
            case MapItem::PLayer1:
                //DrawHexagon(iItemX, iItemY, HexgaonSize);
                //DrawPlayer1(iItemX, iItemY, HexgaonSizeB / 2);
                break;
            case MapItem::PLayer2:
                //DrawHexagon(iItemX, iItemY, HexgaonSize);
                //DrawPlayer2(iItemX, iItemY, HexgaonSizeB / 2);
                break;
            default:
                break;
            }
        }
    }

    /*Draw the center point*/
    //DrawHexagon(500, 300, 10);
    m_pDC->SelectObject(pOldPen);
}

void Render::DrawHexagon(int cx, int cy)//, int edgelength, MapItem::ItemType itype /*= MapItem::ItemType::EMPTY*/)
{
    CBitmap hole1,hole2;
    if (!(hole1.LoadBitmap(IDB_BITMAP1)&&hole2.LoadBitmap(IDB_BITMAP2)))
    {
        if (MessageBox(NULL,"无法找到需要加载的位图","加载位图失败",MB_OK) == IDOK)
        {
            return;
        }
    }

    CDC cdctemp;
    cdctemp.CreateCompatibleDC(NULL);
    cdctemp.SelectObject(&hole2);
    m_pDC->BitBlt(cx,cy,50,30,&cdctemp,0,0,SRCPAINT);

    cdctemp.SelectObject(&hole1);
    m_pDC->BitBlt(cx,cy,50,30,&cdctemp,0,0,SRCAND);
    cdctemp.DeleteDC();
    //m_pDC->BeginPath();
    //m_pDC->MoveTo(cx, cy + edgelength);
    //m_pDC->LineTo(cx + edgelength * gdCos30, cy + edgelength / 2);
    //m_pDC->LineTo(cx + edgelength * gdCos30, cy - edgelength / 2);
    //m_pDC->LineTo(cx , cy - edgelength);
    //m_pDC->LineTo(cx - edgelength * gdCos30, cy - edgelength / 2);
    //m_pDC->LineTo(cx - edgelength * gdCos30, cy + edgelength / 2);
    //m_pDC->LineTo(cx , cy + edgelength);
    //m_pDC->EndPath();
    //CRgn rgn;
    //rgn.CreateFromPath(m_pDC);
    //m_pDC->InvertRgn(&rgn);

    //CBrush  EmptyItemBrush(gColorGreen);
    //m_pDC->FillRgn(&rgn, &EmptyItemBrush);

    //m_pDC->MoveTo(cx, cy + edgelength);
    //m_pDC->LineTo(cx + edgelength * gdCos30, cy + edgelength / 2);
    //m_pDC->LineTo(cx + edgelength * gdCos30, cy - edgelength / 2);
    //m_pDC->LineTo(cx , cy - edgelength);
    //m_pDC->LineTo(cx - edgelength * gdCos30, cy - edgelength / 2);
    //m_pDC->LineTo(cx - edgelength * gdCos30, cy + edgelength / 2);
    //m_pDC->LineTo(cx , cy + edgelength);
}

void Render::DrawPlayer1(int cx, int cy, int edgelength)
{
    CBrush  Brush(gColorBlue);
    CBrush* pOldBrush = m_pDC->SelectObject(&Brush);
    m_pDC->Ellipse(cx - edgelength, cy - edgelength, cx + edgelength, cy + edgelength); 
}

void Render::DrawPlayer2(int cx, int cy, int edgelength)
{
    CBrush  Brush(gColorWhite);
    CBrush* pOldBrush = m_pDC->SelectObject(&Brush);
    m_pDC->Ellipse(cx - edgelength, cy - edgelength, cx + edgelength, cy + edgelength); 
}