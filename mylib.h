
#include <conio.h>

#include <stdio.h>
#include <stdlib.h>
#include <dos.h>
#include <string.h>
#include <windows.h>

#define WIDTH 185
#define HEIGHT 45

#define COT 5
#define COTDS_L 70
#define COTDS_R 184
#define DONG 1
#define DONGTD 9
#define DONGDS_U 3
#define DONGDS_D 45

#define DONGNHAP1 12
#define DONGNHAP2 16
#define DONGNHAP3 20
#define DONGNHAP4 24
#define DONGNHAP5 28
#define DONGNHAP6 32
#define DONGNHAP7 36
#define DONGNHAP8 40
#define DONGNHAP9 44

#define MIDDLE_DOC 65
#define MIDDLE_NGANG 7
#define RONGKHUNG 2
#define DAIKHUNG 60
#define DAIKHUNGNHO 10

#define NGANG 196
#define DOC 179
#define UPLEFT 218
#define UPRIGHT 191
#define DOWNLEFT 192
#define DOWNRIGHT 217
#define BELEFT 195
#define BEUP 194
#define BERIGHT 180
#define BEDOWN 193

#define ENTER 13
#define BACKSPACE 8
#define DELETE 83
#define UP 72
#define DOWN 80
#define ESC 27
#define TAB 9
#define LEFT 75
#define RIGHT 77
#define SPACE 32
#define F2 60
#define F3 61
#define F7 65
#define F8 66
#define F9 67
#define F10 68
#define PU 73
#define PD 81
//const int WHITE=15;
#define PASSWORD "abcdef"
//const int WHITE=15;
#define TIM_MA 0
#define THEM_MB 1
#define XOA_MB 2
#define HIEUCHINH_MB 3
#define THEM_CB 1
#define XOA_CB 2
#define XOA_CB_L 112
#define HIEUCHINH_CB 3
#define HUY_CB 4
#define THEM_HK 1
#define XOA_HK 2
#define HIEUCHINH_HK 3
#define DATVE 3
#define HUYVE 2
#define GDTHEM_HK 113
#define GDTHEM_CB 111
#define LOC_CB 12
#define THONG_KE 11
#define XUAT_MB 5
#define XUAT_CB 6
#define XUAT_HK 7
#define XOA_MB 8
#define XOA_CB 9
#define XOA_HK 10
#define YES 3
#define NO 2
#define CANCEL 0

//A-Z/0-9
#define A 65
#define Z 90
#define a 97
#define z 122
#define So0 48
#define So1 49
#define So2 50
#define So3 51
#define So4 52
#define So5 53
#define So6 54
#define So9 57

char* Pwd () {
     char S[40]; int i=0;
     while ((S[i]= getch()) != ENTER ) 
     { printf ("%c", '*') ; i++ ; 
     }
     S[i]='\0';
     return S;
}

int CheckPwd () {
    int dem =0; 
    for ( dem =1 ; dem <=3 ; dem++)
    { printf( "Password :"); 
      if (strcmp(Pwd(),PASSWORD) ==0)   return 1;
      else printf ( "\nPassword sai. Hay nhap lai\n")  ; 
    }
    return 0;  
}

void gotoxy(short x,short y)
{
        HANDLE hConsoleOutput;
        COORD Cursor_an_Pos = { x,y};
        hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleCursorPosition(hConsoleOutput , Cursor_an_Pos);
}  

int wherex( void )
{
    HANDLE hConsoleOutput;
    hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO screen_buffer_info;
    GetConsoleScreenBufferInfo(hConsoleOutput, &screen_buffer_info);
    return screen_buffer_info.dwCursorPosition.X;
}

int wherey( void )
{
    HANDLE hConsoleOutput;
    hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO screen_buffer_info;
    GetConsoleScreenBufferInfo(hConsoleOutput, &screen_buffer_info);
    return screen_buffer_info.dwCursorPosition.Y;
}
void clreol( ) {
COORD coord;
DWORD written;
CONSOLE_SCREEN_BUFFER_INFO info;
GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);
coord.X = info.dwCursorPosition.X;
coord.Y = info.dwCursorPosition.Y;
FillConsoleOutputCharacter (GetStdHandle(STD_OUTPUT_HANDLE), ' ',
  info.dwSize.X - info.dwCursorPosition.X * info.dwCursorPosition.Y, coord, &written);
gotoxy (info.dwCursorPosition.X , info.dwCursorPosition.Y );
}

void SetColor(WORD color)
{
    HANDLE hConsoleOutput;
    hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_SCREEN_BUFFER_INFO screen_buffer_info;
    GetConsoleScreenBufferInfo(hConsoleOutput, &screen_buffer_info);

    WORD wAttributes = screen_buffer_info.wAttributes;
    color &= 0x000f;
    wAttributes &= 0xfff0;
    wAttributes |= color;

    SetConsoleTextAttribute(hConsoleOutput, wAttributes);
}
void SetBGColor(WORD color)
{
    HANDLE hConsoleOutput;
    hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_SCREEN_BUFFER_INFO screen_buffer_info;
    GetConsoleScreenBufferInfo(hConsoleOutput, &screen_buffer_info);

    WORD wAttributes = screen_buffer_info.wAttributes;
    color &= 0x000f;
    color <<= 4;
    wAttributes &= 0xff0f;
    wAttributes |= color;

    SetConsoleTextAttribute(hConsoleOutput, wAttributes);
}
void clrscr() {
	system("cls");
}

