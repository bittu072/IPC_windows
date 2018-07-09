#include "stdafx.h"
#include <windows.h>
#include <tchar.h>
#include <strsafe.h>
#include <iostream>

#define BUF_SIZE 1024



class SetupClient
{
public:
    SetupClient();
    void connect_to_client();
    ~SetupClient();

private:
	int read_from_server();
	
	int process_response_from_server(std::string buf);
    void write_to_server(std::string msg);

    HANDLE pipe_handle;
    char buf[BUF_SIZE];
    DWORD read_dw;
    DWORD write_dw;
};
