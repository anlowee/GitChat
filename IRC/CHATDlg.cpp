// CHATDlg.cpp : implementation file
//

#include "stdafx.h"
#include "IRC.h"
#include "CHATDlg.h"
#include "LOGINDlg.h"
#include "MyGlobalData.h"
#include "afxdialogex.h"
#include <map>
#include <algorithm>
// CCHATDlg dialog


class ConsoleCommandHandler
{
public:
	bool AddCommand(std::string name, int argCount, void (*handler)(std::string /*params*/, IRCClient* /*client*/))
	{
		CommandEntry entry;
		entry.argCount = argCount;
		entry.handler = handler;
		std::transform(name.begin(), name.end(), name.begin(), towlower);
		_commands.insert(std::pair<std::string, CommandEntry>(name, entry));
		return true;
	}

	void ParseCommand(std::string command, IRCClient* client)
	{
		if (_commands.empty())
		{
			std::cout << "No commands available." << std::endl;
			return;
		}

		if (command[0] == '/')
			command = command.substr(1); // Remove the slash

		std::string name = command.substr(0, command.find(" "));
		std::string args = command.substr(command.find(" ") + 1);
		int argCount = std::count(args.begin(), args.end(), ' ');

		std::transform(name.begin(), name.end(), name.begin(), towlower);

		std::map<std::string, CommandEntry>::const_iterator itr = _commands.find(name);
		if (itr == _commands.end())
		{
			std::cout << "Command not found." << std::endl;
			return;
		}

		if (++argCount < itr->second.argCount)
		{
			std::cout << "Insuficient arguments." << std::endl;
			return;
		}

		(*(itr->second.handler))(args, client);
	}

private:
	struct CommandEntry
	{
		int argCount;
		void (*handler)(std::string /*arguments*/, IRCClient* /*client*/);
	};

	std::map<std::string, CommandEntry> _commands;
};

ConsoleCommandHandler commandHandler;

void msgCommand(std::string arguments, IRCClient* client)
{
	std::string to = arguments.substr(0, arguments.find(" "));
	std::string text = arguments.substr(arguments.find(" ") + 1);

	std::cout << "To " + to + ": " + text << std::endl;
	client->SendIRC("PRIVMSG " + to + " :" + text);
};

void joinCommand(std::string channel, IRCClient * client)
{
	MyGlobalData::NowChannel = channel;

	if (channel[0] != '#')
		channel = "#" + channel;

	client->SendIRC("JOIN " + channel);
}

void partCommand(std::string channel, IRCClient * client)
{
	if (channel[0] != '#')
		channel = "#" + channel;

	client->SendIRC("PART " + channel);
}

void ctcpCommand(std::string arguments, IRCClient * client)
{
	std::string to = arguments.substr(0, arguments.find(" "));
	std::string text = arguments.substr(arguments.find(" ") + 1);

	std::transform(text.begin(), text.end(), text.begin(), towupper);

	client->SendIRC("PRIVMSG " + to + " :\001" + text + "\001");
}





IMPLEMENT_DYNAMIC(CCHATDlg, CDialogEx)

CCHATDlg::CCHATDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_CHAT, pParent)
{
#ifndef _WIN32_WCE
	EnableActiveAccessibility();
#endif

	commandHandler.AddCommand("msg", 2, &msgCommand);
	commandHandler.AddCommand("join", 1, &joinCommand);
	commandHandler.AddCommand("part", 1, &partCommand);
	commandHandler.AddCommand("ctcp", 2, &ctcpCommand);
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


	std::string command = T2A(strMessageInput);

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
	CString rs = this->AddRecord(CString(strUsername.c_str()), CString(strMessageInput.c_str())); USES_CONVERSION;
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
