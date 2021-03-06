#include "stdafx.h"
#include "server.h"
#include <Lmcons.h>


#define BUF_SIZE 1024


SetupServer::SetupServer(void)
{
	pipe_handle = CreateNamedPipe(TEXT("\\\\.\\pipe\\brindal_Pipe"),
		PIPE_ACCESS_DUPLEX, // two way
		PIPE_TYPE_BYTE | PIPE_READMODE_BYTE | PIPE_WAIT,   // FILE_FLAG_FIRST_PIPE_INSTANCE is not needed but forces CreateNamedPipe(..) to fail if the pipe already exists...
		1, // one instance of the pipe
		1024 * 16, // outbound buf
		1024 * 16, //inbound buf
		NMPWAIT_USE_DEFAULT_WAIT, //wait time
		NULL); // default securities attributes

	memset(buf, 0, sizeof(buf));
	read_dw = 0;
	write_dw = 0;
	last_msg.clear();
	last_msg = "No message from client yet\n";
	list_from_client.clear();
}


int SetupServer::start_server()
{
	std::string recv_buf; // received buffer
	std::string res_str; //response sting

    while (pipe_handle != INVALID_HANDLE_VALUE)
    {
        if (ConnectNamedPipe(pipe_handle, NULL) != FALSE)   // wait for someone to connect to the pipe
        {
            
            recv_buf.clear();
            res_str.clear();

            while (ReadFile(pipe_handle, buf, sizeof(buf) - 1, &read_dw, NULL) != FALSE)
            {
                buf[read_dw] = '\0';

                printf("%s\n", buf);
                recv_buf  =  buf ; 
				recv_buf.erase(std::remove(recv_buf.begin(), recv_buf.end(), '\n'), recv_buf.end());
				std::transform(recv_buf.begin(), recv_buf.end(), recv_buf.begin(), ::tolower);
                res_str = response_to_client(recv_buf);
                write_to_client(res_str);
            }
        }

        DisconnectNamedPipe(pipe_handle);
    }

    return 0;
}


std::string SetupServer::response_to_client(std::string recv_msg)
{
    std::string res;
    res.clear();
	
    if (recv_msg.compare("--help") == 0)
    {
		res = "****help****\
		\n\thello - to say hi\
		\n\texit - to disconnect\
		\n\tcommand - \
		\n\t\t{user} - current user of server\
		\n\t\t{last_message} - previous message from client\
		\n\t\t{savelist} - save list on server(limit of 100 char total)\
		\n\t\t{getlist} - get list from server\
		\n\t\t{list_elem} - read element at specific index\
		\n\t\t{update_elem} - update element at specific index\
		\n\t\t{clear_list} - removed the saved list\
		\n\t\tExample.\
		\n\t\t\tcommand{user},\
		\n\t\t\tcommand{savelist}hello,hi,hey, \
		\n\t\t\tcommand{getlist}, \
		\n\t\t\tcommand{list_elem}:2, \
		\n\t\t\tcommand{update_elem}:3=Hola, \
		\n\t\t\tcommand{clear_list}\n\n";
    }
    else if (recv_msg.compare("hello") == 0)
    {
        res = "****hello****\n\tHi, How are you?\n\n";
    }
    else if (recv_msg.compare(0,7,"command") == 0)
    {
		if (recv_msg.compare(7, recv_msg.size() - 1, "{user}") == 0)
		{
			res = "current user of server: " + getusename() + "\n";
		}
		else if (recv_msg.compare(7, recv_msg.size() - 1, "{last_message}") == 0)
		{
			res = "previous mesage to server: " + last_msg + "\n";
		}
		else if (recv_msg.compare(7, 10, "{savelist}") == 0)
		{
			std::size_t pos = recv_msg.find("}");
			std::string list_elem = recv_msg.substr(pos + 1);
			save_list(list_elem);
			res = "list saved\n";
		}
		else if (recv_msg.compare(7, 9, "{getlist}") == 0)
		{
			if (list_from_client.empty() == 1)
			{
				res = "List is not set, send the list to server before reading\n";
			}
			else
			{
				std::string list_str = get_list();
				res = list_str;
			}
		}
		else if (recv_msg.compare(7, 11, "{list_elem}") == 0)
		{
			if (list_from_client.empty() == 1)
			{
				res = "List is not set, send the list to server before reading elem\n";
			}
			else
			{
				std::size_t pos = recv_msg.find(":");
				std::string elem_ind = recv_msg.substr(pos + 1, 1);
				res = get_elem_from_list(elem_ind);;
			}
		}
		else if (recv_msg.compare(7, 13, "{update_elem}") == 0)
		{
			if (list_from_client.empty() == 1)
			{
				res = "List is not set, send the list to server before updating\n";
			}
			else
			{
				std::size_t pos = recv_msg.find(":");
				std::string elem_ind = recv_msg.substr(pos + 1);
				res = update_elem_in_list(elem_ind);
			}
		}
		else if (recv_msg.compare(7, 12, "{clear_list}") == 0)
		{
			if (list_from_client.empty() == 1)
			{
				res = "List is not set, send the list to server before clearing\n";
			}
			else
			{
				list_from_client.clear();
				res = "Cleared the List\n";
			}
		}
    }
    else if (recv_msg.compare("exit") == 0)
    {
        res = "disconnect\n\n";
    }
    else
    {
        res = "**unknown message...Please check the help by sending --help!!\n";
    }

	last_msg.clear();
	last_msg = recv_msg;

    return res;
}

std::string SetupServer::getusename()
{
	char username_buf[UNLEN + 1];
	DWORD username_len = UNLEN + 1;
	GetUserName(username_buf, &username_len);
	std::string username = username_buf;
	return username;
}


void SetupServer::write_to_client(std::string msg)
{
    WriteFile(pipe_handle,
              msg.c_str(),
              600,   // allowing only 100 char max in single message
              &write_dw,
              NULL);
    return;
}

void SetupServer::save_list(std::string list_str)
{
	std::string s = list_str;
	std::string delimiter = ",";
	size_t pos = 0;
	std::string token;

	while ((pos = s.find(delimiter)) != std::string::npos) {
		token = s.substr(0, pos);
		list_from_client.push_back(token);
		s.erase(0, pos + delimiter.length());
	}
	token = s.substr(0);
	list_from_client.push_back(token);

	return;
}

std::string SetupServer::get_list()
{
	std::string list_str;
	list_str.clear();
	for (size_t i = 0; i < list_from_client.size(); i++)
	{
		list_str = list_str + list_from_client[i] + ", ";
	}
	list_str = list_str.substr(0, list_str.size() - 2) + "\n";
	return list_str;
}

std::string SetupServer::get_elem_from_list(std::string elem_ind)
{
	size_t ind = stoi(elem_ind)-1;
	if (ind > list_from_client.size())
	{
		return "Given index does not exist in the list\n";
	}
	std::string elem;
	elem.clear();
	
	elem = list_from_client[ind] + "\n";

	return elem;
}

std::string SetupServer::update_elem_in_list(std::string recv_substr)
{
	size_t ind = stoi(recv_substr.substr(0,1)) -1;
	if (ind > list_from_client.size())
	{
		return "Given index does not exist in the list\n";
	}

	size_t pos = 0;
	std::string value_str;
	

	pos = recv_substr.find("=");
	value_str = recv_substr.substr(pos + 1);
	printf("____&&&&&(%s)\n", value_str.c_str());
	list_from_client[ind] = value_str;


	return "List Updated\n";
}

SetupServer::~SetupServer(void)
{

}
