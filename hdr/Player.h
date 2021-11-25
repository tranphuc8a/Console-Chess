#ifndef PLAYER_H
#define PLAYER_H

#include "Header.h"

class Player{
public:
	static int WHITE;
	static int BLACK;
	int team;
	Game * game;
	
	vector<Piece * > piece;
	Player * rival;
public:
	Player();
public:
	void free();
	void initPiece();
	virtual void move() = 0;
	bool contains(Piece * p);
};

#endif
