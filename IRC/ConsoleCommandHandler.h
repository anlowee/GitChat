#pragma once
#include <string.h>
#include <algorithm>
#include <map>
#include "IRCCLient\IRCClient.h"

class ConsoleCommandHandler
{
public:
	ConsoleCommandHandler();
	~ConsoleCommandHandler();
	bool AddCommand(std::string name, int argCount, void (*handler)(std::string /*params*/, IRCClient* /*client*/));
	void ParseCommand(std::string command, IRCClient* client);

private:
	struct CommandEntry
	{
		int argCount;
		void (*handler)(std::string /*arguments*/, IRCClient* /*client*/);
	};

	std::map<std::string, CommandEntry> _commands;
};

