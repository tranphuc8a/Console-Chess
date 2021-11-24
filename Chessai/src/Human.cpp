#include "SubHeader.h"

Human::Human() : Player(){}

Human::Human(int team, Game * game){
	this->team = team;
	this->game = game;
	initPiece();
}

void Human::move(){
	game->itf->showForm();
	
}

