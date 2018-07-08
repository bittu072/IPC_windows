#pragma once
#include "stdafx.h"

#include <windows.h>
#include <tchar.h>
#include <strsafe.h>
#include <iostream>
#include <algorithm>
#include <fstream>

#include <string>
#include <vector>

#define BUF_SIZE 1024

class SetupServer
{
public:
	SetupServer();
	int start_server();
	~SetupServer();

private:
	std::string response_to_client(std::string recv_msg);
	void write_to_client(std::string);
	std::string getusename();
	void save_list(std::string list_str);
	std::string get_list();
	std::string get_elem_from_list(std::string elem_ind);
	std::string update_elem_in_list(std::string recv_substr);

	HANDLE pipe_handle;
	char buf[BUF_SIZE];
	DWORD read_dw;
	DWORD write_dw;
	std::string last_msg;
	std::vector<std::string> list_from_client;
};
