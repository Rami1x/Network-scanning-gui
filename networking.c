#include <stdio.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <string.h>

#pragma comment(lib, "ws2_32.lib")

#define IP_ADDRESS "10.146.169.126"
#define PORT 80
#define TIMEOUT 2000
#define MAX_HOSTNAME_LENGTH 256

int main() {
	WSADATA wsa;					
	SOCKET socker;					
	struct sockaddr_in target;
	struct hostent* host;	
	int res;
	char hostname[MAX_HOSTNAME_LENGTH] = "unknown";
	
	
	// Initialize Winsock
	
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
		printf("WSAStartup failed.\n");
		return 1;
	}
	
	printf("Checking port %d on %s...\n", PORT, IP_ADDRESS);
	
	// Get hostname :) 
	unsigned long ip = inet_addr(IP_ADDRESS);
	if (ip != INADDR_NONE) {
		host = gethostbyaddr((const char*)&ip, sizeof(ip), AF_INET);
		if (host != NULL) {
			strncpy(hostname, host->h_name, MAX_HOSTNAME_LENGTH - 1);
			hostname[MAX_HOSTNAME_LENGTH - 1] = '\0';
		}
	}
	printf("Hostname: %s\n", hostname);
	
	// Creating Socket
	socker = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (socker == INVALID_SOCKET) {
		printf("Socket creation failed: %d\n", WSAGetLastError());
		WSACleanup();
		return 1;
	}
	
	// Set up the target address
	target.sin_family = AF_INET;
	target.sin_port = htons(PORT);
	if (target.sin_addr.s_addr == INADDR_NONE) {
		printf("Invalid address not supported: %s\n", IP_ADDRESS);
		closesocket(socker);
		WSACleanup();
		return 1;
	}
	
	// Set timeout for connection attempt
	DWORD timeout = TIMEOUT;
	setsockopt(socker, SOL_SOCKET, SO_RCVTIMEO, (const char*)&timeout, sizeof(timeout));
	setsockopt(socker, SOL_SOCKET, SO_SNDTIMEO, (const char*)&timeout, sizeof(timeout));
	
	// attempt to connect
	res = connect(socker, (struct sockaddr*)&target, sizeof(target));
	if (res == SOCKET_ERROR) {
		int error = WSAGetLastError();
		if (error == WSAETIMEDOUT) {
			printf("Port %d: Connection timed out (Filtered?)", PORT);
		} else if (error == WSAECONNREFUSED) {
			printf("Port %d: Closed\n", PORT);
		} else {
			printf("Port %d: Error connection (%d)\n", PORT, error);
		}
	} else {
		printf("Port %d: Open\n", PORT);
	}
	
	closesocket(socker);
	WSACleanup();
	return 0;
}