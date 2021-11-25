#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#include "Header.h"

class ChessBoard{
public:
	vector<vector<Piece *>> piece;
	Game * game;
public:
	ChessBoard();
	ChessBoard(Game * game);
public:
	void free();
	// for input by pointer:
	Move * phongcap(Piece * select, int tr, int tc);
	Move * move(int sr, int sc, int tr, int tc);
	// for input by interface:
	Move * move(string src, string tg);
	Move * phongcap(Piece * select, int tr, int tc, char newPiece);
};


#endif
