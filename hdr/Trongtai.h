#ifndef TRONGTAI_H
#define TRONGTAI_H

#include "Header.h"

class Trongtai{
public:
	static int NORM;
	static int MATE;
	static int DRAW;
public:
	Game * game;
	string quan = "hHxXtTmM";
public:
	Trongtai();
	Trongtai(Game * game);
public:
	void free();
	bool checkNuocdi(string&, string&);
	int checkMate(Player * player);
};

#endif
