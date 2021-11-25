
#include "SubHeader.h"

vector<Point> Vua::cango = {
	Point(1, 0), Point(-1, 0),  Point(0, 1),  Point(0, -1), 
	Point(1, 1), Point(-1, -1), Point(1, -1), Point(-1, 1)
};

Vua::Vua() : Piece(){};
Vua::Vua(Player * player) : Piece(player){
	cntMove = 0;
	team = player->team;
	if (team == Player::WHITE){
		r = 8, c = 5;
	} else {
		r = 1, c = 5;
	}
};
Vua::Vua(Player * player, int r, int c) : Piece(player, r, c){};

Move * Vua::move(int tr, int tc) {
	// update for chessBoard, killed Piece, this piece and create a Move
	if (abs(tc - c) == 2){
		return nhapthanh(tr, tc);
	}
	Piece * select = chessBoard->piece[tr][tc];
	
	int type = Move::NORM;
	if (select != NULL) type = Move::KILL;
	Move * rs = new Move(0, this, r, c, tr, tc, type);
	
	chessBoard->piece[r][c] = NULL;
	chessBoard->piece[tr][tc] = this;
	show(tr, tc);
	r = tr, c = tc;
	
	if (select != NULL) select->isDie = true;
	rs->setKillBear(select, NULL);
	cntMove++;
	return rs;
}

Move * Vua::nhapthanh(int tr, int tc){
	auto &table = chessBoard->piece;
	int lr = r, lc = c;
	if (tc + 2 == c){ // Nhap thanh trai
		Piece * xe = chessBoard->piece[tr][1];
		xe->show(tr, c - 1);
		xe->r = tr, xe->c = c - 1;
		table[r][c - 1] = xe;
		table[r][1] = NULL;
	} else if (tc == c + 2){ // Nhap thanh phai
		Piece * xe = chessBoard->piece[tr][8];
		xe->show(tr, c + 1);
		xe->r = tr, xe->c = c + 1;
		table[r][c + 1] = xe;
		table[r][8] = NULL;
	}
	table[r][c] = NULL;
	table[tr][tc] = this;
	show(tr, tc);
	r = tr, c = tc;
	cntMove++;
	return new Move(0, this, lr, lc, r, c, Move::INN);
}


bool Vua::beChecking(){
	vector<Piece *> rivals = player->rival->piece;
	for (int i = 1; i <= 16; i++){
		if (rivals[i] != NULL && !rivals[i]->isDie && rivals[i]->isKiemsoat(r, c))
			return true;
	}
	return false;
}

vector<Piece *> Vua::getChecking(){
	vector<Piece *> res;
	vector<Piece *> rivals = player->rival->piece;
	for (int i = 1; i <= 16; i++){
		if (rivals[i] != NULL && !rivals[i]->isDie && rivals[i]->isKiemsoat(r, c))
			res.push_back(rivals[i]);
	}
	return res;
}

string Vua::getClassName(){
	return "V";
}

vector<Point> Vua::target() {
	int x = r, y = c;
	vector<Point> res;
	for (auto it : Vua::cango){
		x = r + it.r, y = c + it.c;
		if (isTarget(x, y))
			res.push_back(Point(x, y));
	}
	if (cntMove == 0){
		if (canNhapthanhtrai()){
			res.push_back(Point(r, c - 2));
		}
		if (canNhapthanhphai()){
			res.push_back(Point(r, c + 2));
		}
	}
	return res;
}
vector<Point> Vua::kiemsoat() {
	int x = r, y = c;
	vector<Point> res;
	for (auto it : Vua::cango){
		x = r + it.r, y = c + it.c;
		if (isKiemsoat(x, y))
			res.push_back(Point(x, y));
	}
	return res;
}
bool Vua::isKiemsoat(int x, int y){
	if (!inBound(x, y)) return false;
	return abs(x - r) <= 1 && abs(y - c) <= 1;
}
bool Vua::isTarget(int x, int y) {
	if (!inBound(x, y)) return false;
	if (!isKiemsoat(x, y)){
		if (x != r) return false;
		if (y == c + 2) return canNhapthanhphai();
		if (y == c - 2) return canNhapthanhtrai();
		return false;
	}
	vector<Piece *> rivals = player->rival->piece;
	for (int i = 1; i <= 16; i++){
		if (rivals[i] != NULL && !rivals[i]->isDie && rivals[i]->isKiemsoat(x, y)){
			return false;
		} else {
			auto &table = chessBoard->piece;
			// cho di thu va kiem tra vua khong bi checking:
			// luu bien truoc khi thu
			auto l1 = table[r][c], l2 = table[x][y];
			// di thu:
			if (l2 != NULL) l2->isDie = 1;
			table[x][y] = this, table[r][c] = NULL;
			bool ok = !beChecking();
			// phuc hoi:
			if (l2 != NULL) l2->isDie = 0;
			table[x][y] = l2, table[r][c] = l1;
			if (!ok) return false;
		}
	}
	Piece* select = chessBoard->piece[x][y];
	if (select != NULL && select->team == team) return false;
	return true;
}
bool Vua::canNhapthanhtrai(){
	if (cntMove > 0) return false;
	if (beChecking()) return false;
	auto &table = chessBoard->piece;
	Piece * xe = table[r][1];
	if (xe == NULL || xe->cntMove > 0) return false;
	for (int i = 2; i <= c - 1; i++){
		if (table[r][i] != NULL) return false;
		vector<Piece *> rivals = player->rival->piece;
		for (int i = 1; i <= 16; i++){
			if (rivals[i] != NULL && rivals[i]->isKiemsoat(r, i))
				return false;
		}
	}
	return true;
}
bool Vua::canNhapthanhphai(){
	if (cntMove > 0) return false;
	if (beChecking()) return false;
	auto &table = chessBoard->piece;
	Piece * xe = table[r][8];
	if (xe == NULL || xe->cntMove > 0) return false;
	for (int i = c + 1; i <= 7; i++){
		if (table[r][i] != NULL) return false;
		vector<Piece *> rivals = player->rival->piece;
		for (int i = 1; i <= 16; i++){
			if (rivals[i] != NULL && rivals[i]->isKiemsoat(r, i))
				return false;
		}
	}
	return true;
}





