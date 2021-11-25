#ifndef HUMAN_H
#define HUMAN_H

#include "Header.h"

class Human : public Player{
public:
	
public:
	Human();
	Human(int team, Game * game);
public:
	void move() override;
};

#endif
