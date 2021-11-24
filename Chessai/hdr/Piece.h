#ifndef PIECE_H
#define PIECE_H

#include "Header.h"

class Piece{
public:
	int id;
	Vua * vua;
	int r, c;
	Player * player;
	
	int cntMove;
	bool isDie;
	int team;
	ChessBoard* chessBoard;
public:
	Piece();
	Piece(Player * player);
	Piece(Player * player, int r, int c);

public:
	virtual Move * move(int tr, int tc) = 0;
	virtual string getClassName() = 0;
	virtual vector<Point> target() = 0;
	virtual vector<Point> kiemsoat() = 0;
	virtual bool isKiemsoat(int x, int y) = 0;
	virtual bool isTarget(int x, int y) = 0;
	void setPoint(int x, int y);
	void show(int tr, int tc);
	bool inBound(int x, int y);
	// kiemsoat: vi tri ma neu vua doi phuong dat o do, this co the an ngay
	// target: vi tri ma this co the di chuyen den (co the di chuyen thuong, co the an)
};

#endif
