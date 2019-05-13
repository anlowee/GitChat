#pragma once

#include "IRCClient/IRCClient.h"

#include "CHATDlg.h"
#include <algorithm>

class MyGlobalData
{
public:
	MyGlobalData();
	~MyGlobalData();

	static CString g_strUsername;
	static IRCClient aIRCClient;
	static CCHATDlg newChatDlg;

	static std::string NowChannel;


	void static msgCommand(std::string arguments, IRCClient* client);
	void static joinCommand(std::string channel, IRCClient* client);
	void static partCommand(std::string channel, IRCClient* client);
	void static ctcpCommand(std::string arguments, IRCClient* client);

	bool static StringToWString(const std::string& str, std::wstring& wstr);
	bool static WStringToString(const std::wstring& wstr, std::string& str);
};