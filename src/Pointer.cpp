#include "SubHeader.h"

Pointer::Pointer(){
	
}

Pointer::Pointer(Game * game){
	this->game = game;
	chessBoard = NULL;
	current.set(8, 1);
	if (game != NULL)
		chessBoard = game->chessBoard;
	select = NULL;
}

void Pointer::hide(){
	// (x, y) -> (2*x - 1 + itf->x, 4*y - 2 + itf->y)
	// int x = 2*current.r - 1 + game->itf->x, y = 4*current.c - 2 + game->itf->
}

Move * Pointer::enter(){
	auto &table = chessBoard->piece;
	if (select != NULL){
		Piece * cur = table[current.r][current.c];
		if (cur != NULL && cur->team == select->team){
			select = cur;
			return NULL;
		}
		Move * mv = chessBoard->move(select->r, select->c, current.r, current.c);
		select = NULL;
		if (mv == NULL){
			if (game->turn == Player::WHITE)
				console.gotoXY(22, 12 + game->itf->y); 
			else console.gotoXY(23, 12 + game->itf->y);
			cout << "Nuoc di khong hop le!";
			return NULL;
		} else {
			game->itf->showMove(mv);
			return mv;
		}
	} else {
		select = table[current.r][current.c];
		if (select == NULL) return NULL;
		return NULL;
	}
}

void Pointer::show(int x, int y){
	if (x == 0) x = 8;
	if (x == 9) x = 1;
	if (y == 0) y = 8;
	if (y == 9) y = 1;
	current.set(x, y);
	console.gotoXY(2*x-1 + game->itf->x, 4*y-2 + game->itf->y);
}
void Pointer::turn(int direct){
	switch(direct){
		case Pointer::UP:
			show(current.r - 1, current.c);
			break;
		case Pointer::DOWN:
			show(current.r + 1, current.c);
			break;
		case Pointer::LEFT:
			show(current.r, current.c - 1);
			break;
		case Pointer::RIGHT:
			show(current.r, current.c + 1);
			break;
	}
}

void Pointer::getMove(){
	Move * mv = NULL;
	Event e;
	while (1){
		console.ShowPtr();
		show(current.r, current.c);
		if (mv != NULL) {
			console.HidePtr();
			return;
		}
		
		do {
			e = (Event) getch();
		} while (!(e == ENTER || e == ESC || e == ::UP || e == ::DOWN || e == ::LEFT || e == ::RIGHT || e == SPACE || e == BACKSPACE));
		
		switch (e){
			case ESC:
				game->quit();
				return;
			case ENTER: case SPACE:
				mv = enter();
//				game->itf->show(8, 60, to_string(current.r) + " " + to_string(current.c));
//				if (select != NULL){
//					console.gotoXY(10, 50);
//					cout << "Selected piece: ";
//					cout << select->getClassName() << ", ";
//					cout << "cntMove = " << select->cntMove << ". ";
//					auto v = select->target(); cout << v.size() << ": ";
//					for (auto it : v) 
//						cout<< it.r << it.c << " ";
//				} else {
//					game->itf->show(10, 50, "NULL                                        \t\t");
//				}
				break;
			case BACKSPACE:
				game->back();
				break;
			case ::UP: 
				turn(Pointer::UP);
				break;
			case ::DOWN: 
				turn(Pointer::DOWN);
				break;		
			case ::LEFT: 
				turn(Pointer::LEFT);
				break;
			case ::RIGHT:
				turn(Pointer::RIGHT);
				break;
		}
	}
}
char Pointer::getPhongcap(){
	console.clrscr();
	console.HidePtr();
	console.gotoXY(9, game->itf->y + 3); 
	cout << "CHON QUAN PHONG CAP";
	vector<string> content{ "",
		"Hau", "Xe", "Ma", "Tuong"
	};
	for (int i = 1; i <= 4; i++){
		console.gotoXY(10 + i, game->itf->y + 3);
		cout << content[i];
	}
	Event e;
	int id = 0; 
	while (1){
		game->itf->show(11 + id, game->itf->y, ">");
		do {
			e = (Event) getch();
		} while (!(e == ENTER || e == SPACE || e == ::UP || e == ::DOWN || e == ::LEFT || e == ::RIGHT));
		game->itf->show(11 + id, game->itf->y, " ");
		switch(e){
			case ENTER: case SPACE:
				game->itf->show();
				return content[id + 1][0];
			case ::RIGHT: case ::DOWN:
				id++;
				break;
			case ::LEFT: case ::UP:
				id--;
				break;
		}
		id = (id + 4)%4;
	}
	
}


	
	
	
