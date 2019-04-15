// REGISTERDlg.cpp : implementation file
//

#include "stdafx.h"
#include "IRC.h"
#include "REGISTERDlg.h"
#include "afxdialogex.h"


// CREGISTERDlg dialog

IMPLEMENT_DYNAMIC(CREGISTERDlg, CDialogEx)

CREGISTERDlg::CREGISTERDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_REGISTERUP, pParent)
{
#ifndef _WIN32_WCE
	EnableActiveAccessibility();
#endif

}

CREGISTERDlg::~CREGISTERDlg()
{
}

void CREGISTERDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CREGISTERDlg, CDialogEx)
	ON_BN_CLICKED(IDC_REGISTERNOW, &CREGISTERDlg::OnBnClickedRegisternow)
END_MESSAGE_MAP()


// CREGISTERDlg message handlers


void CREGISTERDlg::OnBnClickedRegisternow()
{
	// Get the register information
	CString strNewUsername, strNewUsercode, strNewUsercode2;
	CString strResponse;
	GetDlgItemText(IDC_NEWUSERNAME, strNewUsername);
	GetDlgItemText(IDC_NEWUSERCODE, strNewUsercode);
	GetDlgItemText(IDC_NEWUSERCODE2, strNewUsercode2);

	//MessageBox(strNewUsercode);
	//MessageBox(strNewUsercode2);
	//Compare code1&code2
	
	//char* pNewUsercode = (char*)((LPCTSTR)strNewUsercode);
	//char* pNewUsercode2 = (char*)((LPCTSTR)strNewUsercode2);
	//if (!strcmp(pNewUsercode, pNewUsercode2))
	if (strNewUsercode == strNewUsercode2)
	{
		strResponse = "Let's chat now!";
		MessageBox(strResponse);
	}
	else
	{
		strResponse = "Ensure your code!";
		MessageBox(strResponse);
	}
}
