#include <winsock2.h>
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <unistd.h>
#include <pthread.h>
#include <stdbool.h>
#pragma comment(lib, "ws2_32.lib") //Winsock Library

//Socket
#define PORT 1108
#define DEFAULT_BUFLEN 512
SOCKET cSocket;

//GUI
const char g_szClassName[] = "myWindowClass";
#define CONNECT_AS_PLAYER    11
#define CONNECT_AS_SPECTATOR 10
#define CLOSE_APP 100
#define VK_W 0x57
#define VK_A 0x41
#define VK_S 0x53
#define VK_D 0x44

HBITMAP hLogoImg, hPlayBImg,hSpectBImg,hExitBImg;
HWND hLogo;
bool playing = false;
bool connected = false;

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM , LPARAM);
void addControls(HWND);
void loadImages();
void sendToServer(int);
bool initializeSocket();
void update();


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
    LPSTR lpCmdLine, int nCmdShow)
{
    WNDCLASSEX wc;
    HWND hwnd;
    MSG Msg;

    wc.cbSize        = sizeof(WNDCLASSEX);
    wc.style         = 0;
    wc.lpfnWndProc   = WndProc;
    wc.cbClsExtra    = 0;
    wc.cbWndExtra    = 0;
    wc.hInstance     = hInstance;
    wc.hIcon         = LoadIcon(NULL, IDI_APPLICATION);
    wc.hCursor       = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
    wc.lpszMenuName  = NULL;
    wc.lpszClassName = g_szClassName;
    wc.hIconSm       = LoadIcon(NULL, IDI_APPLICATION);

    if(!RegisterClassEx(&wc))
    {
        MessageBox(NULL, "Window Registration Failed!", "Error!",
            MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }

    hwnd = CreateWindowEx(
        WS_EX_CLIENTEDGE,
        g_szClassName,
        "DonCEy Kong Jr. VS",
        WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX ,
        CW_USEDEFAULT, CW_USEDEFAULT, 1280, 720,
        NULL, NULL, hInstance, NULL);

    if(hwnd == NULL)
    {
        MessageBox(NULL, "Window Creation Failed!", "Error!",
            MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }

    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);

    while(GetMessage(&Msg, NULL, 0, 0) > 0)
    {
        TranslateMessage(&Msg);
        DispatchMessage(&Msg);
    }
    return Msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch(msg)
	{
        case WM_CREATE:
            loadImages();
            addControls(hwnd);
            break;
        
        
        case WM_COMMAND:

            switch (wParam)
            {
                case CONNECT_AS_PLAYER:
                    playing = true;  
                    initializeSocket();
                    break;

                case CONNECT_AS_SPECTATOR:
                    playing = false;
                    initializeSocket();
                    break;
                
                case CLOSE_APP:
                    closesocket(cSocket);
                    WSACleanup();   
                    DestroyWindow(hwnd);
                    break;
            }
            break;

        case WM_KEYDOWN:

            switch (wParam)
            {

                case VK_W:
                    sendToServer(VK_W);
                    break;
                case VK_UP:
                    sendToServer(VK_W);
                    break;

                //-----------

                case VK_A:
                    sendToServer(VK_A);
                    break;
                case VK_LEFT:
                    sendToServer(VK_A);
                    break;

                 //-----------
                
                case VK_S:
                    sendToServer(VK_S);
                    break;
                case VK_DOWN:
                    sendToServer(VK_S);
                    break;



                 //-----------

                case VK_D:
                    sendToServer(VK_D);
                    break;
                case VK_RIGHT:
                    sendToServer(VK_D);
                    break;

                 //-----------

                 case VK_SPACE:
                    sendToServer(VK_SPACE);
                    break;
                }
            sendToServer(0);
            break;
  

		case WM_CLOSE:
            closesocket(cSocket);
            WSACleanup();   
			DestroyWindow(hwnd);
		    break;

		case WM_DESTROY:
			PostQuitMessage(0);
		    break;

		default:
			return DefWindowProc(hwnd, msg, wParam, lParam);
	}
    
    if (connected){
        update();
    } 
	return 0;
}

void addControls(HWND hwnd)
{

    //Tittle BG
    hLogo = CreateWindowW(L"Static",NULL,WS_VISIBLE|WS_CHILD|SS_BITMAP,0,0,1280,720,hwnd,NULL,NULL,NULL);
     SendMessageW(hLogo,STM_SETIMAGE,IMAGE_BITMAP,(LPARAM)hLogoImg);    

    //Tittle buttons
    HWND hbutt_play = CreateWindowW(L"Button",NULL,WS_VISIBLE|WS_CHILD|BS_BITMAP,850,400,250,50,hwnd,(HMENU)CONNECT_AS_PLAYER,NULL,NULL);
     SendMessageW(hbutt_play,BM_SETIMAGE,IMAGE_BITMAP,(LPARAM)hPlayBImg);

    HWND hbutt_spect = CreateWindowW(L"Button",NULL,WS_VISIBLE|WS_CHILD|BS_BITMAP,850,500,250,50,hwnd,(HMENU)CONNECT_AS_SPECTATOR,NULL,NULL);
     SendMessageW(hbutt_spect,BM_SETIMAGE,IMAGE_BITMAP,(LPARAM)hSpectBImg);

    HWND hbutt_exit = CreateWindowW(L"Button",NULL,WS_VISIBLE|WS_CHILD|BS_BITMAP,850,600,250,50,hwnd,(HMENU)CLOSE_APP,NULL,NULL);
     SendMessageW(hbutt_exit,BM_SETIMAGE,IMAGE_BITMAP,(LPARAM)hExitBImg);
}

void loadImages()
{
    hLogoImg = (HBITMAP)LoadImageW(NULL,L"imgs\\tittlebg.bmp",(IMAGE_BITMAP),0,0,LR_LOADFROMFILE);
    hPlayBImg = (HBITMAP)LoadImageW(NULL,L"imgs\\play.bmp",(IMAGE_BITMAP),250,50,LR_LOADFROMFILE);
    hSpectBImg = (HBITMAP)LoadImageW(NULL,L"imgs\\spect.bmp",(IMAGE_BITMAP),250,50,LR_LOADFROMFILE);
    hExitBImg = (HBITMAP)LoadImageW(NULL,L"imgs\\exit.bmp",(IMAGE_BITMAP),250,50,LR_LOADFROMFILE);
}


bool initializeSocket()
{
    WSADATA wsa;
    struct sockaddr_in server;

    printf("\nInitialising Winsock...");
    if (WSAStartup(MAKEWORD(2,2), &wsa) != 0)
    {
        printf("Failed. Error Code : %d.\n", WSAGetLastError());
        return false;
    }

    printf("Initialised.\n");

    //Create a socket
    if((cSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == INVALID_SOCKET)
    {
        printf("Could not create socket : %d.\n", WSAGetLastError());
        WSACleanup();
        return false;
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
        return false;
    }

    printf("Connetion succesful.\n");
    connected = true;
    sendToServer(0);
    return true;
}

void sendToServer(int key)
{
    int iResult;
    const char *sendbuff = "Tecla\n";
    const char *sendw = "Tecla w\n";
    const char *senda = "Tecla a\n";
    const char *sends = "Tecla s\n";
    const char *sendd = "Tecla d\n";
    const char *sende = "Tecla e\n";

    if(playing)
    {
        switch (key)
        {
            case VK_W:
                iResult = send( cSocket, sendw, (int)strlen(sendw), 0 );
                break;
            case VK_A:
                iResult = send( cSocket, senda, (int)strlen(senda), 0 );
                break;
            case VK_S:
                iResult = send( cSocket, sends, (int)strlen(sends), 0 );
                break;
            case VK_D:
                iResult = send( cSocket, sendd, (int)strlen(sendd), 0 );
                break;
            case VK_SPACE:
                iResult = send( cSocket, sende, (int)strlen(sende), 0 );
                break;
            default:
                iResult = send( cSocket, sendbuff, (int)strlen(sendbuff), 0 );
                break;
        }
        if (iResult == SOCKET_ERROR)
        {
            printf("send failed with error: %d\n", WSAGetLastError());
            closesocket(cSocket);
            WSACleanup();
        }
    }else{
        iResult = send( cSocket, sendbuff, (int)strlen(sendbuff), 0 );
    }      
}

void update()
{
    int iResult;
    char recvbuf[DEFAULT_BUFLEN];
    int recvbuflen = DEFAULT_BUFLEN;
    

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
}