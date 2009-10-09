#include "stdafx.h"

#include "SenceRender.hpp"

const double gdCos30 = 0.86602540378443864676372317075294;

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
    CPen RedPen(PS_SOLID, 1, gColorRed);
    CPen* pOldPen = m_pDC->SelectObject(&RedPen);

    m_pDC->MoveTo(200,0);
    m_pDC->LineTo(200, m_Height);

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
    }

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
