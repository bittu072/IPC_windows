#include "stdafx.h"
#include "client.h"
#include <iostream>

int main(void)
{
	SetupClient ipc_client;
	ipc_client.connect_to_client();

	return 0;
}
