#ifndef HISTORY_H
#define HISTORY_H

#include "Header.h"

class History{
public:
	vector<Move *> move;
public:
	History();
public:
	void push(Move *);
	Move * pop();
	Move * top();
	int size();
	bool empty();
	void free();
};

#endif
