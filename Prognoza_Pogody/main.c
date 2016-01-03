#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#include <string.h>
#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <iphlpapi.h>
#include <stdio.h>

#pragma comment(lib, "libws2_32.a")

#define BUFFERSIZE 1024
#define Label 	  99
#define B_Option1 100
#define B_Option2 101
#define B_Option3 102
#define TI_Edit   103 //Kraj
#define TI_Edit1   110 //Miasto
#define Closing   104
#define Closing2  104
#define Chconn    105

	WNDCLASSEX wc1;
	WNDCLASSEX wc2;
	HWND hwnd;
	HWND hwnd2;
	HWND hwnd3;
	HANDLE Handle_Of_Thread_1 = 0;

int FunkcjaConnectowa(){
	char buffer1[1024];
	WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2,2), &wsaData) != 0) {
        MessageBox(NULL, buffer1,"WSA startup failed",MB_ICONINFORMATION|MB_OK);
        system("pause");
        return 1;
    }
    SOCKET Socket=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
    struct hostent *host;
    host = gethostbyname("api.wunderground.com");
    SOCKADDR_IN SockAddr;
    SockAddr.sin_port=htons(80);
    SockAddr.sin_family=AF_INET;
    SockAddr.sin_addr.s_addr = *((unsigned long*)host->h_addr);
     //MessageBox(NULL, buffer1,"Connecting",MB_ICONINFORMATION|MB_OK);
    if(connect(Socket,(SOCKADDR*)(&SockAddr),sizeof(SockAddr)) != 0){
        MessageBox(NULL, buffer1,"Could not connect",MB_ICONINFORMATION|MB_OK);
        system("pause");
        return 1;
    }
    //MessageBox(NULL, buffer1,"Connected",MB_ICONINFORMATION|MB_OK);
    //send(Socket,"GET / HTTP/1.1\r\nHost: api.wunderground.com/api/5df3f8dcf842e4e7/geolookup/conditions/forecast/q/Poland/Warsaw.json\r\nConnection: close\r\n\r\n", strlen("GET / HTTP/1.1\r\nHost: api.wunderground.com/api/5df3f8dcf842e4e7/geolookup/conditions/forecast/q/Poland/Warsaw.json\r\nConnection: close\r\n\r\n"),0);
    send(Socket,"GET / HTTP/1.1\r\nHost: api.wunderground.com\r\nConnection: close\r\n\r\n", strlen("GET / HTTP/1.1\r\nHost: api.wunderground.com\r\nConnection: close\r\n\r\n"),0);
    
	char buffer[7000];
    int nDataLength;
    
   // MessageBox(NULL, buffer,"test2",MB_ICONINFORMATION|MB_OK);
    while ((nDataLength = recv(Socket,buffer,7000,0)) > 0){        
        //int i = 0;
        MessageBox(NULL, buffer, "Connecting",MB_ICONINFORMATION|MB_OK);
        /*while (buffer[i] >= 32 || buffer[i] == '\n' || buffer[i] == '\r') {
            MessageBox(NULL, buffer, "Connecting",MB_ICONINFORMATION|MB_OK);
            i += 1;
        }*/
    }
    closesocket(Socket);
        WSACleanup();
}

LRESULT OnPaint(HWND hwnd){
	PAINTSTRUCT ps;
	HDC hdc;
	int l=0;
	//static int x,y;

	hdc = BeginPaint(hwnd, &ps);
	RECT rect;
	GetClientRect(hwnd, &rect);
	
	HBRUSH brush = CreateSolidBrush(RGB(0,0,255));
	//FillRect(hdc, &rect, brush);
	SelectObject(hdc, brush);
	
	
	//Rainy claud
	Ellipse(hdc ,200,150,250,200 );
	Ellipse(hdc ,230,150,280,200 );
	Ellipse(hdc ,260,150,310,200 );
	Ellipse(hdc ,290,150,340,200 );
	l+=10;//+l
	Ellipse(hdc ,200+l,150+l,250+l,200 +l);
	Ellipse(hdc ,230+l,150+l,280+l,200 +l);
	Ellipse(hdc ,260+l,150+l,310+l,200+l );
	Ellipse(hdc ,290+l,150+l,340+l,200+l );
	MoveToEx(hdc, rect.left + 210, rect.top + 220, NULL);
	LineTo(hdc, rect.left + 210, rect.top + 250);
	MoveToEx(hdc, rect.left + 230, rect.top + 220, NULL);
	LineTo(hdc, rect.left + 230, rect.top + 250);
	MoveToEx(hdc, rect.left + 250, rect.top + 220, NULL);
	LineTo(hdc, rect.left + 250, rect.top + 250);
	MoveToEx(hdc, rect.left + 270, rect.top + 220, NULL);
	LineTo(hdc, rect.left + 270, rect.top + 250);
	MoveToEx(hdc, rect.left + 290, rect.top + 220, NULL);
	LineTo(hdc, rect.left + 290, rect.top + 250);
	MoveToEx(hdc, rect.left + 310, rect.top + 220, NULL);
	LineTo(hdc, rect.left + 310, rect.top + 250);
	MoveToEx(hdc, rect.left + 330, rect.top + 220, NULL);
	LineTo(hdc, rect.left + 330, rect.top + 250);
	
	EndPaint(hwnd, &ps);
	DeleteObject(brush);
}
	
void GenerateButtonsAuthors(HWND parent, HINSTANCE hInstance){
	
	//static HWND hwnd_ed_u;
	CreateWindow(TEXT("STATIC"), TEXT("Mamy nastepuj1cy sk3ad:"),
                              WS_CHILD | WS_VISIBLE ,
                              50, 10, 200, 25,
                              parent, (HMENU)(502),
                              hInstance, NULL);
							  	
	CreateWindow(TEXT("STATIC"), TEXT("in?. Piotr Zyszczak"),
                              WS_CHILD | WS_VISIBLE ,
                              50, 50, 200, 25,
                              parent, (HMENU)(502),
                              hInstance, NULL);
                              
    CreateWindow(TEXT("STATIC"), TEXT("in? Damian Lukasik"),
                              WS_CHILD | WS_VISIBLE ,
                              50, 90, 200, 25,
                              parent, (HMENU)(502),
                              hInstance, NULL);    
                              
    CreateWindow(TEXT("STATIC"), TEXT("in? Artur Snioszek"),
                              WS_CHILD | WS_VISIBLE ,
                              50, 130, 200, 25,
                              parent, (HMENU)(502),
                              hInstance, NULL);  
                              
	CreateWindowEx(WS_EX_CLIENTEDGE,"Button","Zamknij",WS_VISIBLE|WS_CHILD|BS_PUSHBUTTON,
		50, /* x */
		170, /* y */
		130, /* width */
		30, /* height */
		parent,(HMENU)Closing,hInstance,NULL);                      
}

void GenerateButtonsWeather(HWND parent, HINSTANCE hInstance){
	
	//static HWND hwnd_ed_u;
	CreateWindow(TEXT("STATIC"), TEXT("Wpisz misto/kraj z którego chcesz pogode:"),
                              WS_CHILD | WS_VISIBLE ,
                              50, 10, 300, 25,
                              parent, (HMENU)(502),
                              hInstance, NULL);
                              
    CreateWindowEx(WS_EX_CLIENTEDGE,"EDIT","Kraj",WS_VISIBLE|WS_CHILD|WS_VSCROLL|ES_MULTILINE|ES_AUTOVSCROLL|ES_CENTER,
		50, /* x */
		50, /* y */
		300, /* width */
		25, /* height */
		parent,(HMENU)TI_Edit,hInstance,NULL);
		
	CreateWindowEx(WS_EX_CLIENTEDGE,"EDIT","Miasto",WS_VISIBLE|WS_CHILD|WS_VSCROLL|ES_MULTILINE|ES_AUTOVSCROLL|ES_CENTER,
		50, /* x */
		90, /* y */
		300, /* width */
		25, /* height */
		parent,(HMENU)TI_Edit1,hInstance,NULL);	
    
	CreateWindowEx(WS_EX_CLIENTEDGE,"Button","Zamknij",WS_VISIBLE|WS_CHILD|BS_PUSHBUTTON,
		50, /* x */
		140, /* y */
		130, /* width */
		30, /* height */
		parent,(HMENU)Closing2,hInstance,NULL);
		
	CreateWindowEx(WS_EX_CLIENTEDGE,"Button","Sprawd? pogode",WS_VISIBLE|WS_CHILD|BS_PUSHBUTTON,
		200, /* x */
		140, /* y */
		149, /* width */
		30, /* height */
		parent,(HMENU)Chconn,hInstance,NULL);                           
}

/* This is where all the input to the window goes to */
LRESULT CALLBACK WndProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam) {
	switch(Message) {
		//LPCTSTR Caption = L"Application Programming Interface";
		/* Upon destruction, tell the main thread to stop */
		case WM_CLOSE: {
			switch(MessageBox(NULL, "Chcesz zamkn1a?","Zamykanie?",MB_ICONQUESTION|MB_YESNO)){
						case IDYES:{
							PostQuitMessage(0);
							break;
						}
						case IDNO:{
							MessageBox(NULL, "Nie!","Ups",MB_ICONINFORMATION|MB_OK);
							break;
						}
			}
			break;
		}
		
		case WM_COMMAND: {
			switch(wParam) {
				case B_Option1: {
				
				ShowWindow(hwnd2,SW_SHOW);	
					
					break;
				}
				case B_Option2: {
					
				ShowWindow(hwnd3,SW_SHOW);	
				
					break;	
				}
				case B_Option3: {
					switch(MessageBox(NULL, "Chcesz zamkn1a?","Zamykanie?",MB_ICONQUESTION|MB_YESNO)){
						case IDYES:{
							PostQuitMessage(0);
							break;
						}
						case IDNO:{
							MessageBox(NULL, "Nie!","Odmowa",MB_ICONINFORMATION|MB_OK);
							break;
						}
					break;
					}
				}
				default: {
					break;
				}
			}
			break;
		}
		case WM_PAINT: {
			OnPaint(hwnd);
			break;
		}
		
		/* All other messages (a lot of them) are processed using default procedures */
		default:
			return DefWindowProc(hwnd, Message, wParam, lParam);
	}
	return 0;
}

void GenerateButtons(HWND parent, HINSTANCE hInstance){
	
	//static HWND hwnd_ed_u;
	
	CreateWindow(TEXT("STATIC"), TEXT("Witaj w programie Prognoza Pogody."),
                              WS_CHILD | WS_VISIBLE ,
                              10, 10, 350, 25,
                              parent, (HMENU)(502),
                              hInstance, NULL);
		
	CreateWindowEx(WS_EX_CLIENTEDGE,"Button","Wyszukaj Pogode",WS_VISIBLE|WS_CHILD|BS_PUSHBUTTON,
		50, /* x */
		50, /* y */
		130, /* width */
		30, /* height */
		parent,(HMENU)B_Option1,hInstance,NULL);
	
	CreateWindowEx(WS_EX_CLIENTEDGE,"Button","Autorzy",WS_VISIBLE|WS_CHILD|BS_PUSHBUTTON,
		50, /* x */
		90, /* y */
		70, /* width */
		30, /* height */
		parent,(HMENU)B_Option2,hInstance,NULL);
		
	CreateWindowEx(WS_EX_CLIENTEDGE,"Button","Koniec",WS_VISIBLE|WS_CHILD|BS_PUSHBUTTON,
		50, /* x */
		130, /* y */
		70, /* width */
		30, /* height */
		parent,(HMENU)B_Option3,hInstance,NULL);
}

LRESULT CALLBACK WndProc1(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam) {
	int Data_Of_Thread_1 = 1;
	HANDLE Array_Of_Thread_Handles[3];
	switch(Message) {
		
		/* Upon destruction, tell the main thread to stop */
		case WM_CLOSE: {
			switch(MessageBox(NULL, "Chcesz zamkn1a?","Zamykanie?",MB_ICONQUESTION|MB_YESNO)){
						case IDYES:{
							ShowWindow(hwnd,SW_HIDE);
							break;
						}
						case IDNO:{
							MessageBox(NULL, "Nie!","Ups",MB_ICONINFORMATION|MB_OK);
							break;
						}
			}
			break;
		}
		
		case WM_COMMAND: {
			switch(wParam) {
				case Closing2: {
					ShowWindow(hwnd,SW_HIDE);
					//MessageBox(NULL, "Nie!","Odmowa",MB_ICONINFORMATION|MB_OK);
					break;
				}
				case Chconn: {
					HANDLE Handle_Of_Thread_1 = CreateThread( NULL, 0,FunkcjaConnectowa, &Data_Of_Thread_1, 0, NULL);
					Array_Of_Thread_Handles[0] = Handle_Of_Thread_1;
					WaitForMultipleObjects( 3, Array_Of_Thread_Handles, TRUE, INFINITE);
					CloseHandle(Handle_Of_Thread_1);
					//MessageBox(NULL, "Nie!","Odmowa",MB_ICONINFORMATION|MB_OK);
					break;
				}
			}
			break;
		}
		
		/* All other messages (a lot of them) are processed using default procedures */
		default:
			return DefWindowProc(hwnd, Message, wParam, lParam);
	}
	return 0;
}

LRESULT CALLBACK WndProc2(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam) {
	switch(Message) {
		
		/* Upon destruction, tell the main thread to stop */
		//Tu jest bug trzeba przechwycia zdarzenie zanim zamknie sie okno
		case WM_CLOSE: {
			switch(MessageBox(NULL, "Chcesz zamkn1a?","Zamykanie?",MB_ICONQUESTION|MB_YESNO)){
						case IDYES:{
							ShowWindow(hwnd,SW_HIDE);
							break;
						}
						case IDNO:{
							MessageBox(NULL, "Nie!","Ups",MB_ICONINFORMATION|MB_OK);
							break;
						}
					}
			break;
		}
		
		case WM_COMMAND: {
			switch(wParam) {
				case Closing: {
					ShowWindow(hwnd,SW_HIDE);
					//MessageBox(NULL, "Nie!","Odmowa",MB_ICONINFORMATION|MB_OK);
					break;
				}
			}
			break;
		}
		
		/* All other messages (a lot of them) are processed using default procedures */
		default:
			return DefWindowProc(hwnd, Message, wParam, lParam);
	}
	return 0;
}

/* The 'main' function of Win32 GUI programs: this is where execution starts */
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	WNDCLASSEX wc; /* A properties struct of our window */
	MSG msg; /* A temporary location for all messages */

	/* zero out the struct and set the stuff we want to modify */
	memset(&wc,0,sizeof(wc));
	wc.cbSize		 = sizeof(WNDCLASSEX);
	wc.lpfnWndProc	 = WndProc; /* This is where we will send messages to */
	wc.hInstance	 = hInstance;
	wc.hCursor		 = LoadCursor(NULL, IDC_ARROW);
	
	/* White, COLOR_WINDOW is just a #define for a system color, try Ctrl+Clicking it */
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
	wc.lpszClassName = "WindowClass";
	wc.hIcon		 = LoadIcon(NULL, IDI_APPLICATION); /* Load a standard icon */
	wc.hIconSm		 = LoadIcon(NULL, IDI_APPLICATION); /* use the name "A" to use the project icon */
	
/* zero out the struct and set the stuff we want to modify */
					memset(&wc1,0,sizeof(wc1));
					wc1.cbSize		 = sizeof(WNDCLASSEX);
					wc1.lpfnWndProc	 = WndProc1; /* This is where we will send messages to */
					wc1.hInstance	 = hInstance;
					wc1.hCursor		 = LoadCursor(NULL, IDC_ARROW);
	
					/* White, COLOR_WINDOW is just a #define for a system color, try Ctrl+Clicking it */
					wc1.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
					wc1.lpszClassName = "WindowClass1";
					wc1.hIcon		 = LoadIcon(NULL, IDI_APPLICATION); /* Load a standard icon */
					wc1.hIconSm		 = LoadIcon(NULL, IDI_APPLICATION); /* use the name "A" to use the project icon */
					
					/* zero out the struct and set the stuff we want to modify */
					memset(&wc2,0,sizeof(wc2));
					wc2.cbSize		 = sizeof(WNDCLASSEX);
					wc2.lpfnWndProc	 = WndProc2; /* This is where we will send messages to */
					wc2.hInstance	 = hInstance;
					wc2.hCursor		 = LoadCursor(NULL, IDC_ARROW);
	
					/* White, COLOR_WINDOW is just a #define for a system color, try Ctrl+Clicking it */
					wc2.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
					wc2.lpszClassName = "WindowClass2";
					wc2.hIcon		 = LoadIcon(NULL, IDI_APPLICATION); /* Load a standard icon */
					wc2.hIconSm		 = LoadIcon(NULL, IDI_APPLICATION); /* use the name "A" to use the project icon */


	
	if(!RegisterClassEx(&wc)) {
		MessageBox(NULL, "Window Registration Failed!","Error!",MB_ICONEXCLAMATION|MB_OK);
		return 0;
	}
	
	if(!RegisterClassEx(&wc1)) {
		MessageBox(NULL, "Window Registration Failed!","Error!",MB_ICONEXCLAMATION|MB_OK);
		return 0;
	}
	
	if(!RegisterClassEx(&wc2)) {
		MessageBox(NULL, "Window Registration Failed!","Error!",MB_ICONEXCLAMATION|MB_OK);
		return 0;
	}
	
	hwnd = CreateWindowEx(WS_EX_CLIENTEDGE,"WindowClass","Okno g3ówne",WS_VISIBLE|WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, /* x */
		CW_USEDEFAULT, /* y */
		420, /* width */
		350, /* height */
		NULL,NULL,hInstance,NULL);

	if(hwnd == NULL) {
		MessageBox(NULL, "Window Creation Failed!","Error!",MB_ICONEXCLAMATION|MB_OK);
		return 0;
	}
	
	hwnd2 = CreateWindowEx(WS_EX_CLIENTEDGE,"WindowClass1","Prognoza",WS_VISIBLE|WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, /* x */
		CW_USEDEFAULT, /* y */
		420, /* width */
		350, /* height */
		NULL,NULL,hInstance,NULL);

	if(hwnd2 == NULL) {
		MessageBox(NULL, "Window Creation Failed!","Error!",MB_ICONEXCLAMATION|MB_OK);
		return 0;
	}
	
	hwnd3 = CreateWindowEx(WS_EX_CLIENTEDGE,"WindowClass2","Autorzy",WS_VISIBLE|WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, /* x */
		CW_USEDEFAULT, /* y */
		420, /* width */
		350, /* height */
		NULL,NULL,hInstance,NULL);

	if(hwnd3 == NULL) {
		MessageBox(NULL, "Window Creation Failed!","Error!",MB_ICONEXCLAMATION|MB_OK);
		return 0;
	}

	GenerateButtons(hwnd, hInstance);
	GenerateButtonsWeather(hwnd2, hInstance);
	GenerateButtonsAuthors(hwnd3, hInstance);
	
	ShowWindow(hwnd2,SW_HIDE);
	ShowWindow(hwnd3,SW_HIDE);

	/*
		This is the heart of our program where all input is processed and 
		sent to WndProc. Note that GetMessage blocks code flow until it receives something, so
		this loop will not produce unreasonably high CPU usage
	*/
	while(GetMessage(&msg, NULL, 0, 0) > 0) { /* If no error is received... */
		TranslateMessage(&msg); /* Translate key codes to chars if present */
		DispatchMessage(&msg); /* Send it to WndProc */
	}
	return msg.wParam;
}
