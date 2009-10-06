// HexxagonDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Hexxagon.h"
#include "HexxagonDlg.h"
#include ".\SenceRender\SenceRender.hpp"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialog
{
public:
    CAboutDlg();

    // �Ի�������
    enum { IDD = IDD_ABOUTBOX };

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

    // ʵ��
protected:
    DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CHexxagonDlg �Ի���




CHexxagonDlg::CHexxagonDlg(CWnd* pParent /*=NULL*/)
: CDialog(CHexxagonDlg::IDD, pParent)
{
    m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CHexxagonDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CHexxagonDlg, CDialog)
    ON_WM_SYSCOMMAND()
    ON_WM_PAINT()
    ON_WM_QUERYDRAGICON()
    //}}AFX_MSG_MAP
    ON_WM_ERASEBKGND()
END_MESSAGE_MAP()


// CHexxagonDlg ��Ϣ�������

BOOL CHexxagonDlg::OnInitDialog()
{
    CDialog::OnInitDialog();

    // ��������...���˵�����ӵ�ϵͳ�˵��С�

    // IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
    ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
    ASSERT(IDM_ABOUTBOX < 0xF000);

    CMenu* pSysMenu = GetSystemMenu(FALSE);
    if (pSysMenu != NULL)
    {
        CString strAboutMenu;
        strAboutMenu.LoadString(IDS_ABOUTBOX);
        if (!strAboutMenu.IsEmpty())
        {
            pSysMenu->AppendMenu(MF_SEPARATOR);
            pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
        }
    }

    // ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
    //  ִ�д˲���
    SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
    SetIcon(m_hIcon, FALSE);		// ����Сͼ��

    // TODO: �ڴ���Ӷ���ĳ�ʼ������
    SetWindowPos(NULL, 0, 0, 800, 600, SWP_SHOWWINDOW);

    return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CHexxagonDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
    if ((nID & 0xFFF0) == IDM_ABOUTBOX)
    {
        CAboutDlg dlgAbout;
        dlgAbout.DoModal();
    }
    else
    {
        CDialog::OnSysCommand(nID, lParam);
    }
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CHexxagonDlg::OnPaint()
{
    if (IsIconic())
    {
        CPaintDC dc(this); // ���ڻ��Ƶ��豸������

        SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

        // ʹͼ���ڹ����������о���
        int cxIcon = GetSystemMetrics(SM_CXICON);
        int cyIcon = GetSystemMetrics(SM_CYICON);
        CRect rect;
        GetClientRect(&rect);
        int x = (rect.Width() - cxIcon + 1) / 2;
        int y = (rect.Height() - cyIcon + 1) / 2;

        // ����ͼ��
        dc.DrawIcon(x, y, m_hIcon);
    }
    else
    {
        //CDialog::OnPaint();
        //ʹ��˫�����ͼ
        CPaintDC dc(this); // ���ڻ��Ƶ��豸������
        CRect lcrcClient;
        GetClientRect(&lcrcClient);

        CDC MemDC; //���ȶ���һ����ʾ�豸����
        CBitmap MemBitmap;//����һ��λͼ����
        MemDC.CreateCompatibleDC(NULL);
        MemBitmap.CreateCompatibleBitmap(&dc,lcrcClient.Width(),lcrcClient.Height());
        CBitmap *pOldBit=MemDC.SelectObject(&MemBitmap);

        MemDC.SetBkColor(gBackGroundColor);
        MemDC.SetBkMode(TRANSPARENT);

        CBrush lcBKBrush(gBackGroundColor);
        MemDC.FillRect(&lcrcClient, &lcBKBrush);

        //���浱ǰ����
        CPen lcPen(PS_SOLID, 1, gColorGreen);
        CPen *lcpOldPen = MemDC.SelectObject(&lcPen);

        Render::SRender().SetDC(&MemDC);
        Render::SRender().SetSenceSize(lcrcClient.Width(), lcrcClient.Height());

        Render::SRender().RenderSence();

        MemDC.SelectObject(lcpOldPen);

        dc.BitBlt(lcrcClient.left, lcrcClient.top, 
            lcrcClient.Width(), lcrcClient.Height(), 
            &MemDC, lcrcClient.left, lcrcClient.top, SRCCOPY);

        //��ͼ��ɺ������
        MemBitmap.DeleteObject();
        MemDC.DeleteDC();
    }
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CHexxagonDlg::OnQueryDragIcon()
{
    return static_cast<HCURSOR>(m_hIcon);
}


BOOL CHexxagonDlg::OnEraseBkgnd(CDC* pDC)
{
    //return CDialog::OnEraseBkgnd(pDC);
    return TRUE;
}
