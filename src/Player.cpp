#include "SubHeader.h"

int Player::WHITE = 0;
int Player::BLACK = 1;

Player::Player(){
	team = Player::WHITE;
}

void Player::initPiece(){
	int row = 8;
	if (team == Player::BLACK) row = 1;
	piece = vector<Piece *>(17, NULL);
	piece[1] = new Vua(this);
	piece[2] = new Hau(this);
	piece[3] = new Xe(this, row, 1);
	piece[4] = new Xe(this, row, 8);
	piece[5] = new Ma(this, row, 2);
	piece[6] = new Ma(this, row, 7);
	piece[7] = new Tuong(this, row, 3);
	piece[8] = new Tuong(this, row, 6);
	row = 7;
	if (team == Player::BLACK) row = 2;
	for (int i = 9; i <= 16; i++)
		piece[i] = new Tot(this, row, i - 8);
	for (int i = 1; i <= 16; i++){
		if (piece[i] != NULL){
			piece[i]->id = i;
			piece[i]->vua = (Vua *) piece[1];
		}
	}		
}

void Player::free(){
	for (int i = 1; i <= 16; i++){
		if (piece[i] != NULL){
			std::free(piece[i]);
		}
	}
}

bool Player::contains(Piece * p){
	if (p == NULL) return false;
	for (int i = 1; i <= 16; i++)
		if (piece[i] == p)
			return true;
	return false;
}


