/*
 * Copyright (C) 2011 Fredi Machado <https://github.com/fredimachado>
 * IRCClient is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 3.0 of the License, or any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * http://www.gnu.org/licenses/lgpl.html 
 */

#include "stdafx.h"

#include "IRCHandler.h"

#include "../MyGlobalData.h"

#include "../CHATDlg.h"

IRCCommandHandler ircCommandTable[NUM_IRC_CMDS] =
{
    { "PRIVMSG",            &IRCClient::HandlePrivMsg                   },
    { "NOTICE",             &IRCClient::HandleNotice                    },
    { "JOIN",               &IRCClient::HandleChannelJoinPart           },
    { "PART",               &IRCClient::HandleChannelJoinPart           },
    { "NICK",               &IRCClient::HandleUserNickChange            },
    { "QUIT",               &IRCClient::HandleUserQuit                  },
    { "353",                &IRCClient::HandleChannelNamesList          },
    { "433",                &IRCClient::HandleNicknameInUse             },
    { "001",                &IRCClient::HandleServerMessage             },
    { "002",                &IRCClient::HandleServerMessage             },
    { "003",                &IRCClient::HandleServerMessage             },
    { "004",                &IRCClient::HandleServerMessage             },
    { "005",                &IRCClient::HandleServerMessage             },
    { "250",                &IRCClient::HandleServerMessage             },
    { "251",                &IRCClient::HandleServerMessage             },
    { "252",                &IRCClient::HandleServerMessage             },
    { "253",                &IRCClient::HandleServerMessage             },
    { "254",                &IRCClient::HandleServerMessage             },
    { "255",                &IRCClient::HandleServerMessage             },
    { "265",                &IRCClient::HandleServerMessage             },
    { "266",                &IRCClient::HandleServerMessage             },
    { "366",                &IRCClient::HandleServerMessage             },
    { "372",                &IRCClient::HandleServerMessage             },
    { "375",                &IRCClient::HandleServerMessage             },
    { "376",                &IRCClient::HandleServerMessage             },
    { "439",                &IRCClient::HandleServerMessage             },
};

void IRCClient::HandleCTCP(IRCMessage message)
{
    std::string to = message.parameters.at(0);
    std::string text = message.parameters.at(message.parameters.size() - 1);

    // Remove '\001' from start/end of the string
    text = text.substr(1, text.size() - 2);

    //std::cout << "[" + message.prefix.nick << " requested CTCP " << text << "]" << std::endl;
	MyGlobalData::newChatDlg.AddRecord(message.prefix.nick, text);

    if (to == _nick)
    {
        if (text == "VERSION") // Respond to CTCP VERSION
        {
            SendIRC("NOTICE " + message.prefix.nick + " :\001VERSION Open source IRC client by Fredi Machado - https://github.com/fredimachado/IRCClient \001");
            return;
        }

        // CTCP not implemented
        SendIRC("NOTICE " + message.prefix.nick + " :\001ERRMSG " + text + " :Not implemented\001");
    }
}

void IRCClient::HandlePrivMsg(IRCMessage message)
{
    std::string to = message.parameters.at(0);
    std::string text = message.parameters.at(message.parameters.size() - 1);

    // Handle Client-To-Client Protocol
    if (text[0] == '\001')
    {
        HandleCTCP(message);
        return;
    }

    if (to[0] == '#')
	{
		std::string strUsername = "From " + message.prefix.nick + " @" + to + ": ";
		std::string strMessageInput = text + "\n";
		MyGlobalData::newChatDlg.AddRecord(strUsername, strMessageInput);
	}

        //std::cout << "From " + message.prefix.nick << " @ " + to + ": " << text << std::endl;
	else
	{
		std::string strUsername = "From " + message.prefix.nick + ": ";
		std::string strMessageInput = text + "\n";
		MyGlobalData::newChatDlg.AddRecord(strUsername, strMessageInput);
	}
        //std::cout << "From " + message.prefix.nick << ": " << text << std::endl;
}

void IRCClient::HandleNotice(IRCMessage message)
{
    std::string from = message.prefix.nick != "" ? message.prefix.nick : message.prefix.prefix;
    std::string text;

    if( !message.parameters.empty() )
        text = message.parameters.at(message.parameters.size() - 1);

    if (!text.empty() && text[0] == '\001')
    {
        text = text.substr(1, text.size() - 2);
        if (text.find(" ") == std::string::npos)
        {
			std::string tempMessage = "[Invalid " + text + "reply from " + from + "]" + "\n";
			MyGlobalData::newChatDlg.AddRecord("Server ", tempMessage);
			//std::cout << "[Invalid " << text << " reply from " << from << "]" << std::endl;
            return;
        }
        std::string ctcp = text.substr(0, text.find(" "));
		std::string tempMessage = "[" + from + " " + ctcp + " reply]: " + text.substr(text.find(" ") + 1) + "\n";
		MyGlobalData::newChatDlg.AddRecord("Server ", tempMessage);
        //std::cout << "[" << from << " " << ctcp << " reply]: " << text.substr(text.find(" ") + 1) << std::endl;
    }
    else
        std::cout << "-" << from << "- " << text << std::endl;
}

void IRCClient::HandleChannelJoinPart(IRCMessage message)
{
    std::string channel = message.parameters.at(0);
    std::string action = message.command == "JOIN" ? "joins" : "leaves";
	std::string tempMessage = message.prefix.nick + " " + action + " " + channel + "\n";
	MyGlobalData::newChatDlg.AddRecord("Server ", tempMessage);
    //std::cout << message.prefix.nick << " " << action << " " << channel << std::endl;
}

void IRCClient::HandleUserNickChange(IRCMessage message)
{
    std::string newNick = message.parameters.at(0);
	std::string tempMessage = message.prefix.nick + " changed his nick to " + newNick + "\n";
	MyGlobalData::newChatDlg.AddRecord("Server ", tempMessage);
   //std::cout << message.prefix.nick << " changed his nick to " << newNick << std::endl;
}

void IRCClient::HandleUserQuit(IRCMessage message)
{
    //std::string text = message.parameters.at(0);
    //std::cout << message.prefix.nick << " quits (" << text << ")" << std::endl;
}

void IRCClient::HandleChannelNamesList(IRCMessage message)
{
	return;
	try {
		std::string channel = message.parameters.at(2);
		std::string nicks = message.parameters.at(3);
		std::string tempMessage = "People on " + channel + ":" + "\n" + nicks + "\n";
		MyGlobalData::newChatDlg.AddRecord("Server ", tempMessage);
		//std::cout << "People on " << channel << ":" << std::endl << nicks << std::endl;
	}
	catch (...){
		std::string tempMessage = "?????";
		MyGlobalData::newChatDlg.AddRecord("Server ", tempMessage);
		//std::cout << "?????";
	}
}

void IRCClient::HandleNicknameInUse(IRCMessage message)
{
	std::string tempMessage = message.parameters.at(1) + " " + message.parameters.at(2) + "\n";
	MyGlobalData::newChatDlg.AddRecord("Server ", tempMessage);
    //std::cout << message.parameters.at(1) << " " << message.parameters.at(2) << std::endl;
}

void IRCClient::HandleServerMessage(IRCMessage message)
{
    if( message.parameters.empty() )
        return;

    std::vector<std::string>::const_iterator itr = message.parameters.begin();
    ++itr; // skip the first parameter (our nick)

	std::string MSG="";

    for (; itr != message.parameters.end(); ++itr)
        MSG+= *itr ;
    //std::cout << std::endl;
	MyGlobalData::newChatDlg.AddRecord("Server ", MSG);
	
}
