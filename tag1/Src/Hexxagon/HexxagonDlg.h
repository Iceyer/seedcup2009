// HexxagonDlg.h : ͷ�ļ�
//

#pragma once

#include "resource.h"

// CHexxagonDlg �Ի���
class CHexxagonDlg : public CDialog
{
    // ����
public:
    CHexxagonDlg(CWnd* pParent = NULL);	// ��׼���캯��

    ~CHexxagonDlg();

    // �Ի�������
    enum { IDD = IDD_HEXXAGON_DIALOG };

protected:
    virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��

public:
    /// ���ɵ���Ϣӳ�亯��
    virtual BOOL OnInitDialog();
    afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
    afx_msg void OnPaint();
    afx_msg HCURSOR OnQueryDragIcon();
    afx_msg void OnDestroy();
    afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
    afx_msg BOOL OnEraseBkgnd(CDC* pDC);
    DECLARE_MESSAGE_MAP()

public:
    static CHexxagonDlg *Myself();
    void StartGame();
    void NextMatch();
    void DisableUI();

    /// ʵ��
protected:
    HICON                       m_hIcon;
    static CHexxagonDlg*        m_pSelf;
};
