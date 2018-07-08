# IPC_windows

### Introduction
Windows Console applications to showcase IPC between server and client using named pipe.
* Written in C++
* Server can allow client to connect, to know the current user of the server, to save/read/update/remove list, to disconnect

#### Client can send following command to server:
1. hello - to say hi "hello"
2. exit - to disconnect "exit"
3. help - for help "--help"
4. command -
		{user} - current user of server "command{user}"
		{last_message} - previous message from client "command{last_message}"
		{savelist} - save list on server(limit of 100 char total) "command{savelist}elem1,elem2,elem3,...,elemN"
		{getlist} - get list from server "command{getlist}"
        {list_elem} - read element at specific index "command{list_elem}:N"
        {update_elem} - update element at specific index "command{update_elem}:N=_value_"
		{clear_list} - removed the saved list "command{clear_list}"
Example.
	command{user}
    command{savelist}hello,hi,hey
    command{getlist}
    command{list_elem}:2
    command{update_elem}:3=Hola
    command{clear_list}


#### Note
If you are not using Visual studio then remove #include "stdafx.h" from all the files
