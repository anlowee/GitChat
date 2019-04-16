// CHATDlg.cpp : implementation file
//

#include "stdafx.h"
#include "IRC.h"
#include "CHATDlg.h"
#include "LOGINDlg.h"
#include "afxdialogex.h"
// CCHATDlg dialog

IMPLEMENT_DYNAMIC(CCHATDlg, CDialogEx)

CCHATDlg::CCHATDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_CHAT, pParent)
{
#ifndef _WIN32_WCE
	EnableActiveAccessibility();
#endif

}

CCHATDlg::~CCHATDlg()
{
}

void CCHATDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CCHATDlg, CDialogEx)
	ON_BN_CLICKED(IDC_SEND, &CCHATDlg::OnBnClickedSend)
END_MESSAGE_MAP()


// CCHATDlg message handlers


void CCHATDlg::OnBnClickedSend()
{
	static CString strMessageOutput = NULL;
	CString strMessageInput, strCurrentTime;
	CString strEnterBack;
	CTime ctCurrentTime;

	strEnterBack = "\r\n";
	GetDlgItemText(IDC_MESSAGEEDIT, strMessageInput);
	ctCurrentTime.CTime::GetCurrentTime();
	UpdateData(FALSE);
	strCurrentTime = ctCurrentTime.Format("%Y-%m-%d %H:%M:%S");
	/*
	*Before time, there should be Username added in strMessageOutput
	*/
	strMessageOutput = strMessageOutput + strCurrentTime + strEnterBack + strMessageInput;
	strMessageOutput = strMessageOutput + strEnterBack + strEnterBack;

	SetDlgItemText(IDC_MESSAGELOG, strMessageOutput);
}

