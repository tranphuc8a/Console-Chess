#ifndef VUA_H
#define VUA_H

#include "Header.h"

class Vua : public Piece{
public:
	static vector<Point> cango;
public:
	Vua();
	Vua(Player * player);
	Vua(Player * player, int r, int c);
public:
	Move * move(int tr, int tc) override;
	Move * nhapthanh(int tr, int tc);
	bool beChecking();
	vector<Piece *> getChecking();
	string getClassName() override;
	vector<Point> target() override;
	vector<Point> kiemsoat() override;
	bool isKiemsoat(int x, int y) override;
	bool isTarget(int x, int y) override;
	bool canNhapthanhtrai();
	bool canNhapthanhphai();
	
};

#endif
