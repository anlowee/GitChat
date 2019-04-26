#include "stdafx.h"
#include "MyGlobalData.h"


MyGlobalData::MyGlobalData()
{
}


MyGlobalData::~MyGlobalData()
{
}

CString MyGlobalData::g_strUsername = NULL;
IRCClient MyGlobalData::aIRCClient;
CCHATDlg MyGlobalData::newChatDlg;