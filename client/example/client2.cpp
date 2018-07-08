#include "stdafx.h"
#include <windows.h>
#include <tchar.h>
#include <strsafe.h>
#include <iostream>
#include <algorithm>
#include <string>

int main(void)
{
	HANDLE pipe_handle;
	DWORD write_dw;
	DWORD read_dw;
	char buf[1024];


	pipe_handle = CreateFile(TEXT("\\\\.\\pipe\\brindal_Pipe"),
		GENERIC_READ | GENERIC_WRITE,
		0,
		NULL,
		OPEN_EXISTING,
		0,
		NULL);

	while (pipe_handle != INVALID_HANDLE_VALUE)
	{

			WriteFile(pipe_handle,
				"command{last_message}\n",
				50,   // = length of string + terminating '\0' !!!
				&write_dw,
				NULL);
			while (ReadFile(pipe_handle, buf, sizeof(buf) - 1, &read_dw, NULL) != FALSE)
			{
				buf[read_dw] = '\0';

				printf("%s", buf);
				break;
			}

			WriteFile(pipe_handle,
				"hello\n",
				50,   // = length of string + terminating '\0' !!!
				&write_dw,
				NULL);
			while (ReadFile(pipe_handle, buf, sizeof(buf) - 1, &read_dw, NULL) != FALSE)
			{
				buf[read_dw] = '\0';

				printf("%s", buf);
				break;
			}

			WriteFile(pipe_handle,
				"--help\n",
				50,   // = length of string + terminating '\0' !!!
				&write_dw,
				NULL);
			while (ReadFile(pipe_handle, buf, sizeof(buf) - 1, &read_dw, NULL) != FALSE)
			{
				buf[read_dw] = '\0';

				printf("%s", buf);
				break;
			}

			WriteFile(pipe_handle,
				"command{user}\n",
				50,   // = length of string + terminating '\0' !!!
				&write_dw,
				NULL);
			while (ReadFile(pipe_handle, buf, sizeof(buf) - 1, &read_dw, NULL) != FALSE)
			{
				buf[read_dw] = '\0';

				printf("%s_______________\n", buf);
				break;
			}
	
			WriteFile(pipe_handle,
				"command{savelist}hello,hi,hey\n",
				50,   // = length of string + terminating '\0' !!!
				&write_dw,
				NULL);
			while (ReadFile(pipe_handle, buf, sizeof(buf) - 1, &read_dw, NULL) != FALSE)
			{
				buf[read_dw] = '\0';

				printf("%s", buf);
				break;
			}

			WriteFile(pipe_handle,
				"command{getlist}\n",
				50,   // = length of string + terminating '\0' !!!
				&write_dw,
				NULL);
			while (ReadFile(pipe_handle, buf, sizeof(buf) - 1, &read_dw, NULL) != FALSE)
			{
				buf[read_dw] = '\0';

				printf("%s", buf);
				break;
			}

			WriteFile(pipe_handle,
				"command{list_elem}:2\n",
				25,   // = length of string + terminating '\0' !!!
				&write_dw,
				NULL);
			while (ReadFile(pipe_handle, buf, sizeof(buf) - 1, &read_dw, NULL) != FALSE)
			{
				buf[read_dw] = '\0';

				printf("%s", buf);
				break;
			}

			WriteFile(pipe_handle,
				"command{update_elem}:3=Hola\n",
				50,   // = length of string + terminating '\0' !!!
				&write_dw,
				NULL);
			WriteFile(pipe_handle,
				"command{getlist}\n",
				50,   // = length of string + terminating '\0' !!!
				&write_dw,
				NULL);
			printf("DONE::::::: both command together");
			while (ReadFile(pipe_handle, buf, sizeof(buf) - 1, &read_dw, NULL) != FALSE)
			{
				buf[read_dw] = '\0';

				printf("%s", buf);
				break;
			}

			WriteFile(pipe_handle,
				"command{list_elm}:3\n",
				50,   // = length of string + terminating '\0' !!!
				&write_dw,
				NULL);
			printf("######3\n");
			while (ReadFile(pipe_handle, buf, sizeof(buf) - 1, &read_dw, NULL) != FALSE)
			{
				buf[read_dw] = '\0';

				printf("%s", buf);
				break;
			}

			WriteFile(pipe_handle,
				"command{list_elem}:5\n",
				50,   // = length of string + terminating '\0' !!!
				&write_dw,
				NULL);
			printf("does not onee\n");
			while (ReadFile(pipe_handle, buf, sizeof(buf) - 1, &read_dw, NULL) != FALSE)
			{
				buf[read_dw] = '\0';

				printf("%s", buf);
				break;
			}

			WriteFile(pipe_handle,
				"command{list_elem}:1\n",
				50,   // = length of string + terminating '\0' !!!
				&write_dw,
				NULL);
			while (ReadFile(pipe_handle, buf, sizeof(buf) - 1, &read_dw, NULL) != FALSE)
			{
				buf[read_dw] = '\0';

				printf("%s", buf);
				break;
			}

			WriteFile(pipe_handle,
				"command{list_elem}:3\n",
				50,   // = length of string + terminating '\0' !!!
				&write_dw,
				NULL);
			while (ReadFile(pipe_handle, buf, sizeof(buf) - 1, &read_dw, NULL) != FALSE)
			{
				buf[read_dw] = '\0';

				printf("%s", buf);
				break;
			}

			WriteFile(pipe_handle,
				"command{clear_list}\n",
				50,   // = length of string + terminating '\0' !!!
				&write_dw,
				NULL);
			while (ReadFile(pipe_handle, buf, sizeof(buf) - 1, &read_dw, NULL) != FALSE)
			{
				buf[read_dw] = '\0';

				printf("%s", buf);
				break;
			}

			WriteFile(pipe_handle,
				"command{getlist}\n",
				50,   // = length of string + terminating '\0' !!!
				&write_dw,
				NULL);
			while (ReadFile(pipe_handle, buf, sizeof(buf) - 1, &read_dw, NULL) != FALSE)
			{
				buf[read_dw] = '\0';

				printf("%s", buf);
				break;
			}

			WriteFile(pipe_handle,
				"command{list_elem}:1\n",
				50,   // = length of string + terminating '\0' !!!
				&write_dw,
				NULL);
			while (ReadFile(pipe_handle, buf, sizeof(buf) - 1, &read_dw, NULL) != FALSE)
			{
				buf[read_dw] = '\0';

				printf("%s", buf);
				break;
			}

			WriteFile(pipe_handle,
				"command{update_elem}:3=Hola\n",
				50,   // = length of string + terminating '\0' !!!
				&write_dw,
				NULL);
			while (ReadFile(pipe_handle, buf, sizeof(buf) - 1, &read_dw, NULL) != FALSE)
			{
				buf[read_dw] = '\0';

				printf("%s", buf);
				break;
			}

			WriteFile(pipe_handle,
				"command{last_message}\n",
				50,   // = length of string + terminating '\0' !!!
				&write_dw,
				NULL);
			while (ReadFile(pipe_handle, buf, sizeof(buf) - 1, &read_dw, NULL) != FALSE)
			{
				buf[read_dw] = '\0';

				printf("%s", buf);
				break;
			}
	
			std::string temp_buf;
			WriteFile(pipe_handle,
				"exit\n",
				50,   // = length of string + terminating '\0' !!!
				&write_dw,
				NULL);
			while (ReadFile(pipe_handle, buf, sizeof(buf) - 1, &read_dw, NULL) != FALSE)
			{
				buf[read_dw] = '\0';

				printf("%s", buf);
				temp_buf = buf;
				break;
			}
			temp_buf.erase(std::remove(temp_buf.begin(), temp_buf.end(), '\n'), temp_buf.end());
			if (temp_buf.compare("disconnect") == 0)
			{
				CloseHandle(pipe_handle);
				break;
			}



	}


	
	return 0;
}

