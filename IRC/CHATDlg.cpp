// CHATDlg.cpp : implementation file
//

#include "stdafx.h"
#include "IRC.h"
#include "CHATDlg.h"
#include "LOGINDlg.h"
#include "MyGlobalData.h"
#include "afxdialogex.h"
#include "ConsoleCommandHandler.h"

// CCHATDlg dialog

ConsoleCommandHandler commandHandler;

IMPLEMENT_DYNAMIC(CCHATDlg, CDialogEx)

CCHATDlg::CCHATDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_CHAT, pParent)
{
#ifndef _WIN32_WCE
	EnableActiveAccessibility();
#endif

	commandHandler.AddCommand("msg", 2, &MyGlobalData::msgCommand);
	commandHandler.AddCommand("join", 1, &MyGlobalData::joinCommand);
	commandHandler.AddCommand("part", 1, &MyGlobalData::partCommand);
	commandHandler.AddCommand("ctcp", 2, &MyGlobalData::ctcpCommand);
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
	CString strMessageInput; USES_CONVERSION;
	CString strUsername;

	strUsername = MyGlobalData::g_strUsername;
	GetDlgItemText(IDC_MESSAGEEDIT, strMessageInput);
	UpdateData(FALSE);

	/*
	*Before time, there should be Username added in strMessageOutput
	*/


	//strMessageInput


	std::wstring raw = strMessageInput;
	std::string command;

	MyGlobalData::WStringToString(raw, command);

	if (command == "") { return; };

	if (command[0] == '/') {
		commandHandler.ParseCommand(command, &MyGlobalData::aIRCClient);
	}
	else
	{
		command = "/MSG #" + MyGlobalData::NowChannel + " " + command;
		commandHandler.ParseCommand(command, &MyGlobalData::aIRCClient);

		//MyGlobalData::aIRCClient.SendIRC(command);
	};

	strMessageInput = AddRecord(strUsername, strMessageInput);
	IndicateRecord(strMessageInput);
}


// Record process


//Using do process the record

CString CCHATDlg::AddRecord(CString strUsername, CString strMessageInput)
{
	// TODO: Add your implementation code here.
	CString strMessageOutput;
	CString strEnterBack = _T("\r\n");
	CTime ctCurrentTime = CTime ::GetCurrentTime();
	CString strCurrentTime = ctCurrentTime.Format("%Y-%m-%d %H:%M:%S");
	
	strMessageOutput = strCurrentTime + " " + strUsername + " says: " + strEnterBack + strMessageInput;
	strMessageOutput = strMessageOutput + strEnterBack + strEnterBack;

	return strMessageOutput;
}


std::string CCHATDlg::AddRecord(std::string strUsername, std::string strMessageInput)
{
	std::wstring wstrUsername;
	std::wstring wstrMessageInput;
	MyGlobalData::StringToWString(strUsername, wstrUsername);
	MyGlobalData::StringToWString(strMessageInput, wstrMessageInput);

	CString rs = this->AddRecord(CString(wstrUsername.c_str()), CString(wstrMessageInput.c_str())); USES_CONVERSION;
	IndicateRecord(rs);
	return T2A(rs);
}


// Using to indicate new records
void CCHATDlg::IndicateRecord(CString strMessageInput)
{
	// TODO: Add your implementation code here.
	static CString strMessageOutput = NULL;

	strMessageOutput = strMessageOutput + strMessageInput;

	SetDlgItemText(IDC_MESSAGELOG, strMessageOutput);
	this->SendDlgItemMessage(IDC_MESSAGELOG, WM_VSCROLL, SB_BOTTOM, 0);
}
