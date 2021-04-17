#include <windows.h>
#include <stdio.h>

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



LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
void addControls(HWND);
void loadImages();

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
                    //SendMessageW(hLogo,STM_SETIMAGE,IMAGE_BITMAP,(LPARAM)hLogoImg);  
                    break;

                case CONNECT_AS_SPECTATOR:
                    //
                    break;
                
                case CLOSE_APP:
                    DestroyWindow(hwnd);
                    break;
            }
            break;

           

        case WM_KEYDOWN:

            switch (wParam)
            {

                case VK_W:
                    printf("w");
                    break;

                case VK_UP:
                    printf("w");
                    break;

                //-----------

                case VK_A:
                    printf("a");
                    break;

                case VK_LEFT:
                    printf("a");
                    break;

                 //-----------
                
                case VK_S:
                    printf("s");
                    break;

                case VK_DOWN:
                    printf("s");
                    break;



                 //-----------

                case VK_D:
                    printf("d");
                    break;

                case VK_RIGHT:
                    printf("d");
                    break;


                 //-----------

                 case VK_SPACE:
                    printf("space");
                    break;
                
                default:
  
                    break;
                }
            break;
  

		case WM_CLOSE:
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

    //Tittle BG
    hLogo = CreateWindowW(L"Static",NULL,WS_VISIBLE|WS_CHILD|SS_BITMAP,0,0,1280,720,hwnd,NULL,NULL,NULL);
     SendMessageW(hLogo,STM_SETIMAGE,IMAGE_BITMAP,(LPARAM)hLogoImg);    

    //Tittle buttons
    HWND hbutt_play = CreateWindowW(L"Button",NULL,WS_VISIBLE|WS_CHILD|BS_BITMAP,850,400,250,50,hwnd,(HMENU)CONNECT_AS_PLAYER,NULL,NULL);
     SendMessageW(hbutt_play,BM_SETIMAGE,IMAGE_BITMAP,(LPARAM)hPlayBImg);

    HWND hbutt_spect = CreateWindowW(L"Button",NULL,WS_VISIBLE|WS_CHILD|BS_BITMAP,850,500,250,50,hwnd,NULL,NULL,NULL);
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