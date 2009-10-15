//Header file for render sence
#pragma once

const COLORREF gColorRed    = RGB(255, 0, 0);
const COLORREF gColorGreen  = RGB(0, 255, 0);
const COLORREF gColorBlue   = RGB(0, 0, 255);
const COLORREF gColorYellow = RGB(255, 255, 0);
const COLORREF gColorWhite  = RGB(255, 255, 255);
const COLORREF gColorBlack  = RGB(0, 0, 0);

const COLORREF gBackGroundColor = gColorBlack;

class CDC;

class Render
{
public:
    ~Render();

public:
    static Render& SRender()
    {
        return m_Render;
    }

    void SetDC(CDC *pdc);

    void Render::SetSenceSize(int x, int y);

    void RenderSence();

    void DrawHexagon(int cx, int cy);//, int edgelength, MapItem::ItemType itype = MapItem::ItemType::EMPTY);

    void Render::DrawPlayer1(int cx, int cy, int edgelength);
    
    void Render::DrawPlayer2(int cx, int cy, int edgelength);


private:
    Render();

    static Render m_Render;

    CDC     *m_pDC;
    int     m_Width;
    int     m_Height;
};