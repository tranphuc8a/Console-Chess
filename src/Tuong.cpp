#include "SubHeader.h"

Tuong::Tuong() : Piece(){}
Tuong::Tuong(Player * player) : Piece(player) {}
Tuong::Tuong(Player * player, int r, int c) : Piece(player, r, c){}

Move * Tuong::move(int tr, int tc) {
	int lr = r, lc = c;
	auto &table = chessBoard->piece;
	Piece * select = table[tr][tc];
	int type = Move::NORM;
	if (select != NULL) {
		select->isDie = 1;
		type = Move::KILL;
	}
	table[r][c] = NULL;
	table[tr][tc] = this;
	show(tr, tc);
	r = tr, c = tc;
	Move * rs = new Move(0, this, lr, lc, r, c, type);
	rs->setKillBear(select, NULL);
	return rs;
}
string Tuong::getClassName(){
	return "T";
}

vector<Point> Tuong::target(){
	vector<Point> res;
	int x, y;
	for (int a = -1; a <= 1; a+=2){
		for (int b = -1; b <= 1; b+=2){
			for (int i = 1; i <= 8; i++){
				x = r + a * i, y = c + b * i;
				if (!inBound(x, y)) break;
				if (isTarget(x, y))
					res.push_back(Point(x, y));
			}
		}
	}
	return res;
}
vector<Point> Tuong::kiemsoat(){
	vector<Point> res;
	int x, y;
	for (int a = -1; a <= 1; a += 2){
		for (int b = -1; b <= 1; b += 2){
			for (int i = 1; i <= 8; i++){
				x = r + a * i, y = c + b * i;
				if (!inBound(x, y)) break;
				if (isKiemsoat(x, y))
					res.push_back(Point(x, y));
			}
		}
	}
	return res;
}
bool Tuong::isKiemsoat(int x, int y) { // can eat viral's king at (x, y)?
	if (isDie || !inBound(x, y)) return false;
	if (x == r && y == c) return false;
	auto &table = chessBoard->piece;
	// check between this and (x, y)
	if (x - y == r - c){
		for (int i = min(x, r) + 1; i <= max(x, r) - 1; i++){
			if (table[i][i + c - r] != NULL) return false;
		}
		return true;
	}
	if (x + y == r + c){
		for (int i = min(x, r) + 1; i <= max(x, r) - 1; i++){
			if (table[i][c + r - i] != NULL) return false;
		}
		return true;
	}
	return false;
}
bool Tuong::isTarget(int x, int y) { // co thi di den o (x, y) hay khong?
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



