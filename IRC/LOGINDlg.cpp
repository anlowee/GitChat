// LOGINDlg.cpp : implementation file
//

#include "stdafx.h"
#include "IRC.h"
#include "LOGINDlg.h"
#include "afxdialogex.h"


// CLOGINDlg dialog

IMPLEMENT_DYNAMIC(CLOGINDlg, CDialogEx)

CLOGINDlg::CLOGINDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_LOGIN, pParent)
{
#ifndef _WIN32_WCE
	EnableActiveAccessibility();
#endif

}

CLOGINDlg::~CLOGINDlg()
{
}

void CLOGINDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CLOGINDlg, CDialogEx)
	ON_BN_CLICKED(IDC_GETIN, &CLOGINDlg::OnBnClickedGetin)
END_MESSAGE_MAP()


// CLOGINDlg message handlers


void CLOGINDlg::OnBnClickedGetin()
{
	// Get what user inputs
	CString strUsername, strUsercode;
	GetDlgItemText(IDC_USERNAME, strUsername);
	GetDlgItemText(IDC_USERCODE, strUsercode);

	//Compare with user's data
	/*
	*
	*
	*/
}
