#ifndef MOVE_H
#define MOVE_H

#include "Header.h"

class Move{
public:
	enum MOVE{
		NORM, KILL, INN, UPP, SKILL
	};
//	static const int NORM;
//	static const int KILL;
//	static const int INN;
//	static const int UPP;
//	static const int SKILL;
public:
	int id;
	Piece * piece;
	int sr, sc, tr, tc;
	Piece * kill, * bear;
	int type;
	string src, tg;
public:
	Move();
	Move(int id, Piece * piece, int sr, int sc, int tr, int tc, int type);
	void setKillBear(Piece *, Piece *);
};

#endif
