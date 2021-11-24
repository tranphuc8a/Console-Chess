#include "SubHeader.h"

Piece::Piece(){
	cntMove = 0;
	isDie = false;
}

Piece::Piece(Player * player) : Piece(){
	if (player == NULL) return;
	this->player = player;
	this->team = player->team;
}
Piece::Piece(Player * player, int r, int c) : Piece(player) {
	this->r = r;
	this->c = c;
	this->team = player->team;
};

void Piece::setPoint(int x, int y){
	r = x, c = y;
}

vector<Point> Piece::target(){
	vector<Point> res;
	for (int i = 1; i = 8; i++){
		for (int j = 1; j <= 8; j++){
			if (isTarget(i, j)){
				res.push_back(Point(i, j));
			}
		}
	}
	return res;	
};

vector<Point> Piece::kiemsoat(){
	vector<Point> res;
	for (int i = 1; i = 8; i++){
		for (int j = 1; j <= 8; j++){
			if (isKiemsoat(i, j)){
				res.push_back(Point(i, j));
			}
		}
	}
	return res;
}

void Piece::show(int tr, int tc){
	ChessBoard * table = player->game->chessBoard;
	int x = player->game->itf->x, y = player->game->itf->y;
	if (tr < 0 && tc < 0){
		console.gotoXY(2*r - 1 + x, 4*c - 2 + y); cout << " ";
		return;
	}
	
	console.gotoXY(2*r - 1 + x, 4*c - 2 + y); cout << " ";
	console.gotoXY(2*tr - 1 + x, 4*tc - 2 + y);
	if (player->team == Player::BLACK) {
		console.SetColor(BLACK);	
	} else {
		console.SetColor(WHITE);
	}
	cout << getClassName().c_str();
	console.SetColor(DEFAULT);
}

bool Piece::inBound(int x, int y){
	return 1 <= x && x <= 8 && 1 <= y && y <= 8;
}



