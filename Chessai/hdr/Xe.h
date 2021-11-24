#ifndef XE_H
#define XE_H

#include "Header.h"

class Xe : public Piece{
public:
	static vector<Point> cango;
public:
	Xe();
	Xe(Player * player);
	Xe(Player * player, int r, int c);
public:
	Move * move(int tr, int tc) override;
	string getClassName() override;
	vector<Point> target() override;
	vector<Point> kiemsoat() override;
	bool isKiemsoat(int x, int y) override;
	bool isTarget(int x, int y) override;
};

#endif
