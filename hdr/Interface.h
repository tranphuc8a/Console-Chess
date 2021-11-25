#ifndef INTERFACE_H
#define INTERFACE_H

#include "Header.h"

class Interface{
public:
	vector<string> chessBoard;
	int x, y;
public:
	Game * game;
public:
	Interface();
	Interface(Game * game);
public:
	void free();
	void update();
	void show();
	void show(int x, int y, string content);
	void show(string content, int x, int y);
	void showChessBoard();
	void showForm();
	void showHistory();
	void showMove(Move * mv);
	void removeLastMove();
	void getMove();
	void showWin(int team);
	void showDraw();
};

#endif
