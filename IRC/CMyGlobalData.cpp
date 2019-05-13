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
std::string MyGlobalData::NowChannel = "English";



void MyGlobalData::msgCommand(std::string arguments, IRCClient* client)
{
	std::string to = arguments.substr(0, arguments.find(" "));
	std::string text = arguments.substr(arguments.find(" ") + 1);

	std::cout << "To " + to + ": " + text << std::endl;
	client->SendIRC("PRIVMSG " + to + " :" + text);
};

void MyGlobalData::joinCommand(std::string channel, IRCClient * client)
{
	MyGlobalData::NowChannel = channel;

	if (channel[0] != '#')
		channel = "#" + channel;

	client->SendIRC("JOIN " + channel);
}

void MyGlobalData::partCommand(std::string channel, IRCClient * client)
{
	if (channel[0] != '#')
		channel = "#" + channel;

	client->SendIRC("PART " + channel);
}

void MyGlobalData::ctcpCommand(std::string arguments, IRCClient * client)
{
	std::string to = arguments.substr(0, arguments.find(" "));
	std::string text = arguments.substr(arguments.find(" ") + 1);

	std::transform(text.begin(), text.end(), text.begin(), towupper);

	client->SendIRC("PRIVMSG " + to + " :\001" + text + "\001");
}

bool MyGlobalData::StringToWString(const std::string& str, std::wstring& wstr)
{
    int nLen = (int)str.length();
    wstr.resize(nLen, L' ');

    int nResult = MultiByteToWideChar(CP_UTF8, 0, (LPCSTR)str.data(), nLen, (LPWSTR)wstr.c_str(), nLen);
	
    if (nResult == 0)
    {
        return FALSE;
    }

    return TRUE;
}

bool MyGlobalData::WStringToString(const std::wstring& wstr, std::string& str)
{
	int nLen = (int)wstr.length();
	str.resize(nLen, ' ');

	int nResult = WideCharToMultiByte(CP_UTF8, 0, (LPCWSTR)wstr.c_str(), nLen, (LPSTR)str.c_str(), nLen, NULL, NULL);

	if (nResult == 0)
	{
		return FALSE;
	}

	return TRUE;
}