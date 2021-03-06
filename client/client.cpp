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


	printf("--> Requesting user:\n");
	write_to_server("command{user}");
	std::getchar();
	printf("--> Sending Hi to server:\n");
	write_to_server("hello");
	std::getchar();
	printf("--> Saving list of (abcd,123,hello,hi,sunday):\n");
	write_to_server("command{savelist}abcd,123,hello,hi,Sunday");
	std::getchar();
	printf("--> Reading the list:\n");
	write_to_server("command{getlist}");
	std::getchar();
	printf("--> Reading the 2nd elem from server:\n");
	write_to_server("command{list_elem}:2");
	std::getchar();
	printf("--> Replacing 2nd elem of list with 5798:\n");
	write_to_server("command{update_elem}:2=5798");
	std::getchar();
	printf("--> Reading the 2nd elem from server:\n");
	write_to_server("command{list_elem}:2");
	std::getchar();
	printf("--> Replacing 2nd elem of list with hello:\n");
	write_to_server("command{update_elem}:2=hello");
	std::getchar();
	printf("--> Replacing 3rd elem of list with 0000:\n");
	write_to_server("command{update_elem}:3=0000");
	std::getchar();
	printf("--> Reading the list:\n");
	write_to_server("command{getlist}");
	std::getchar();
	printf("--> Clearing the list:\n");
	write_to_server("command{clear_list}");
	std::getchar();
	printf("--> Sending Hi to server:\n");
	write_to_server("hello");
	std::getchar();
	printf("--> Saying bye to server:\n");
	write_to_server("exit");

	CloseHandle(pipe_handle);

	std::getchar();
}

int SetupClient::read_from_server()
{
	memset(buf, 0, sizeof(buf));
	if (pipe_handle != INVALID_HANDLE_VALUE)
	{
		if (ReadFile(pipe_handle, buf, sizeof(buf) - 1, &read_dw, NULL) != FALSE)
		{
			buf[read_dw] = '\0';  
			printf("Response :: %s", buf); 
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
