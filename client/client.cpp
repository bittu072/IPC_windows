#include "stdafx.h"
#include "client.h"
#include <thread>

SetupClient::SetupClient()
{
    memset(buf, 0, sizeof(buf));
	read_dw = 0;
	write_dw = 0;
}

void SetupClient::connect_to_client()
{
    pipe_handle = CreateFile(TEXT("\\\\.\\pipe\\brindal_Pipe"),
                       GENERIC_READ | GENERIC_WRITE,
                       0,
                       NULL,
                       OPEN_EXISTING,
                       0,
                       NULL);



	write_to_server("command{user}");
	write_to_server("hello");
	write_to_server("command{savelist}abcd,123,hello,hi,Sunday");
	write_to_server("command{getlist}");
	write_to_server("command{get_elem}:2");
	write_to_server("command{update_elem}:2=5798");
	write_to_server("command{list_elem}:2");
	write_to_server("command{update_elem}:2=hello");
	write_to_server("command{update_elem}:3=0000");
	write_to_server("command{getlist}");
	write_to_server("command{clear_list}");
	write_to_server("hello");
	write_to_server("command{getlist}");
	write_to_server("command{update_elem}:3=0000");
	write_to_server("exit");

	CloseHandle(pipe_handle);
}

int SetupClient::read_from_server()
{
	memset(buf, 0, sizeof(buf));
	if (pipe_handle != INVALID_HANDLE_VALUE)
	{
		if (ReadFile(pipe_handle, buf, sizeof(buf) - 1, &read_dw, NULL) != FALSE)
		{
			buf[read_dw] = '\0';  
			printf("%s", buf); 
		}
	}
    return 0;
}

int SetupClient::process_response_from_server(std::string buf)
{
	printf("checking res");

    if (buf.compare("disconnect") == 0)
    {
        return 0;
    }
    return 1;
}


void SetupClient::write_to_server(std::string msg)
{
	if (pipe_handle != INVALID_HANDLE_VALUE)
	{
		WriteFile(pipe_handle,
			msg.c_str(),
			100,   // allowing only 100 char max in single message
			&write_dw,
			NULL);
	}

	read_from_server();

    return ;
}

SetupClient::~SetupClient(void)
{
    
}
