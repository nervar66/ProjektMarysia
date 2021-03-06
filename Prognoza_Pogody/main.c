
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#include <string.h>
#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <iphlpapi.h>
#include <sqltypes.h>
#include <sql.h> 
#include <sqlext.h>

#pragma comment(lib, "libws2_32.a")
#pragma comment(lib, "libodbc32.a")
#pragma comment(lib, "libodbccp32.a")

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
#define DBtest    106

	WNDCLASSEX wc1;
	WNDCLASSEX wc2;
	HWND hwnd;
	HWND hwnd2;
	HWND hwnd3;
	HANDLE Handle_Of_Thread_1 = 0;
	HWND hText,hText2;
	CRITICAL_SECTION g_Section;
	int StatusWatek1=-1;   
	CRITICAL_SECTION g_Section1;
	int StatusWatek2=-1;
		
		
		
	char buffer1[1024];
	char buffer_w1[100000]; // dane z watku1 
	char dest_buf_w2[500]; // dane z watku2
	SQLCHAR message_w2[500]; // komunikat bledu w2
int FunkcjaConnectowa(){
	
	char buffer[100000];
	buffer[0] = 0;
	
	
	char *mess;
	
	WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2,2), &wsaData) != 0) {
       // MessageBox(NULL, "dsa","WSA startup failed",MB_ICONINFORMATION|MB_OK);
        EnterCriticalSection( & g_Section );
	 	StatusWatek1=4;
	 	LeaveCriticalSection( & g_Section );
        system("pause");
        return 1;
    }
  
    SOCKET Socket=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
    struct hostent *host;
    
    host = gethostbyname("api.wunderground.com");
    if(host != NULL){
    }
    else{
		EnterCriticalSection( & g_Section );
	 	StatusWatek1=7;
	 	LeaveCriticalSection( & g_Section );
	 	system("pause");
	 	return 1;}
	//WSACleanup();

    SOCKADDR_IN SockAddr;
    SockAddr.sin_port=htons(80);
    SockAddr.sin_family=AF_INET;
    SockAddr.sin_addr.s_addr = *((unsigned long*)host->h_addr);
    
    if(connect(Socket,(SOCKADDR*)(&SockAddr),sizeof(SockAddr)) != 0){
        EnterCriticalSection( & g_Section );
	 	StatusWatek1=3;
	 	LeaveCriticalSection( & g_Section );
        system("pause");
        return 1;
    }
    
   	DWORD dlugosc = GetWindowTextLength( hText );
	LPSTR Bufor =( LPSTR ) GlobalAlloc( GPTR, dlugosc + 1 );
	GetWindowText( hText, Bufor, dlugosc + 1 );
	
	DWORD dlugosc2 = GetWindowTextLength( hText2 );
	LPSTR Bufor2 =( LPSTR ) GlobalAlloc( GPTR, dlugosc2 + 1 );
	GetWindowText( hText2, Bufor2, dlugosc2 + 1 );
	
	
	char* char1=(char*)Bufor;
	char* char2=(char*)Bufor2;
	char* char3= "GET /api/5df3f8dcf842e4e7/geolookup/conditions/forecast/q/";
	char* char4= "/";
	char* char5= ".json HTTP/1.1\r\nHost: api.wunderground.com\r\n\r\n";
	char dest_buf[100]; 
	wsprintf (dest_buf, "%s%s", char3, char1);
	wsprintf (dest_buf, "%s%s", dest_buf, char4);
	wsprintf (dest_buf, "%s%s", dest_buf, char2);
	wsprintf (dest_buf, "%s%s", dest_buf, char5);

	
	mess = dest_buf;
    if(send(Socket , mess , strlen(mess) , 0) < 0)
    {
        EnterCriticalSection( & g_Section );
	 	StatusWatek1=2;
	 	LeaveCriticalSection( & g_Section );
    }
	
    int nDataLength;
    
   
    while ((nDataLength = recv(Socket,buffer,2000,0)) > 0){        
        
       // MessageBox(NULL, buffer, "Connecting",MB_ICONINFORMATION|MB_OK);
        EnterCriticalSection( & g_Section );
        wsprintf (buffer_w1, "%s%s", buffer_w1, buffer);
	 	StatusWatek1=1;
	 	LeaveCriticalSection( & g_Section );
    }
    
    //EnterCriticalSection( & g_Section );
   // recv(Socket,buffer,100000,0);
    //LeaveCriticalSection( & g_Section );
    
    EnterCriticalSection( & g_Section );
  
   // wsprintf(buffer_w1, "%s%s", buffer_w1, buffer);
    StatusWatek1=0;
    LeaveCriticalSection( & g_Section );
    //wsprintf (dest_buf, "%s%s", dest_buf, char5);
    
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
	CreateWindow(TEXT("STATIC"), TEXT("Mamy nast�puj�cy sk�ad:"),
                              WS_CHILD | WS_VISIBLE ,
                              50, 10, 200, 25,
                              parent, (HMENU)(502),
                              hInstance, NULL);
							  	
	CreateWindow(TEXT("STATIC"), TEXT("in�. Piotr Zyszczak"),
                              WS_CHILD | WS_VISIBLE ,
                              50, 50, 200, 25,
                              parent, (HMENU)(502),
                              hInstance, NULL);
                              
    CreateWindow(TEXT("STATIC"), TEXT("in� Artur �nioszek"),
                              WS_CHILD | WS_VISIBLE ,
                              50, 90, 200, 25,
                              parent, (HMENU)(502),
                              hInstance, NULL);   
                              
	CreateWindow(TEXT("STATIC"), TEXT("in� Damian �ukasik"),
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
	CreateWindow(TEXT("STATIC"), TEXT("Wpisz misto/kraj z kt�rego chcesz pogod�:"),
                              WS_CHILD | WS_VISIBLE ,
                              50, 10, 300, 25,
                              parent, (HMENU)(502),
                              hInstance, NULL);
                              
   	hText = CreateWindowEx(WS_EX_CLIENTEDGE,"EDIT","Kraj",WS_VISIBLE|WS_CHILD|WS_VSCROLL|ES_MULTILINE|ES_AUTOVSCROLL|ES_CENTER,
		50, /* x */
		50, /* y */
		300, /* width */
		25, /* height */
		parent,(HMENU)TI_Edit,hInstance,NULL);
		
	hText2=CreateWindowEx(WS_EX_CLIENTEDGE,"EDIT","Miasto",WS_VISIBLE|WS_CHILD|WS_VSCROLL|ES_MULTILINE|ES_AUTOVSCROLL|ES_CENTER,
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
		
	CreateWindowEx(WS_EX_CLIENTEDGE,"Button","Sprawd� pogod�",WS_VISIBLE|WS_CHILD|BS_PUSHBUTTON,
		200, /* x */
		140, /* y */
		149, /* width */
		30, /* height */
		parent,(HMENU)Chconn,hInstance,NULL);    
		
	CreateWindowEx(WS_EX_CLIENTEDGE,"Button","Test bazy",WS_VISIBLE|WS_CHILD|BS_PUSHBUTTON,
		200, /* x */
		170, /* y */
		149, /* width */
		30, /* height */
		parent,(HMENU)DBtest,hInstance,NULL);                        
}

/* This is where all the input to the window goes to */
LRESULT CALLBACK WndProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam) {
	switch(Message) {
		/* Upon destruction, tell the main thread to stop */
		case WM_CLOSE: {
			switch(MessageBox(NULL, "Chcesz zamkn��?","Zamykanie?",MB_ICONQUESTION|MB_YESNO)){
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
					switch(MessageBox(NULL, "Chcesz zamkn��?","Zamykanie?",MB_ICONQUESTION|MB_YESNO)){
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
	CreateWindow(TEXT("STATIC"), TEXT("Witaj w programie Prognoza Pogody."),
                              WS_CHILD | WS_VISIBLE ,
                              10, 10, 350, 25,
                              parent, (HMENU)(502),
                              hInstance, NULL);
		
	CreateWindowEx(WS_EX_CLIENTEDGE,"Button","Wyszukaj Pogod�",WS_VISIBLE|WS_CHILD|BS_PUSHBUTTON,
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

void show_error(unsigned int handletype, const SQLHANDLE handle){
    SQLCHAR sqlstate[1024];
    SQLCHAR message[1024];
    if(SQL_SUCCESS == SQLGetDiagRec(handletype, handle, 1, sqlstate, NULL, message, 1024, NULL)){
    	EnterCriticalSection( & g_Section1 );
    	StatusWatek2=2;
    	wsprintf (message_w2, "%s%s", message_w2, message);
        //cout<<"Message: "<<message<<"nSQLSTATE: "<<sqlstate<<endl;
        LeaveCriticalSection( & g_Section1 );
	}	
}    

int FunkcjaBazodanowa(){
	char dest_buf[500];
	
	EnterCriticalSection( & g_Section1 );
	//dest_buf[0] = 0;
	StatusWatek2=0;
	LeaveCriticalSection( & g_Section1 );
	
    SQLHANDLE sqlenvhandle;    
    SQLHANDLE sqlconnectionhandle;
    SQLHANDLE sqlstatementhandle;
    SQLRETURN retcode;

    if(SQL_SUCCESS!=SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &sqlenvhandle))
        goto FINISHED;

    if(SQL_SUCCESS!=SQLSetEnvAttr(sqlenvhandle,SQL_ATTR_ODBC_VERSION, (SQLPOINTER)SQL_OV_ODBC3, 0)) 
        goto FINISHED;
    
    if(SQL_SUCCESS!=SQLAllocHandle(SQL_HANDLE_DBC, sqlenvhandle, &sqlconnectionhandle))
        goto FINISHED;

    SQLCHAR retconstring[1024];
    switch(SQLDriverConnect (sqlconnectionhandle, 
                NULL, 
                (SQLCHAR*)"DSN=mysqlster;", 
                SQL_NTS, 
                retconstring, 
                1024, 
                NULL,
                SQL_DRIVER_COMPLETE)){
        case SQL_SUCCESS_WITH_INFO:
            show_error(SQL_HANDLE_DBC, sqlconnectionhandle);
            break;
        case SQL_INVALID_HANDLE:
        case SQL_ERROR:
            show_error(SQL_HANDLE_DBC, sqlconnectionhandle);
            goto FINISHED;
        default:
            break;
    }
    
    if(SQL_SUCCESS!=SQLAllocHandle(SQL_HANDLE_STMT, sqlconnectionhandle, &sqlstatementhandle))
        goto FINISHED;

    if(SQL_SUCCESS!=SQLExecDirect(sqlstatementhandle, (SQLCHAR*)"select * from testtable", SQL_NTS)){
        show_error(SQL_HANDLE_STMT, sqlstatementhandle);
        goto FINISHED;
    }
    else{
        char name[64];
        char address[64];
        char id[64];
        while(SQLFetch(sqlstatementhandle)==SQL_SUCCESS){
            SQLGetData(sqlstatementhandle, 1, SQL_C_CHAR, id, 64, NULL);
            SQLGetData(sqlstatementhandle, 2, SQL_C_CHAR, name, 64, NULL);
            SQLGetData(sqlstatementhandle, 3, SQL_C_CHAR, address, 64, NULL);
            
            //EnterCriticalSection( & g_Section1 );
            wsprintf (dest_buf, "%s%s", dest_buf, id);
            wsprintf (dest_buf, "%s%s", dest_buf, name);
            wsprintf (dest_buf, "%s%s", dest_buf, address);
            
            EnterCriticalSection( & g_Section1 );
	StatusWatek2=1;
	wsprintf(dest_buf_w2, "%s%s", dest_buf_w2, dest_buf);
	LeaveCriticalSection( & g_Section1 );	
        }
    }
    
    
	
	FINISHED:
	SQLFreeHandle(SQL_HANDLE_STMT, sqlstatementhandle );
	SQLDisconnect(sqlconnectionhandle);
    SQLFreeHandle(SQL_HANDLE_DBC, sqlconnectionhandle);
    SQLFreeHandle(SQL_HANDLE_ENV, sqlenvhandle);
    
}

LRESULT CALLBACK WndProc1(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam) {
	
	
	int Data_Of_Thread_1 = 1;
	int Data_Of_Thread_2 = 1;
	HANDLE Array_Of_Thread_Handles[3];
	switch(Message) {
		
		/* Upon destruction, tell the main thread to stop */
		case WM_CLOSE: {
			switch(MessageBox(NULL, "Chcesz zamkn��?","Zamykanie?",MB_ICONQUESTION|MB_YESNO)){
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
					break;
				}
				case Chconn: {
					//InitializeCriticalSection( & g_Section );
					HANDLE Handle_Of_Thread_1 = CreateThread( NULL, 0,FunkcjaConnectowa, &Data_Of_Thread_1, 0, NULL);
					//Array_Of_Thread_Handles[0] = Handle_Of_Thread_1;
					//WaitForSingleObject( Handle_Of_Thread_1, 500);
					DWORD rs = WaitForSingleObject( Handle_Of_Thread_1, 10000);
				
					
					if(rs == WAIT_OBJECT_0)
					{
						MessageBox(NULL,"Watek zakonczyl sie","Komunikat",MB_ICONINFORMATION|MB_OK);	 
					}
					else if(rs == WAIT_TIMEOUT)
					{
						MessageBox(NULL,"Przekroczono czas","Komunikat",MB_ICONINFORMATION|MB_OK);	        		
					}
					else if(rs == WAIT_FAILED)
					{
						MessageBox(NULL,"Funkcja nie powiodla sie","Komunikat",MB_ICONINFORMATION|MB_OK);	        		
					}
					else if(rs == WAIT_ABANDONED)
					{
						MessageBox(NULL,"Blad","Komunikat",MB_ICONINFORMATION|MB_OK);	  
					}
					//MessageBox(NULL,buffer,"Watek pogodowy",MB_ICONINFORMATION|MB_OK);
				
					//DeleteCriticalSection(& g_Section);
					CloseHandle(Handle_Of_Thread_1);
						
					if (StatusWatek1==-1) {
						MessageBox(NULL,"Watek nie uruchomiony","Komunikat",MB_ICONINFORMATION|MB_OK);
					}
					else if (StatusWatek1==0) {
						MessageBox(NULL,"Zakonczono pobieranie","Komunikat",MB_ICONINFORMATION|MB_OK);
					}
					else if (StatusWatek1==1) {
						MessageBox(NULL,"Nadal pobieram dane","Komunikat",MB_ICONINFORMATION|MB_OK);
					}
					else if(StatusWatek1==2) {
						MessageBox(NULL,"Wysylam zapytanie","Komunikat",MB_ICONINFORMATION|MB_OK);
					}
					else if(StatusWatek1==3) {
						MessageBox(NULL,"Blad w funkcji connect","Komunikat",MB_ICONINFORMATION|MB_OK);
					}
					else if(StatusWatek1==4) {
						MessageBox(NULL,"Blad inicjacji wsastartup","Komunikat",MB_ICONINFORMATION|MB_OK);
					}
					else if(StatusWatek1==7) {
						MessageBox(NULL,"Nie ma Internetu","Komunikat",MB_ICONINFORMATION|MB_OK);
					}
					MessageBox(NULL,buffer_w1,"Komunikat",MB_ICONINFORMATION|MB_OK);
					memset(buffer_w1, 0, sizeof buffer_w1);
					break;
				}
				
				case DBtest: {
					//InitializeCriticalSection( & g_Section1 );
					HANDLE Handle_Of_Thread_2 = CreateThread( NULL, 0,FunkcjaBazodanowa, &Data_Of_Thread_2, 0, NULL);
					if (WaitForSingleObject( Handle_Of_Thread_2,100000) !=WAIT_TIMEOUT){
					if(StatusWatek2==0){
						MessageBox(NULL, "Blad w watku!","Blad!",MB_ICONINFORMATION|MB_OK);
					}
					if(StatusWatek2==1){
						MessageBox(NULL, dest_buf_w2,"Wszystko ok!",MB_ICONINFORMATION|MB_OK);
					}
					if(StatusWatek2==2){
						MessageBox(NULL, message_w2,"Blad wdostepie do bazy!",MB_ICONINFORMATION|MB_OK);
					}
					}
        			else{
    					MessageBox(NULL,"Proces przekroczyl czas!","Wszystko ok",MB_ICONINFORMATION|MB_OK);
					}
					memset(dest_buf_w2, 0, sizeof dest_buf_w2);
					memset(message_w2, 0, sizeof message_w2);
					CloseHandle(Handle_Of_Thread_2);
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
		case WM_CLOSE: {
			switch(MessageBox(NULL, "Chcesz zamkn��?","Zamykanie?",MB_ICONQUESTION|MB_YESNO)){
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
	InitializeCriticalSection( & g_Section );
	InitializeCriticalSection( & g_Section1 );
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
	
	hwnd = CreateWindowEx(WS_EX_CLIENTEDGE,"WindowClass","Okno g��wne",WS_VISIBLE|WS_OVERLAPPEDWINDOW,
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
	DeleteCriticalSection(& g_Section);
	DeleteCriticalSection(& g_Section1);
	return msg.wParam;
}
