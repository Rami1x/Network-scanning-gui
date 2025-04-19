#include "netinput.h"
#include <stdio.h>
#include <string.h>

#define TIMEOUT 2000
#define MAX_HOSTNAME_LENGTH 256

int initialize_winsock() {
	WSADATA wsa;
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
		return 1;	// Error
	}
	return 0;		// Success WOOO!
}

void cleanup_winsock() {
	WSACleanup();
}

int scan_port(const char* ip_address, int port, char* hostname) {
	SOCKET socker;
	struct sockaddr_in target;
	int res;
	struct hostent* host;
	
	// Get da hostname 
	unsigned long ip = inet_addr(ip_address); 	//must be unsigned long to use it
	if (ip != INADDR_NONE) {
		host = gethostbyaddr((const char*)&ip, sizeof(ip), AF_INET);
		if (host != NULL) {
			strncpy(hostname, host->h_name, MAX_HOSTNAME_LENGTH - 1);
			hostname[MAX_HOSTNAME_LENGTH - 1] = '\0';
		} 
		else {
			strcpy(hostname, "unknown");
		}
	}
	else {
		strcpy(hostname, "unknown");
	}
	
	// Creating the socket and error correcting
	socker = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (socker == INVALID_SOCKET) {
		return -1;
	}
	
	// This part is for the target
	target.sin_family = AF_INET;
	target.sin_port = htons(port);
	target.sin_addr.s_addr = inet_addr(ip_address);
	
	if (target.sin_addr.s_addr == INADDR_NONE) {
		closesocket(socker);
		return 2;
	}
	
	// Timeout stuff
	DWORD timeout = TIMEOUT;		// DWORD IS A 32bit unsigned integer
	setsockopt(socker, SOL_SOCKET, SO_RCVTIMEO, (const char*)&timeout, sizeof(timeout));
	setsockopt(socker, SOL_SOCKET, SO_SNDTIMEO, (const char*)&timeout, sizeof(timeout));
	
	// attempting to connect
	res = connect(socker, (struct sockaddr*)&target, sizeof(target));
	closesocket(socker);
	
	if (res == SOCKET_ERROR) {
		int error = WSAGetLastError();
		if (error == WSAETIMEDOUT) {
			return -3;		//Timeout :(
		}
		else if (error == WSAECONNREFUSED){
			return -4;		// Connection refused (blocked)
		}
		return -5;			// Unknown error
	}
	
	return 0;  				// Success (port open)
}