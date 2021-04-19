#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <unistd.h>
#include <pthread.h>
#include <winsock2.h>
#pragma comment(lib, "ws2_32.lib") //Winsock Library

#define PORT 1108
#define DEFAULT_BUFLEN 512

//void *myThreadFun(void *vargp)
//{
    //while (true)
    //{

    //    printf("%c",getch());
    //}
       
//}
   

int main(int argc, char *argv[])
{
    WSADATA wsa;
    SOCKET cSocket;
    struct sockaddr_in server;
    char c = 0;
    const char *sendbuff = "Tecla\n";
    const char *sendw = "Tecla w\n";
    const char *senda = "Tecla a\n";
    const char *sends = "Tecla s\n";
    const char *sendd = "Tecla d\n";
    char recvbuf[DEFAULT_BUFLEN];
    int iResult;
    int recvbuflen = DEFAULT_BUFLEN;

    printf("\nInitialising Winsock...");
    if (WSAStartup(MAKEWORD(2,2), &wsa) != 0)
    {
        printf("Failed. Error Code : %d.\nPress a key to exit...", WSAGetLastError());
        c = getch();
        return 1;
    }

    printf("Initialised.\n");

    //Create a socket
    if((cSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == INVALID_SOCKET)
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
    if (connect(cSocket, (struct sockaddr *)&server, sizeof(server)) < 0)
    {
        printf("Connect error:%d.\nPress a key to exit...", WSAGetLastError());
        closesocket(cSocket);
        WSACleanup();
        c = getch();
        return 1;
    }

    //pthread_t thread_id;
    //printf("Before Thread\n");
    ///pthread_create(&thread_id, NULL, myThreadFun, NULL);
    //pthread_join(thread_id, NULL);
    //printf("After Thread\n");


    // Send an initial buffer
   

    // Receive until the peer closes the connection
    do {
        c = getch();
        printf("Client: %c \n",c);
        switch (c)
        {
        case 'w':
            iResult = send( cSocket, sendw, (int)strlen(sendw), 0 );
            break;
        case 'a':
            iResult = send( cSocket, senda, (int)strlen(senda), 0 );
            break;
        case 's':
            iResult = send( cSocket, sends, (int)strlen(sends), 0 );
            break;
        case 'd':
            iResult = send( cSocket, sendd, (int)strlen(sendd), 0 );
            break;
        default:
            iResult = send( cSocket, sendbuff, (int)strlen(sendbuff), 0 );
            break;
        }
        if (iResult == SOCKET_ERROR) {
            printf("send failed with error: %d\n", WSAGetLastError());
            closesocket(cSocket);
            WSACleanup();
            return 1;
        }

        printf("Bytes Sent: %ld\n", iResult);

        iResult = recv(cSocket, recvbuf, recvbuflen, 0);
        if ( iResult > 0 )
        {
            printf("Bytes received: %d\n", iResult);
            printf(recvbuf);
        }
        else if ( iResult == 0 )
            printf("Connection closed\n");
        else
            printf("recv failed with error: %d\n", WSAGetLastError());

    } while( iResult > 0 );

    closesocket(cSocket);
    WSACleanup();
    return 0;
}