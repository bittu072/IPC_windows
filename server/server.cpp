#include "stdafx.h"
#include <windows.h>
#include <tchar.h>
#include <strsafe.h>
#include <iostream>

#include <string>

#define BUF_SIZE 1024



int main(void)
{
    HANDLE pipe_handle;
    char buf[BUF_SIZE];
    DWORD read_dw;


    pipe_handle = CreateNamedPipe(TEXT("\\\\.\\pipe\\brindal_Pipe"),
                            PIPE_ACCESS_DUPLEX, // two way
                            PIPE_TYPE_BYTE | PIPE_READMODE_BYTE | PIPE_WAIT,   // FILE_FLAG_FIRST_PIPE_INSTANCE is not needed but forces CreateNamedPipe(..) to fail if the pipe already exists...
                            1, // one instance of the pipe
                            1024 * 16, // outbound buf
                            1024 * 16, //inbound buf
                            NMPWAIT_USE_DEFAULT_WAIT, //wait time
                            NULL); // default securities attributes
    while (pipe_handle != INVALID_HANDLE_VALUE)
    {
        if (ConnectNamedPipe(pipe_handle, NULL) != FALSE)   // wait for someone to connect to the pipe
        {
            while (ReadFile(pipe_handle, buf, sizeof(buf) - 1, &read_dw, NULL) != FALSE)
            {
                /* add terminating zero */
                buf[read_dw] = '\0';

                /* do something with data in buf */
                printf("%s", buf);
            }
        }

        DisconnectNamedPipe(pipe_handle);
    }

    return 0;
}
