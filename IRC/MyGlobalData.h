#pragma once

#include "IRCClient/IRCClient.h"

#include "CHATDlg.h"

class MyGlobalData
{
public:
	MyGlobalData();
	~MyGlobalData();

	static CString g_strUsername;
	static IRCClient aIRCClient;
	static CCHATDlg newChatDlg;

	//static CString (CCHATDlg::*CCHATDlg_AddRecord)(CString, CString);
};

