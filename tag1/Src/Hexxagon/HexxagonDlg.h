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
    afx_msg BOOL OnEraseBkgnd(CDC* pDC);
    afx_msg static CHexxagonDlg *Myself();
    // ʵ��
protected:
    HICON m_hIcon;
    CRITICAL_SECTION    m_Critical;
    static CHexxagonDlg *      m_pSelf;

    // ���ɵ���Ϣӳ�亯��
    virtual BOOL OnInitDialog();
    afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
    afx_msg void OnPaint();
    afx_msg HCURSOR OnQueryDragIcon();
    DECLARE_MESSAGE_MAP()

};