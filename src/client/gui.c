#include <winsock2.h>
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <stdbool.h>
#include <wchar.h>
#include <gdiplus.h>
#include <string.h> //For C
#include "constantes.h"
#pragma comment(lib, "ws2_32.lib") //Winsock Library

//Socket
SOCKET cSocket;
char recvbuf[DEFAULT_BUFLEN];

//GUI
const char g_szClassName[] = "myWindowClass";
HBITMAP hBgImg, hPlayBImg,hSpectBImg,hExitBImg,hGameBgImg,hServerBgImg,hServer1Img,hServer2Img,hGameoverImg; //Utilities
HBITMAP hPlayerRImg, hPlayerLImg,hPlayerMoveRImg,hPlayerMoveLImg,hPlayerUpRImg,hPlayerUpLImg; //player
HBITMAP hEnemyBlueImg,hEnemyRedImg,hFruitImg; //Enemies
HWND hwnd;
HWND hBg,hbutt_spect,hbutt_play,hbutt_exit,hbutt_srv1,hbutt_srv2,hgame,hpoints,hlives;
HWND elements[40], past[40];
HBITMAP imgs[40];

/**
 * @brief Estructura que controla todos los flags del juego
 * 
 */
struct gameState {

    bool playing;
    bool connected;
    bool ready;
    bool sent;
    bool right;
    bool up;
    bool moving;
    int onScreenElem;
    int onScreenPastElem;
    bool clean;
    bool lost;
    int lastX;
    int animCount;

};

struct gameState game;

/**
 * @brief Loop default de win32
 * 
 * @return LRESULT 
 */
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM , LPARAM);
/**
 * @brief Agrega todos los concontroles a la interfaz grafica en la ventana HWND
 * 
 * 
 */
void addControls(HWND);
/**
 * @brief Carga todas las imagenes de la interfaz grafica
 * 
 */
void loadImages();
/**
 * @brief Funcion que se encarga de generar y enviar los mensajes al servidor
 * 
 */
void sendToServer(int);
/**
 * @brief Funcion que se encarga de leer los mensajes del servidor y cargalos al buffer (recvbuff)
 * 
 */
void readFromServer();
/**
 * @brief Inicializa un socket para un puerto espacifico determinado por el usuario al escoger un servidor
 * 
 */
void initializeSocket(int);
/**
 * @brief Funcion que se ejecuta cada vez que termina el timer. Elimina todas las imagenes cargadas en la iteracion pasada y carga las 
 * nuevas imagenes segun lo especificado por el servidor
 * 
 */
void update(HWND);
/**
 * @brief Funcion que esconde los botones de la pantalla de titulo y muestra el fondo y los botones de la seleccion de servidor
 * 
 */
void serverSelect();
/**
 * @brief Funcion que esconde los botones de la pantalla de seleccion de servidor y muestra el fondo y los textos de juego
 * 
 */
void gameStart(HWND);
/**
 * @brief Funcion que muestra una imagen determinada por el codigo de imagen y posiciones X y Y en Hwnd
 * 
 */
void windowSetNewImg(int, int, int,HWND);
/**
 * @brief Parser del mensaje del servidor. Extrae todos los detalles que deben ser mostrados durante el ciclo de update
 * 
 */
void setPositions(char*, int , HWND);
/**
 * @brief Muestra la pantalla de derrota
 * 
 */
void endGame();

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
    LPSTR lpCmdLine, int nCmdShow)
{
    WNDCLASSEX wc;
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

    game.playing          = false;
    game.connected        = false;
    game.ready            = true;
    game.sent             = false;
    game.right            = true;
    game.up               = false;
    game.moving           = false;
    game.onScreenElem     = 0;
    game.onScreenPastElem = 0;
    game.clean            = false;
    game.lost             = false;
    game.lastX            = 85;
    game.animCount        = 0;

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
        case WM_CREATE: //Al crear la ventana
            UINT ret;
            loadImages();
            addControls(hwnd);
            ret = SetTimer(hwnd, ID_TIMER, 50, NULL);
			if(ret == 0)
				MessageBox(hwnd, "Could not SetTimer()!", "Error", MB_OK | MB_ICONEXCLAMATION);
            ShowWindow(hbutt_srv1,SW_HIDE);
            ShowWindow(hbutt_srv2,SW_HIDE);
            break;
        
        
        case WM_COMMAND: // Comandos especificos de botones

            switch (wParam)
            {
                case CONNECT_AS_PLAYER:
                    game.playing = true;  
                    serverSelect();
                    break;

                case CONNECT_AS_SPECTATOR:
                    game.playing = false;
                    serverSelect();
                    break;

                case CONNECT_TO_1:
                    initializeSocket(1);
                    sendToServer(0);
                    readFromServer();
                    gameStart(hwnd);
                    break;

                case CONNECT_TO_2:
                    initializeSocket(2);
                    sendToServer(0);
                    readFromServer();
                    gameStart(hwnd);
                    break;
                
                case CLOSE_APP:
                    closesocket(cSocket);
                    WSACleanup();   
                    DestroyWindow(hwnd);
                    break;
            }
            break;

        case WM_KEYDOWN: // Al presionar una tecla
        {
            if (game.playing && game.ready)
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
                        //game.right = false;
                        sendToServer(VK_A);
                        break;
                    case VK_LEFT:
                        //game.right = false;
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
                        //game.right = true;
                        sendToServer(VK_D);
                        break;
                    case VK_RIGHT:
                        //game.right = true;   
                        sendToServer(VK_D);
                        break;

                    //-----------

                    case VK_SPACE:
                        sendToServer(VK_SPACE);
                        break;
                }
                game.ready = false;
            }   
            
            

            break;
        }
        case WM_KEYUP: // Al liberar la tecla
        {
            game.ready = true;
            break;
        }
        case WM_ERASEBKGND: // Evita el flicker de las imagenes
        {
            return 1;
            break;
        }

        case WM_TIMER: // Al terminar el timer
		{
            InvalidateRect(hwnd, NULL, FALSE);
			if (game.connected)
            {              
                update(hwnd);
            } 
            break;
        }
  
		case WM_CLOSE:
            //sendToServer(1);
            closesocket(cSocket);
            WSACleanup();   
			DestroyWindow(hwnd);
		    break;

		case WM_DESTROY:
            //sendToServer(1);
            closesocket(cSocket);
            WSACleanup();
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

    //Sever select buttons
    hbutt_srv1 = CreateWindowW(L"Button",NULL,WS_VISIBLE|WS_CHILD|BS_BITMAP,50,500,250,50,hwnd,(HMENU)CONNECT_TO_1,NULL,NULL);
     SendMessageW(hbutt_srv1,BM_SETIMAGE,IMAGE_BITMAP,(LPARAM)hServer1Img);

    hbutt_srv2 = CreateWindowW(L"Button",NULL,WS_VISIBLE|WS_CHILD|BS_BITMAP,950,500,250,50,hwnd,(HMENU)CONNECT_TO_2,NULL,NULL);
     SendMessageW(hbutt_srv2,BM_SETIMAGE,IMAGE_BITMAP,(LPARAM)hServer2Img);

        
}

void loadImages()
{
    //Tittle Screen
    hBgImg = (HBITMAP)LoadImageW(NULL,L"imgs\\tittlebg.bmp",(IMAGE_BITMAP),0,0,LR_LOADFROMFILE);
    hPlayBImg = (HBITMAP)LoadImageW(NULL,L"imgs\\play.bmp",(IMAGE_BITMAP),250,50,LR_LOADFROMFILE);
    hSpectBImg = (HBITMAP)LoadImageW(NULL,L"imgs\\spect.bmp",(IMAGE_BITMAP),250,50,LR_LOADFROMFILE);
    hExitBImg = (HBITMAP)LoadImageW(NULL,L"imgs\\exit.bmp",(IMAGE_BITMAP),250,50,LR_LOADFROMFILE);
    //Server select
    hServerBgImg = (HBITMAP)LoadImageW(NULL,L"imgs\\serverbg.bmp",(IMAGE_BITMAP),0,0,LR_LOADFROMFILE);
    hServer1Img = (HBITMAP)LoadImageW(NULL,L"imgs\\server1.bmp",(IMAGE_BITMAP),250,50,LR_LOADFROMFILE);
    hServer2Img = (HBITMAP)LoadImageW(NULL,L"imgs\\server2.bmp",(IMAGE_BITMAP),250,50,LR_LOADFROMFILE);
    //Game Bg
    hGameBgImg = (HBITMAP)LoadImageW(NULL,L"imgs\\gamebg.bmp",(IMAGE_BITMAP),0,0,LR_LOADFROMFILE);
    hGameoverImg = (HBITMAP)LoadImageW(NULL,L"imgs\\gameover.bmp",(IMAGE_BITMAP),0,0,LR_LOADFROMFILE);
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

void initializeSocket(int serverID)
{
    int port;

    if(serverID == 1)
    {
        port = PORT1;
    }
    else if(serverID == 2)
    {
        port = PORT2;
    }
    
    WSADATA wsa;
    struct sockaddr_in server;

    printf("\nInitialising Winsock...");
    if (WSAStartup(MAKEWORD(2,2), &wsa) != 0)
    {
        printf("Failed. Error Code : %d.\n", WSAGetLastError());
        MessageBox(hwnd, "Failed. The application will close", "Error", MB_OK | MB_ICONEXCLAMATION);
        SendMessageW(hwnd,WM_CLOSE,0,0);
     
    }

    printf("Initialised.\n");

    //Create a socket
    if((cSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == INVALID_SOCKET)
    {
        printf("Could not create socket : %d.\n", WSAGetLastError());
        MessageBox(hwnd, "Failed: Could not create socket. The application will close", "Error", MB_OK | MB_ICONEXCLAMATION);
        SendMessageW(hwnd,WM_CLOSE,0,0);
        WSACleanup();
     
    }
    printf("Socket created. Connecting...\n");
    memset(&server, 0, sizeof server);
    server.sin_addr.s_addr = inet_addr("127.0.0.1");
    server.sin_family = AF_INET;
    server.sin_port = htons(port);

    //Connect to remote server
    if (connect(cSocket, (struct sockaddr *)&server, sizeof(server)) < 0)
    {
        printf("Connect error:%d.\n", WSAGetLastError());
        MessageBox(hwnd, "Failed: Could not connect to server. The application will close", "Error", MB_OK | MB_ICONEXCLAMATION);
        SendMessageW(hwnd,WM_CLOSE,0,0);
        closesocket(cSocket);
        WSACleanup();
      
    }

    printf("Connetion succesful.\n");
    
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

    const char *sendplayer= "player\n";
    const char *sendspectator= "spectator\n";
    const char *sendbye= "bye\n";

    if(game.playing && game.ready)
    {
        switch (key)
        {
            case VK_W:
                iResult = send( cSocket, sendw, (int)strlen(sendw), 0 );
                printf("msg w enviado");
                game.sent = true;
                break;
            case VK_A:
                iResult = send( cSocket, senda, (int)strlen(senda), 0 );
                printf("msg enviado");
                game.sent = true;
                break;
            case VK_S:
                iResult = send( cSocket, sends, (int)strlen(sends), 0 );
                printf("msg enviado");
                game.sent = true;
                break;
            case VK_D:
                iResult = send( cSocket, sendd, (int)strlen(sendd), 0 );
                printf("msg enviado");
                game.sent = true;
                break;
            case VK_SPACE:
                iResult = send( cSocket, sende, (int)strlen(sende), 0 );
                printf("msg enviado");
                game.sent = true;
                break;  
        }
    }

    switch (key)
    {
    case 0:
        if(game.playing)
        {
            iResult = send( cSocket, sendplayer, (int)strlen(sendplayer), 0 );
            printf("msg enviado");
            
        }
        else if(!game.playing)
        {
            iResult = send( cSocket, sendspectator, (int)strlen(sendspectator), 0 );
            printf("msg enviado");
        }
        break;
    case 1:
        iResult = send( cSocket, sendbye, (int)strlen(sendbye), 0 );
        printf("msg enviado");
        break;

    default:
        if(!game.sent)
        {
            iResult = send( cSocket, sendbuff, (int)strlen(sendbuff), 0 );
            printf("msg update enviado");
        }
        break;   
    }

    if (iResult == SOCKET_ERROR)
        {
            game.connected = false;
            printf("send failed with error: %d\n", WSAGetLastError());
            MessageBox(hwnd, "Failed: Lost contact with server. The application will close", "Error", MB_OK | MB_ICONEXCLAMATION);
            SendMessageW(hwnd,WM_CLOSE,0,0);
            
        }

      
}

void readFromServer()
{
    int iResult;
    int recvbuflen = DEFAULT_BUFLEN;
    iResult = recv(cSocket, recvbuf, recvbuflen, 0);

    if ( iResult > 0 )
    {
        printf("Bytes received: %d\n", iResult);
        printf(recvbuf);
    }
    else if ( iResult == 0 )
    {
        printf("Connection closed\n");
        SendMessageW(hwnd,WM_CLOSE,0,0);
    }
    else
    {
        printf("recv failed with error: %d\n", WSAGetLastError());
        game.connected = false;
        MessageBox(hwnd, "Failed to read from server. The application will close", "Error", MB_OK | MB_ICONEXCLAMATION);
        SendMessageW(hwnd,WM_CLOSE,0,0);
    }
}

void update(HWND hwnd)
{
    int iResult;
    const char *sendbuff = "Tecla\n";
    
    //if(!game.sent)
    //{
        //iResult = send( cSocket, sendbuff, (int)strlen(sendbuff), 0 );  

        //if (iResult == SOCKET_ERROR)
          //  {
               // game.connected = false;
               // printf("send failed with error: %d\n", WSAGetLastError());
               // MessageBox(hwnd, "Failed: lost contact with server. The application will close", "Error", MB_OK | MB_ICONEXCLAMATION);
                //SendMessageW(hwnd,WM_CLOSE,0,0);
            //} 
    //}
   // game.sent = false;

    if (!game.sent) sendToServer(100);
    readFromServer();
    game.sent = false;

    //animation control
    if(game.animCount > 8)
    {
        if(game.moving)
        {
            game.moving = false;
        }
        else
        {
            game.moving = true;
        }

        game.animCount = 0;
    }

    game.animCount++;

    //Erase past elements off the window
    for (int i = 0; i < game.onScreenPastElem ; i++)
    {
        ShowWindow(past[i],SW_HIDE);
    }   

    //Move current elements to past
   for(int loop = 0; loop < game.onScreenElem; loop++) 
   {
      past[loop] = elements[loop];
   }
   game.onScreenPastElem = game.onScreenElem;
   game.onScreenElem = 0;

    char * token = strtok(recvbuf, ";");
    int counter = 0;
    char* parts [5];

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
}

void setPositions(char* token, int cases, HWND hwnd)
{
    int x,y;
    int counter = 0;
    char* things [15];
    if (!game.lost)
    {
        switch (cases)
        {
            case 1: //Vidas
            {

                if(strcmp(token,"LIVES:0")==0)
                {
                        game.lost = true;
                        game.playing = false;
                        game.connected = false;
                        endGame();
                }

                wchar_t LivesBuffer[20];
                mbstowcs(LivesBuffer, token, 20);

                SetWindowTextW(hlives,LivesBuffer);
                

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
                windowSetNewImg(x,y,100,hwnd);
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
} 

void windowSetNewImg(int x, int y, int imgCode,HWND hwnd )
{
    HBITMAP img;
    int height = 50;
    int width = 50;


    if (x != 0 && y != 0)
    {

        switch (imgCode)
        {
        case 100: //player

            if(game.lastX == x)
            {
                printf("%d es igual que %d ",game.lastX,x);
            }
            else if(game.lastX  > x )
            {
                printf("%d es mayor que %d ",game.lastX,x);
                game.right = false;
            }
            else if (game.lastX < x)
            {
                printf("%d es menor %d ",game.lastX,x);
                game.right = true;
            }

            game.lastX = x;

            if (x >= 1010 && y >= 100)
            {
               if(game.right)
                {
                    img = hPlayerUpRImg;
                    //printf("Diddy en %d y %d viendo derecha arriba\n",x,y);
                }
                else 
                {
                    img = hPlayerUpLImg;
                    //printf("Diddy en %d y %d viendo izquierda arriba \n",x,y);
                }
            }

            else if (y >= 550 || y <= 230)
            {
                if(game.right && game.moving)
                {
                    img = hPlayerMoveRImg;
                    //printf("Diddy en %d y %d viendo derecha moviendose \n",x,y);
                    //game.moving = false;
                }
                else if(game.right) 
                {
                    img = hPlayerRImg;
                    //printf("Diddy en %d y %d viendo derecha quieto\n",x,y);
                    //game.moving = true;
                }
                else if(!game.right && game.moving) 
                {
                    img = hPlayerMoveLImg;
                    //printf("Diddy en %d y %d viendo izquierda moviendose \n",x,y);
                    //game.moving = false;
                }
                else 
                {
                    img = hPlayerLImg;
                    //printf("Diddy en %d y %d viendo izquierda quieto \n",x,y);
                    //game.moving = true;
                }
            }
            else
            {
                if(game.right)
                {
                    img = hPlayerUpRImg;
                    //printf("Diddy en %d y %d en liana viendo derecha \n",x,y);
                }
                else 
                {
                    img = hPlayerUpLImg;
                    //printf("Diddy en %d y %d en liana viendo izquierda\n",x,y);
                }
            }
            break;


        case 1: // red enemy
            img = hEnemyRedImg;
            height = 150;
            width = 150;
            //printf("Rojo en %d y %d\n",x,y);
            break;
        case 2: // blue enemy
            img = hEnemyBlueImg;
            height = 150;
            width = 150;
            //printf("Azul en %d y %d\n",x,y);
            break;
        case 3: //fruit
            img = hFruitImg;
            height = 150;
            width = 150;
            //printf("Fruta en %d y %d\n",x,y);
            break;

        }

        HWND temp = CreateWindowW(L"Static",NULL,WS_VISIBLE|WS_CHILD|SS_BITMAP,x,y,width,height,hwnd,NULL,NULL,NULL);
        SendMessageW(temp,STM_SETIMAGE,IMAGE_BITMAP,(LPARAM)img);
        elements[game.onScreenElem] = temp;
        imgs[game.onScreenElem] = img;
        game.onScreenElem++;
    }
}

void serverSelect()
{
    SendMessageW(hBg,STM_SETIMAGE,IMAGE_BITMAP,(LPARAM)hServerBgImg);
    ShowWindow(hbutt_srv1,SW_SHOW);
    ShowWindow(hbutt_srv2,SW_SHOW);
    ShowWindow(hbutt_play,SW_HIDE);
    ShowWindow(hbutt_spect,SW_HIDE);
    ShowWindow(hbutt_exit,SW_HIDE);
}

void gameStart(HWND hwnd)
{
    

    if(strcmp(recvbuf,"pdenied")==0)
    {
        sendToServer(1);
        game.connected = false;
        MessageBox(hwnd, "Sorry! The server already has a player, you can try other server or spectate the game. The application will close", "Error", MB_OK | MB_ICONEXCLAMATION);
        SendMessageW(hwnd,WM_CLOSE,0,0);
    }
    else if(strcmp(recvbuf,"sdenied")==0)
    {
        sendToServer(1);
        game.connected = false;
        MessageBox(hwnd, "Sorry! The server is still needs a player, no more spectators allowed. The application will close", "Error", MB_OK | MB_ICONEXCLAMATION);
        SendMessageW(hwnd,WM_CLOSE,0,0);
    }
    else
    {
        game.connected = true;

        hpoints = CreateWindowW(L"Static",L"POINTS:",WS_VISIBLE|WS_CHILD,900,20,100,20,hwnd,NULL,NULL,NULL);
        hlives = CreateWindowW(L"Static",L"LIVES:",WS_VISIBLE|WS_CHILD,1100,20,100,20,hwnd,NULL,NULL,NULL);
    }

    ShowWindow(hbutt_srv1,SW_HIDE);
    ShowWindow(hbutt_srv2,SW_HIDE);
    SendMessageW(hBg,STM_SETIMAGE,IMAGE_BITMAP,(LPARAM)hGameBgImg);
 
}

void endGame(){

    for (int i = 0; i < 40 ; i++)
    {
        ShowWindow(past[i],SW_HIDE);
    }

    ShowWindow(hbutt_exit,SW_SHOW);
    SendMessageW(hBg,STM_SETIMAGE,IMAGE_BITMAP,(LPARAM)hGameoverImg);
}