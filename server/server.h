#pragma once


class SetupServer
{
public:
	SetupServer();
	int start_server();
	~SetupServer();

private:
	std::string response_to_client(std::string recv_msg);
	void write_to_client(std::string);

	HANDLE pipe_handle;
	char buf[BUF_SIZE];
	DWORD read_dw;
	DWORD write_dw;
}
