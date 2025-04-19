// for sending and recieving data
#ifndef NETINPUT_H
#define NETINPUT_H

#include <winsock2.h>
#include <ws2tcpip.h>

#pragma comment(lib, "ws2_32.lib")

#define TIMEOUT 2000
#define MAX_HOSTNAME_LENGTH 256

// functions I need to transport
int initialize_winsock();
void cleanup_winsock();
int scan_port(const char* ip_address, int port, char* hostname);

#endif