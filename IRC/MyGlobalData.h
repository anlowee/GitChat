#pragma once

#include "IRCClient/IRCClient.h"

class MyGlobalData
{
public:
	MyGlobalData();
	~MyGlobalData();

	static CString g_strUsername;
	static IRCClient aIRCClient;
};

