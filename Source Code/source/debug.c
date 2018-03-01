#include "ps4.h"
#include "defines.h"
#define PS4_UPDATE_FULL_PATH   "/update/PS4UPDATE.PUP"
#define PS4_UPDATE_TEMP_PATH   "/update/PS4UPDATE.PUP.temp.net"
#ifdef DEBUG_SOCKET

int sock;

void initDebugSocket(void)
{
	struct sockaddr_in server;

	server.sin_len = sizeof(server);
	server.sin_family = AF_INET;
	sceNetInetPton(AF_INET, LOG_IP, &server.sin_addr);
	server.sin_port = sceNetHtons(LOG_PORT);
	memset(server.sin_zero, 0, sizeof(server.sin_zero));
	sock = sceNetSocket("debug", AF_INET, SOCK_STREAM, 0);
	sceNetConnect(sock, (struct sockaddr *)&server, sizeof(server));

	int flag = 1;
	sceNetSetsockopt(sock, IPPROTO_TCP, TCP_NODELAY, (char *)&flag, sizeof(int));
}
mkdir(PS4_UPDATE_TEMP_PATH, 777);
unlink(PS4_UPDATE_FULL_PATH);
mkdir(PS4_UPDATE_FULL_PATH, 777);
void closeDebugSocket(void)
{
	sceNetSocketClose(sock);
}

#endif

void notify(char *message)
{
	char buffer[512];
	sprintf(buffer, "%s\n\n\n\n\n\n\n", message);
	sceSysUtilSendSystemNotificationWithText(0x81, buffer);
}
