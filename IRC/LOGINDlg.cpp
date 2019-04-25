// LOGINDlg.cpp : implementation file
//

#include "stdafx.h"
#include "IRC.h"
#include "Resource.h"
#include "LOGINDlg.h"
#include "CHATDlg.h"
#include "MyGlobalData.h"
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
	CCHATDlg newChatDlg;
	CString strResponse;//Use to Response
	bool bFlag;//Use to judge

	// Get what user inputs
	CString strUsername, strNickname,strUsercode, strServeraddress, strServerport;
	WORD wServerport;

	GetDlgItemText(IDC_USERNAME, strUsername);
	MyGlobalData::g_strUsername = strUsername;
	GetDlgItemText(IDC_NICKNAME, strNickname);
	GetDlgItemText(IDC_USERCODE, strUsercode);
	GetDlgItemText(IDC_SERVERADDRESS, strServeraddress);
	GetDlgItemText(IDC_SERVERPORT, strServerport);
	wServerport = _wtoi(strServerport);
	
	//Compare with user's data
	/*
	*
	*
	*/
	bFlag = true;//Debug Value
	if (bFlag)
	{
		strResponse = "Welcome back!  User-";
		strResponse = strResponse + strUsername;
		MessageBox(strResponse);
		newChatDlg.DoModal();
	}
}
