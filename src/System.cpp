
#include "../hdr/System.h"

void SYSTEM::clrscr()
{
//	for (int i = 0; i<=20; i++)
//	{
//		gotoXY(i, 0);
//		for (int j = 1; j<=10; j++)
//			cout << "\t";
//		cout << endl;
//	}
//	gotoXY(0, 0);
	system("cls");
}	
void SYSTEM::SetColor(int x)
{ 
    HANDLE hConsoleColor;
    hConsoleColor = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsoleColor, x);
    // system("color " + x.to_string());
}
void SYSTEM::SetColor(int letter, int background){
	letter %= 16;
	background %= 16;
	SetColor(letter + (background << 4));
}
void SYSTEM::gotoXY(int x, int y)
{
	COORD coord;
	coord.X = y;
	coord.Y = x;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
void SYSTEM::Srand()
{
	srand((int) time(0));
}
int SYSTEM::Random()
{
	return rand();
}
void SYSTEM::HidePtr()
{
    HANDLE hOut;
    CONSOLE_CURSOR_INFO ConCurInf;
    hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    ConCurInf.dwSize = 10;
    ConCurInf.bVisible = FALSE;
    SetConsoleCursorInfo(hOut,&ConCurInf);
}
void SYSTEM::ShowPtr()
{
    HANDLE hOut;
    CONSOLE_CURSOR_INFO ConCurInf;
    hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    ConCurInf.dwSize = 10;
    ConCurInf.bVisible = TRUE;
    SetConsoleCursorInfo(hOut,&ConCurInf);
} 

//SYSTEM System;
