#include <stdio.h>
#include <conio.h>
#include <winsock2.h>
#pragma comment(lib, "ws2_32.lib") //Winsock Library

#define PORT 1108

int main(int argc, char *argv[])
{
    WSADATA wsa;
    SOCKET s;
    struct sockaddr_in server;
    char c = 0;

    printf("\nInitialising Winsock...");
    if (WSAStartup(MAKEWORD(2,2), &wsa) != 0)
    {
        printf("Failed. Error Code : %d.\nPress a key to exit...", WSAGetLastError());
        c = getch();
        return 1;
    }

    printf("Initialised.\n");

    //Create a socket
    if((s = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == INVALID_SOCKET)
    {
        printf("Could not create socket : %d.\n", WSAGetLastError());
        WSACleanup();
        c = getch();
        return 1;
    }
    printf("Socket created. Connecting...\n");
    memset(&server, 0, sizeof server);
    server.sin_addr.s_addr = inet_addr("127.0.0.1");
    server.sin_family = AF_INET;
    server.sin_port = htons(PORT);

    //Connect to remote server
    if (connect(s, (struct sockaddr *)&server, sizeof(server)) < 0)
    {
        printf("Connect error:%d.\nPress a key to exit...", WSAGetLastError());
        closesocket(s);
        WSACleanup();
        c = getch();
        return 1;
    }
    puts("Connected.\nPress a key to exit...");
    closesocket(s);
    WSACleanup();
    c = getch();
    return 0;
}