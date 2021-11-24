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
	Move * move(string src, string tg);
	Move * phongcap(Piece * select, int tr, int tc, char newPiece);
};


#endif
