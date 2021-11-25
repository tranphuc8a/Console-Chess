#ifndef SYSTEM_H
#define SYSTEM_H

#include <bits/stdc++.h>
#include <windows.h>

using namespace std;

#define MAX 1000

class SYSTEM
{
public:
	void clrscr();
	void SetColor(int x);
	void SetColor(int letter, int background);
	void gotoXY(int, int);
//	void Goto(Toado);
	void Srand();
	int Random();
	void HidePtr();
	void ShowPtr();
};

enum Event{
	NONE,
	
	number_0 = 48, 	number_1, number_2, number_3, number_4, 
	number_5, 		number_6, number_7, number_8, number_9,
	
	KEY_A = 97, KEY_B, KEY_C, KEY_D, KEY_E, KEY_F, KEY_G, 
				KEY_H, KEY_I, KEY_J, KEY_K, KEY_L, KEY_M, KEY_N, 		
				KEY_O, KEY_P, KEY_Q, KEY_R, KEY_S, KEY_T, KEY_U, 
				KEY_V, KEY_W, KEY_X, KEY_Y, KEY_Z,
				
	BACKSPACE 	= 	8,
	TAB			= 	9,
	ENTER 		= 	13,
	ESC 		= 	27,
	SPACE 		= 	32,
	UP 			= 	72,
	LEFT 		= 	75,
	RIGHT 		= 	77,
	DOWN 		= 	80
};

enum Color{
	BLACK 		= 0,
	NAVY  		= 1,
	GREEN		= 2,
	TEAL		= 3,
	MAROON		= 4,
	PURPLE		= 5,
	OLIVE		= 6,
	SILVER		= 7,
	GRAY		= 8,
	BLUE		= 9,
	LIME		= 10,
	AQUA		= 11,
	RED			= 12,
	FUCHSIA		= 13,
	YELLOW		= 14,
	WHITE		= 15
};

#endif
