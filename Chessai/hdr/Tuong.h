#ifndef TUONG_H
#define TUONG_H

#include "Header.h"

class Tuong : public Piece{
public:
	Tuong();
	Tuong(Player * player);
	Tuong(Player * player, int r, int c);
public:
	Move * move(int tr, int tc) override;
	string getClassName() override;
	vector<Point> target() override;
	vector<Point> kiemsoat() override;
	bool isKiemsoat(int x, int y) override;
	bool isTarget(int x, int y) override;
};

#endif
