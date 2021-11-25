#ifndef TOT_H
#define TOT_H

#include "Header.h"

class Tot : public Piece{
public:
	Tot();
	Tot(Player * player);
	Tot(Player * player, int r, int c);
public:
	Move * move(int tr, int tc) override;
	Move * eat(int tr, int tc);
	Move * eatRoad(int tr, int tc);
	string getClassName() override;
	vector<Point> target() override;
	vector<Point> kiemsoat() override;
	bool isKiemsoat(int x, int y) override;
	bool isTarget(int x, int y) override;
};

#endif
