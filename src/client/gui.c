#include <winsock2.h>
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <unistd.h>
#include <pthread.h>
#include <stdbool.h>
#include <wchar.h>
#include <gdiplus.h>
#include <string.h> //For C
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
#define ID_TIMER 1

HBITMAP hBgImg, hPlayBImg,hSpectBImg,hExitBImg,hGameBgImg; //Utilities
HBITMAP hPlayerRImg, hPlayerLImg,hPlayerMoveRImg,hPlayerMoveLImg,hPlayerUpRImg,hPlayerUpLImg; //player
HBITMAP hEnemyBlueImg,hEnemyRedImg,hFruitImg; //Enemies
HWND hBg,hbutt_spect,hbutt_play,hbutt_exit,hgame,hpoints,hlives;
HWND elements[40], past[40];
HBITMAP imgs[40];
bool playing = false;
bool connected = false;
bool ready = true;
bool sent = false;
bool right = true;
bool up = false;
bool moving = false;
int onScreenElem = 0;
bool clean = false;

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM , LPARAM);
void addControls(HWND);
void loadImages();
void sendToServer(int);
bool initializeSocket();
void update(HWND);
void gameStart(HWND);
void windowSetNewImg(int, int, int,HWND);
void setPositions(char*, int , HWND);

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


    ShowWindow(hgame, nCmdShow);
    UpdateWindow(hgame);

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
            UINT ret;
            loadImages();
            addControls(hwnd);
            ret = SetTimer(hwnd, ID_TIMER, 250, NULL);
			if(ret == 0)
				MessageBox(hwnd, "Could not SetTimer()!", "Error", MB_OK | MB_ICONEXCLAMATION);
            break;
        
        
        case WM_COMMAND:

            switch (wParam)
            {
                case CONNECT_AS_PLAYER:
                    playing = true;  
                    initializeSocket();
                    gameStart(hwnd);
                    break;

                case CONNECT_AS_SPECTATOR:
                    playing = false;
                    initializeSocket();
                    gameStart(hwnd);
                    break;
                
                case CLOSE_APP:
                    closesocket(cSocket);
                    WSACleanup();   
                    DestroyWindow(hwnd);
                    break;
            }
            break;

        case WM_KEYDOWN:
        {
            if (playing)
            {
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
                        right = false;
                        sendToServer(VK_A);
                        break;
                    case VK_LEFT:
                        right = false;
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
                        right = true;
                        sendToServer(VK_D);
                        break;
                    case VK_RIGHT:
                        right = true;   
                        sendToServer(VK_D);
                        break;

                    //-----------

                    case VK_SPACE:
                        sendToServer(VK_SPACE);
                        break;
                }
            }   
            
            ready = false;

            break;
        }
        case WM_KEYUP:
        {
            ready = true;
            break;
        }
        case WM_ERASEBKGND:
        {
            return 1;
            break;
        }

        case WM_TIMER:
		{
            InvalidateRect(hwnd, NULL, FALSE);
			if (connected)
            {              
                update(hwnd);
            } 
            break;
        }
  
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
    
	return 0;
}

void addControls(HWND hwnd)
{

    //Tittle screen BG
    hBg = CreateWindowW(L"Static",NULL,WS_VISIBLE|WS_CHILD|SS_BITMAP,0,0,1280,720,hwnd,NULL,NULL,NULL);
     SendMessageW(hBg,STM_SETIMAGE,IMAGE_BITMAP,(LPARAM)hBgImg);    

    //Tittle buttons
    hbutt_play = CreateWindowW(L"Button",NULL,WS_VISIBLE|WS_CHILD|BS_BITMAP,850,400,250,50,hwnd,(HMENU)CONNECT_AS_PLAYER,NULL,NULL);
     SendMessageW(hbutt_play,BM_SETIMAGE,IMAGE_BITMAP,(LPARAM)hPlayBImg);

    hbutt_spect = CreateWindowW(L"Button",NULL,WS_VISIBLE|WS_CHILD|BS_BITMAP,850,500,250,50,hwnd,(HMENU)CONNECT_AS_SPECTATOR,NULL,NULL);
     SendMessageW(hbutt_spect,BM_SETIMAGE,IMAGE_BITMAP,(LPARAM)hSpectBImg);

    hbutt_exit = CreateWindowW(L"Button",NULL,WS_VISIBLE|WS_CHILD|BS_BITMAP,850,600,250,50,hwnd,(HMENU)CLOSE_APP,NULL,NULL);
     SendMessageW(hbutt_exit,BM_SETIMAGE,IMAGE_BITMAP,(LPARAM)hExitBImg);

        
}

void loadImages()
{
    //Tittle Screen
    hBgImg = (HBITMAP)LoadImageW(NULL,L"imgs\\tittlebg.bmp",(IMAGE_BITMAP),0,0,LR_LOADFROMFILE);
    hPlayBImg = (HBITMAP)LoadImageW(NULL,L"imgs\\play.bmp",(IMAGE_BITMAP),250,50,LR_LOADFROMFILE);
    hSpectBImg = (HBITMAP)LoadImageW(NULL,L"imgs\\spect.bmp",(IMAGE_BITMAP),250,50,LR_LOADFROMFILE);
    hExitBImg = (HBITMAP)LoadImageW(NULL,L"imgs\\exit.bmp",(IMAGE_BITMAP),250,50,LR_LOADFROMFILE);
    //Game Bg
    hGameBgImg = (HBITMAP)LoadImageW(NULL,L"imgs\\gamebg.bmp",(IMAGE_BITMAP),0,0,LR_LOADFROMFILE);
    //Player
    hPlayerRImg = (HBITMAP)LoadImageW(NULL,L"imgs\\stillr.bmp",(IMAGE_BITMAP),0,0,LR_LOADFROMFILE);
    hPlayerLImg = (HBITMAP)LoadImageW(NULL,L"imgs\\stilll.bmp",(IMAGE_BITMAP),0,0,LR_LOADFROMFILE);

    hPlayerMoveRImg = (HBITMAP)LoadImageW(NULL,L"imgs\\mover.bmp",(IMAGE_BITMAP),0,0,LR_LOADFROMFILE);
    hPlayerMoveLImg = (HBITMAP)LoadImageW(NULL,L"imgs\\movel.bmp",(IMAGE_BITMAP),0,0,LR_LOADFROMFILE);

    hPlayerUpRImg = (HBITMAP)LoadImageW(NULL,L"imgs\\upr.bmp",(IMAGE_BITMAP),0,0,LR_LOADFROMFILE);
    hPlayerUpLImg = (HBITMAP)LoadImageW(NULL,L"imgs\\upl.bmp",(IMAGE_BITMAP),0,0,LR_LOADFROMFILE);
    //Enemies
    hEnemyBlueImg =  (HBITMAP)LoadImageW(NULL,L"imgs\\blue.bmp",(IMAGE_BITMAP),0,0,LR_LOADFROMFILE);
    hEnemyRedImg =  (HBITMAP)LoadImageW(NULL,L"imgs\\red.bmp",(IMAGE_BITMAP),0,0,LR_LOADFROMFILE);
    //Fruit
    hFruitImg = (HBITMAP)LoadImageW(NULL,L"imgs\\fruit.bmp",(IMAGE_BITMAP),0,0,LR_LOADFROMFILE);

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

    if(playing && ready)
    {
        switch (key)
        {
            case VK_W:
                iResult = send( cSocket, sendw, (int)strlen(sendw), 0 );
                sent = true;
                break;
            case VK_A:
                iResult = send( cSocket, senda, (int)strlen(senda), 0 );
                sent = true;
                break;
            case VK_S:
                iResult = send( cSocket, sends, (int)strlen(sends), 0 );
                sent = true;
                break;
            case VK_D:
                iResult = send( cSocket, sendd, (int)strlen(sendd), 0 );
                sent = true;
                break;
            case VK_SPACE:
                iResult = send( cSocket, sende, (int)strlen(sende), 0 );
                sent = true;
                break;
            default:
                iResult = send( cSocket, sendbuff, (int)strlen(sendbuff), 0 );
                sent = true;
                break;
        }
        if (iResult == SOCKET_ERROR)
        {
            printf("send failed with error: %d\n", WSAGetLastError());
            closesocket(cSocket);
            WSACleanup();
        }
    }
      
}

void update(HWND hwnd)
{
    int iResult;
    char recvbuf[DEFAULT_BUFLEN];
    int recvbuflen = DEFAULT_BUFLEN;
    const char *sendbuff = "Tecla\n";
    
    
    if(!sent)
    {
        iResult = send( cSocket, sendbuff, (int)strlen(sendbuff), 0 );  

        if (iResult == SOCKET_ERROR)
            {
                printf("send failed with error: %d\n", WSAGetLastError());
                closesocket(cSocket);
                WSACleanup();
            } 
    }
    sent = false;

    iResult = recv(cSocket, recvbuf, recvbuflen, 0);

    if ( iResult > 0 )
    {
        printf("Bytes received: %d\n", iResult);
        printf(recvbuf);
    }
    else if ( iResult == 0 )
    {
        printf("Connection closed\n");
    }
    else
    {
        printf("recv failed with error: %d\n", WSAGetLastError());
    }

    for (int i = 0; i < onScreenElem ; i++)
    {
        ShowWindow(past[i],SW_HIDE);
    }   

   for(int loop = 0; loop < onScreenElem; loop++) 
   {
      past[loop] = elements[loop];
   }
   onScreenElem = 0;

    char * token = strtok(recvbuf, ";");
    int counter = 0;
    //bool lost = false;
    char* parts [5];
    // loop through the string to extract all other tokens
    while( token != NULL )
    {
        parts [counter] = token;
        counter++;
        token = strtok(NULL, ";");
    }
    for (int i = 0; i < 5 ; i++)
    {
        setPositions(parts[i],i+1,hwnd);
    }
    printf("hola >:v");

}

void setPositions(char* token, int cases, HWND hwnd)
{
    int x,y;
    int counter = 0;
    char* things [15];
    switch (cases)
        {
            case 1: //Vidas
            {
                wchar_t LivesBuffer[20];
                mbstowcs(LivesBuffer, token, 20);

                SetWindowTextW(hlives,LivesBuffer);
                if(strcmp("0",token)==1)
               {
                    //end game
                    //lost = true;
                }
                break;
            }
            case 2://Pts
            {
                wchar_t PointsBuffer[20];
                mbstowcs(PointsBuffer, token, 20);

                SetWindowTextW(hpoints,PointsBuffer);
                break;
            }
            case 3://Player x,y
            {
                char * cord = strtok(token, ",");
                x = atoi(cord);
                cord = strtok(NULL, ",");
                y = atoi(cord);
                windowSetNewImg(x,y,0,hwnd);
                break;
            }
            case 4://enemies x,y
            {
                char * cocs = strtok(token, ":");
                int type;
                while( cocs != NULL )
                {
                    things[counter] = cocs;
                    counter++;
                    cocs = strtok(NULL, ":");
                }

                for( int i = 0 ; i < counter ; i++ ) 
                {
                   char * coc = strtok(things[i], ",");
                   type = atoi(coc);
                   coc = strtok(NULL, ",");
                   x = atoi(coc);
                   coc = strtok(NULL, ",");
                   y = atoi(coc);
                
                    windowSetNewImg(x,y,type,hwnd);
                }
                break;
            }
            case 5://fruits x,y
            {
                char * fruits = strtok(token, ":");
                while( fruits  != NULL )
                {
                    things[counter] = fruits;
                    counter++;
                    fruits  = strtok(NULL, ":");
                }

                for( int i = 0 ; i < counter ; i++ ) 
                {
                   char *  fruit = strtok(things[i], ",");
                   x = atoi(fruit);
                   fruit = strtok(NULL, ",");
                   y = atoi(fruit);
                
                    windowSetNewImg(x,y,3,hwnd);
                }
                break;
        
            }
        }
}

void windowSetNewImg(int x, int y, int imgCode,HWND hwnd )
{
    HBITMAP img;
    int height = 50;
    int width = 50;
        switch (imgCode)
        {
        case 0: //player
            if (x >= 1010 && y >= 100)
            {
               if(right)
                {
                    img = hPlayerUpRImg;
                    printf("Diddy en %d y %d viendo derecha arriba\n",x,y);
                }
                else 
                {
                    img = hPlayerUpLImg;
                    printf("Diddy en %d y %d viendo izquierda arriba \n",x,y);
                }
            }

            else if (y >= 550 || y <= 230)
            {
                if(right && moving)
                {
                    img = hPlayerMoveRImg;
                    printf("Diddy en %d y %d viendo derecha moviendose \n",x,y);
                    moving = false;
                }
                else if(right) 
                {
                    img = hPlayerRImg;
                    printf("Diddy en %d y %d viendo derecha quieto\n",x,y);
                    moving = true;
                }
                else if(!right && moving) 
                {
                    img = hPlayerMoveLImg;
                    printf("Diddy en %d y %d viendo izquierda moviendose \n",x,y);
                    moving = false;
                }
                else 
                {
                    img = hPlayerLImg;
                    printf("Diddy en %d y %d viendo izquierda quieto \n",x,y);
                    moving = true;
                }
            }
            else
            {
                if(right)
                {
                    img = hPlayerUpRImg;
                    printf("Diddy en %d y %d en liana viendo derecha \n",x,y);
                }
                else 
                {
                    img = hPlayerUpLImg;
                    printf("Diddy en %d y %d en liana viendo izquierda\n",x,y);
                }
            }
            break;


        case 1: // red enemy
            img = hEnemyRedImg;
            height = 150;
            width = 150;
            printf("Rojo en %d y %d\n",x,y);
            break;
        case 2: // blue enemy
            img = hEnemyBlueImg;
            height = 150;
            width = 150;
            printf("Azul en %d y %d\n",x,y);
            break;
        case 3: //fruit
            img = hFruitImg;
            height = 150;
            width = 150;
            printf("Fruta en %d y %d\n",x,y);
            break;

        }

        HWND temp = CreateWindowW(L"Static",NULL,WS_VISIBLE|WS_CHILD|SS_BITMAP,x,y,width,height,hwnd,NULL,NULL,NULL);
        SendMessageW(temp,STM_SETIMAGE,IMAGE_BITMAP,(LPARAM)img);
        elements[onScreenElem] = temp;
        imgs[onScreenElem] = img;
        onScreenElem++;

        

}

void gameStart(HWND hwnd)
{
    ShowWindow(hbutt_play,SW_HIDE);
    ShowWindow(hbutt_spect,SW_HIDE);
    ShowWindow(hbutt_exit,SW_HIDE);
    SendMessageW(hBg,STM_SETIMAGE,IMAGE_BITMAP,(LPARAM)hGameBgImg);

    hpoints = CreateWindowW(L"Static",L"POINTS:",WS_VISIBLE|WS_CHILD,900,20,100,20,hwnd,NULL,NULL,NULL);
    hlives = CreateWindowW(L"Static",L"LIVES:",WS_VISIBLE|WS_CHILD,1100,20,100,20,hwnd,NULL,NULL,NULL);
    
}