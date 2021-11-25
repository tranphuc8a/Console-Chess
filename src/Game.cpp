#include "SubHeader.h"

Game::Game(){
//	init();
}

void Game::init(){
	trongtai = new Trongtai(this);
	itf = new Interface(this);
	white = black = NULL;
	
	white = new Human(Player::WHITE, this);
	black = new Human(Player::BLACK, this);
	white->rival = black; black->rival = white;
	chessBoard = new ChessBoard(this);
	history = NULL;
	history = new History();
	pointer = new Pointer(this);
	
	turn = Player::WHITE;
	isEnd = false;
	winner = NULL;
	currentPlayer = white;
}

void Game::start(){
	init();
	itf->show();
	int x = 0, check = Trongtai::NORM;
	while (1){
		// Luot trang di:
		turn = Player::WHITE;
		currentPlayer = white;
		white->move();
		if (isEnd){
			break;
		}
		check = trongtai->checkMate(black);
		if (check == Trongtai::MATE){
			win(white);
			break;
		} else if (check == Trongtai::DRAW){
			draw();
			break;
		}
		
		// Luot den di:
		turn = Player::BLACK;
		currentPlayer = black;
		black->move();
		if (isEnd){
			break;
		}
		check = trongtai->checkMate(white);
		if (check == Trongtai::MATE){
			win(black);
			break;
		} else if (check == Trongtai::DRAW){
			draw();
			break;
		}
	}
}

void Game::win(Player * player){
	itf->showWin(player->team);
}
void Game::draw(){
	itf->showDraw();
}

void Game::quit(){
	this->isEnd = 1;
	history->free();
	free(history);
	chessBoard->free();
	free(chessBoard);
	white->free();
	black->free();
	free(white);
	free(black);
	itf->free();
	free(itf);
	trongtai->free();
	free(trongtai);
	free(pointer);
}

void Game::back(){
	if (history->size() < 2) return;
	itf->removeLastMove();
	auto &table = chessBoard->piece;
	for (int i = 1; i <= 2; i++){
		Move * top = history->pop();
		top->piece->cntMove--;
		Piece * xe = NULL;
		switch (top->type){
			case Move::NORM:
				top->piece->show(top->sr, top->sc);
				top->piece->setPoint(top->sr, top->sc);
				table[top->sr][top->sc] = top->piece;
				table[top->tr][top->tc] = NULL;
				break;
			case Move::KILL: case Move::SKILL:
				top->piece->show(top->sr, top->sc);
				top->piece->setPoint(top->sr, top->sc);
				top->kill->isDie = 0;
				top->kill->show(top->tr, top->tc);
				table[top->sr][top->sc] = top->piece;
				if (top->type == Move::KILL){
					table[top->tr][top->tc] = top->kill;
				} else {
					table[top->sr][top->tc] = top->kill;
				}
				break;
			case Move::INN:
				top->piece->show(top->sr, top->sc);
				top->piece->setPoint(top->sr, top->sc);
				table[top->sr][top->sc] = top->piece;
				table[top->tr][top->tc] = NULL;
				xe = NULL;
				if (top->tc > top->sc){ // Nhap thanh phai:
					xe = chessBoard->piece[top->sr][top->sc + 1];
					xe->show(top->sr, 8);
					xe->setPoint(top->sr, 8);
					table[top->sr][8] = xe;
					table[top->sr][top->sc + 1] = NULL;
				} else { // nhap thanh trai
					xe = chessBoard->piece[top->sr][top->sc - 1];
					xe->show(top->sr, 1);
					xe->setPoint(top->sr, 1);
					table[top->sr][1] = xe;
					table[top->sr][top->sc - 1] = NULL;
				}
				break;
			case Move::UPP:
				Piece * act = top->piece;
				act->player->piece[act->id] = act;
				act->isDie = 0;
				act->show(top->sr, top->sc);
				act->setPoint(top->sr, top->sc);
				if (top->kill != NULL){
					top->kill->isDie = 0;
					top->kill->show(top->tr, top->tc);
					top->kill->setPoint(top->tr, top->tc);
				}
				table[top->sr][top->sc] = act;
				table[top->tr][top->tc] = top->kill;
				free(top->bear);
				break;
		}
		free(top);
	}
}
