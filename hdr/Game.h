#ifndef GAME_H
#define GAME_H

#include "Header.h"

class Game{
public:
	Interface * itf = NULL;
	Player * white = NULL, * black = NULL;
	Trongtai * trongtai = NULL;
	ChessBoard * chessBoard = NULL;
	History * history;
	Pointer * pointer;
public:
	int turn;
	bool isEnd;
	Player * winner, * currentPlayer;
public:
	Game();
public:
	void init();
	void start();
	void quit();
	void back();
	void win(Player * player);
	void draw();
};

#endif
