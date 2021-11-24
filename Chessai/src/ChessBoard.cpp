#include "SubHeader.h"

ChessBoard::ChessBoard(){
	piece = vector<vector<Piece*>> (9, vector<Piece*>(9, NULL));
}
ChessBoard::ChessBoard(Game * game) : ChessBoard(){
	this->game = game;
	Player * pl1 = game->white, * pl2 = game->black;
	
	if (pl1 != NULL)
	for (int i = 1; i <= 16; i++){
		auto p = pl1->piece[i];
		if (p != NULL){
			piece[p->r][p->c] = p;
			p->chessBoard = this;
		}
	}
	if (pl2 != NULL)
	for (int i = 1; i <= 16; i++){
		auto p = pl2->piece[i];
		if (p != NULL){
			piece[p->r][p->c] = p;
			p->chessBoard = this;
		}
	}
}

void ChessBoard::free(){
	
}

Move * ChessBoard::move(string src, string tg){
	// translate src & tg;
	int sr = 9 - (src[1] - '0'), sc = src[0] - 'a' + 1;
	int tr = 9 - (tg[1] - '0'), tc = tg[0] - 'a' + 1;
	// check select:
	Piece * select = piece[sr][sc];
	
	if (select == NULL || select->isDie || !(game->currentPlayer->contains(select)))
		return NULL;
	if (select->getClassName() == "i" && tg.size() == 2 && (tr == 1 || tr == 8)) return NULL;
		
	// check select can go:
	if (!select->isTarget(tr, tc))
		return NULL;	
	// OK:
	// phong cap:
	if (tg.size() == 3)
		return phongcap(select, tr, tc, tg[2]);
	// Normal
	Move * mv = select->move(tr, tc);
	game->history->push(mv);
	return mv;
}

Move * ChessBoard::phongcap(Piece * select, int tr, int tc, char newPiece){
	Move * mv = new Move(0, select, select->r, select->c, tr, tc, Move::UPP);
	Piece * kill = NULL;
	if (select->isKiemsoat(tr, tc) && (piece[tr][tc] != NULL)){
		piece[tr][tc]->isDie = 1;
		kill = piece[tr][tc];
	}
	Piece * newP = NULL;
	switch (newPiece){
		case 'H': case 'h':
			newP = new Hau(select->player, tr, tc);
			break;
		case 'X': case 'x':
			newP = new Xe(select->player, tr, tc);
			break;
		case 'M': case 'm':
			newP = new Ma(select->player, tr, tc);
			break;
		case 'T': case 't':
			newP = new Tuong(select->player, tr, tc);
			break;
	}
	newP->id = select->id;
	newP->vua = select->vua;
	newP->chessBoard = this;
	select->player->piece[select->id] = newP;
	select->isDie = 1;
	piece[tr][tc] = newP;
	piece[select->r][select->c] = NULL;
	select->show(tr, tc);
	newP->show(tr, tc);
	mv->setKillBear(kill, newP);
	game->history->push(mv);
	return mv;
}





