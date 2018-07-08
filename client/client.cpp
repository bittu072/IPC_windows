#include "stdafx.h"
#include <windows.h>
#include <tchar.h>
#include <strsafe.h>
#include <iostream>

int main(void)
{
    HANDLE pipe_handle;
    DWORD write_dw;


    pipe_handle = CreateFile(TEXT("\\\\.\\pipe\\brindal_Pipe"),
                       GENERIC_READ | GENERIC_WRITE,
                       0,
                       NULL,
                       OPEN_EXISTING,
                       0,
                       NULL);
    if (pipe_handle != INVALID_HANDLE_VALUE)
    {
        WriteFile(pipe_handle,
                  "Hello pipe server __ this is brindal\n",
                  100,   // allowing only 100 char max in single message
                  &write_dw,
                  NULL);

        CloseHandle(pipe_handle);
    }

    return (0);
}
