#include "SubHeader.h"

vector<Point> Ma::cango {
	Point(1, 2), Point(1, -2), Point(-1, 2), Point(-1, -2),
	Point(2, 1), Point(2, -1), Point(-2, 1), Point(-2, -1)
};

Ma::Ma() : Piece(){}
Ma::Ma(Player * player) : Piece(player){
};
Ma::Ma(Player * player, int r, int c) : Piece(player, r, c){
};

Move * Ma::move(int tr, int tc){
	int lr = r, lc = c;
	auto &table = player->game->chessBoard->piece;
	Piece * select = table[tr][tc];
	int type = Move::NORM;
	if (select != NULL) {
		select->isDie = 1;;
		type = Move::KILL;	
	}
	table[r][c] = NULL;
	table[tr][tc] = this;
	show(tr, tc);	
	r = tr, c = tc;
	Move * rs = new Move(0, this, lr, lc, r, c, type);
	rs->setKillBear(select, NULL);
	cntMove++;
	return rs;
};
string Ma::getClassName(){
	return "M";
};

vector<Point> Ma::target(){
	vector<Point> res;
	int x, y;
	for (auto it : Ma::cango){
		x = r + it.r, y = c + it.c;
		if (isTarget(x, y))
			res.push_back(Point(x, y));
	}
	return res;
}
vector<Point> Ma::kiemsoat(){
	vector<Point> res;
	int x, y;
	for (auto it : Ma::cango){
		x = r + it.r, y = c + it.c;
		if (isKiemsoat(x, y))
			res.push_back(Point(x, y));
	}
	return res;
}
bool Ma::isKiemsoat(int x, int y) {	// can eat viral's king at (x, y)?
	if (isDie || !inBound(x, y)) return false;
	if (x == r && y == c) return false;
	int a = abs(r - x), b = abs(c - y);
	if (a <= 0 || b <= 0) return false;
	return a + b == 3;
}
bool Ma::isTarget(int x, int y) { // co thi di den o (x, y) hay khong?
	if (!isKiemsoat(x, y)) return false;
	auto &table = chessBoard->piece;
	// o (x, y) chua quan minh dang dung:
	Piece* select = table[x][y];
	if (select != NULL && select->team == team) return false;
	
	// cho di thu va kiem tra vua khong bi checking:
	// luu bien truoc khi thu
	auto l1 = table[r][c], l2 = table[x][y];
	// di thu:
	if (l2 != NULL) l2->isDie = 1;
	table[x][y] = this, table[r][c] = NULL;
	bool ok = !vua->beChecking();
	// phuc hoi:
	if (l2 != NULL) l2->isDie = 0;
	table[x][y] = l2, table[r][c] = l1;

	return ok;
}









