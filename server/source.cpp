#include "stdafx.h"
#include "server.h"
#include <iostream>

int main(void)
{
	SetupServer ipc_server;
	ipc_server.start_server();

	return 0;
}
