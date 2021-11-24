#include "SubHeader.h"

Tot::Tot() : Piece(){}
Tot::Tot(Player * player) : Piece(player) {}
Tot::Tot(Player * player, int r, int c) : Piece(player, r, c){}

Move* Tot::move(int tr, int tc) {
	// move binh thuong, khong phai phong cap
	// eat:
	if (tc != c){
		return eat(tr, tc);
	}
	// go straight:
	int lr = r, lc = c;
	auto &table = chessBoard->piece;
	table[r][c] = NULL;
	table[tr][tc] = this;
	show(tr, tc);
	r = tr, c = tc;
	cntMove++;
	return new Move(0, this, lr, lc, r, c, Move::NORM);
}

Move * Tot::eat(int tr, int tc){
	auto &table = chessBoard->piece;
	if (table[tr][tc] == NULL) return eatRoad(tr, tc);
	// normal eat:
	Piece * select = table[tr][tc];
	select->isDie = 1;
	Move * mv = new Move(0, this, r, c, tr, tc, Move::KILL);
	mv->setKillBear(select, NULL);
	table[tr][tc] = this;
	table[r][c] = NULL;
	show(tr, tc);
	r = tr, c = tc;
	cntMove++;
	return mv;
}
Move * Tot::eatRoad(int tr, int tc){
	// an tot qua duong
	auto &table = chessBoard->piece;
	Piece * select = table[r][tc];
	select->isDie = 1;
	Move * mv = new Move(0, this, r, c, tr, tc, Move::SKILL);
	mv->setKillBear(select, NULL);
	table[tr][tc] = this;
	table[r][c] = NULL;
	table[r][tc] = NULL;
	select->show(-1, -1);
	show(tr, tc);
	r = tr, c = tc;
	cntMove++;
	return mv;
}
string Tot::getClassName(){
	return "i";
}


vector<Point> Tot::target(){
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
vector<Point> Tot::kiemsoat(){
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
bool Tot::isKiemsoat(int x, int y) { // can eat viral's king at (x, y)?
	if (isDie || !inBound(x, y)) return false;
	if (x == r && y == c) return false;
	auto &table = chessBoard->piece;
	if (team == Player::WHITE){
		return x + 1 == r && (c - 1 == y || c + 1 == y);
	} 
	return x - 1 == r && (c - 1 == y || c + 1 == y);
}
bool Tot::isTarget(int x, int y) { // co thi di den o (x, y) hay khong?
	if (!inBound(x, y)) return false;
	if (isDie) return false;
	auto &table = chessBoard->piece;
	if (y == c){ // di thang:
		// kiem tra abs(x - c) <= 2 && khong vuong quan nao
		if (table[x][y] != NULL) return false;
		if (team == Player::WHITE){
			if (x >= r || x + 2 < r) return false;
			if (x + 2 == r && table[x + 1][r] != NULL) return false; 
		} else {
			if (x <= r || x - 2 > r) return false;
			if (x - 2 == r && table[x - 1][r] != NULL) return false;
		}
		// cho di thu va kiem tra vua khong bi checking:
		// luu bien truoc khi thu
		auto l1 = table[r][c], l2 = table[x][y];
		// di thu:
		table[x][y] = this, table[r][c] = NULL;
		bool ok = !vua->beChecking();
		// phuc hoi:
		table[x][y] = l2, table[r][c] = l1;
		return ok;
	}
	// an cheo:
	if (!isKiemsoat(x, y)) return false;
	Piece* select = table[x][y];
	if (select == NULL){ // an tot qua duong:
		Move * befMove = player->game->history->top();
		if (befMove == NULL) return false;
		Piece * lastPiece = befMove->piece;
		if (lastPiece->getClassName() != "i") return false;
		if (lastPiece->cntMove != 1) return false;
		if (lastPiece->r != r || lastPiece->c != y) return false;
		return true;
	} else {
		// cung team:
		if (select->team == team) return false;
		// cho di thu va kiem tra vua khong bi checking:
		// luu bien truoc khi thu
		auto l1 = table[r][c], l2 = table[x][y];
		// di thu:
		l2->isDie = 1;
		table[x][y] = this, table[r][c] = NULL;
		bool ok = !vua->beChecking();
		// phuc hoi:
		l2->isDie = 0;
		table[x][y] = l2, table[r][c] = l1;	
		return ok;
	}
}
