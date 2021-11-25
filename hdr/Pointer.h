#ifndef POINTER_H
#define POINTER_H

#include "Header.h"

class Pointer{
	enum{
		UP, DOWN, LEFT, RIGHT
	};
	Point current;
	Game * game;
	ChessBoard * chessBoard;
	Piece * select;
public:
	Pointer();
	Pointer(Game * game);
public:
	void hide();
	void show(int x, int y);
	Move * enter();
	void turn(int direct);
	void getMove();
	char getPhongcap();
};

#endif
