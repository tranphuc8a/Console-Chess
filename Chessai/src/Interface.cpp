#include "SubHeader.h"

Interface::Interface(){
	chessBoard = vector<string>(19);
	for (int i = 1; i <= 17; i++){
		if (i % 2 == 0){
			chessBoard[i] = "|   |   |   |   |   |   |   |   | ";
			chessBoard[i] += to_string(9 - i/2);
		}
		else {
			chessBoard[i] = "+---+---+---+---+---+---+---+---+ ";
		}
	}
	chessBoard[18] = "  a   b   c   d   e   f   g   h";
	
	x = 1, y = 0;
}

Interface::Interface(Game * game) : Interface(){
	this->game = game;
}

void Interface::free(){
	
}

void Interface::show(){
	system("cls");
	console.gotoXY(0, 0);
	cout << "\tGAME CO VUA AI by C++";
	showChessBoard();
	console.gotoXY(19, 0);
	cout << "===============BAN CO================";
	console.gotoXY(27, 0);
	cout << "==============BIEN BAN===============";
	showHistory();
	console.gotoXY(0, 0);
}

void Interface::showChessBoard(){
	console.gotoXY(x, y);
	for (int i = 1; i <= 18; i++) cout << chessBoard[i].c_str() << endl;
	console.gotoXY(0, 0);
	ChessBoard * table = game->chessBoard;
	for (int i = 1; i <= 8; i++){
		for (int j = 1; j <= 8; j++){
			if (table->piece[i][j] != NULL){
				console.gotoXY(2*i - 1 + x, 4*j - 2 + y);
				if (table->piece[i][j]->player->team == Player::BLACK){
					console.SetColor(BLACK);
				} else console.SetColor(WHITE);				
				cout << table->piece[i][j]->getClassName().c_str();
				console.SetColor(DEFAULT);
			}
		}
	}
}

void Interface::showForm(){
	// show:
	console.gotoXY(20, 0);
	cout << "\tQ = Quit, B = Back" << endl;		// 20
	cout << "Last move:  " << endl;				// 21
	cout << "    White:  " << endl;				// 22
	cout << "    Black:  " << endl;				// 23
	cout << "Input move: " << endl;				// 24
	cout << "    Source: " << endl;				// 25
	cout << "    Target: " << endl;				// 26
	if (game->turn == Player::WHITE){
		console.gotoXY(23, 1); cout << " ";
		console.gotoXY(22, 1); cout << ">";
	} else {
		console.gotoXY(22, 1); cout << " ";
		console.gotoXY(23, 1); cout << ">";
	}
	// get move:
	getMove();
}

void Interface::getMove(){
	string src, tg;
	while (1) {
		// input:
		console.ShowPtr();
		console.gotoXY(25, 12); cout << "                            ";
		console.gotoXY(26, 12); cout << "                            ";
		console.gotoXY(25, 12);
		getline(cin, src);
		console.gotoXY(26, 12);
		getline(cin, tg);
		console.HidePtr();
		// solve:
		// back or quit:
		if (src == "b" || src == "B" || tg == "b" || tg == "B"){
			game->back();
			continue;
		}
		if (src == "q" || src == "Q" || tg == "q" || tg == "Q"){
			game->quit();
			return;
		}
		// check move and move:
		Move * mv = NULL;
		if (game->trongtai->checkNuocdi(src, tg)){
			mv = game->chessBoard->move(src, tg);
		} 
		if (mv == NULL){
			if (game->turn == Player::WHITE)
				console.gotoXY(22, 12); 
			else console.gotoXY(23, 12);
			cout << "Nuoc di khong hop le!";
		} else {
			// game->history->push(mv);
			if (game->turn == Player::WHITE){
				console.gotoXY(22, 12); cout << "                            ";
				console.gotoXY(22, 12); cout << src.c_str() << "-" << tg.c_str();
			} else {
				console.gotoXY(23, 12); cout << "                            ";
				console.gotoXY(23, 12); cout << src.c_str() << "-" << tg.c_str();
			}
			showMove(game->history->top());
			break;
		}
	}
}

void Interface::showHistory(){
	console.gotoXY(28, 0);
	vector<Move *> move = game->history->move;
	for (auto it : move){
		showMove(it);
	}
	console.gotoXY(0, 0);
}

void Interface::showMove(Move * it){
	if (it == NULL) return;
	console.gotoXY(it->id + 27, 0);
	string src, tg;
	if (it->id % 2 == 1) cout << setw(3) << right << (it->id + 1)/2 << ") ";
	else cout << "     ";
	cout << it->piece->getClassName() << ": ";
	cout << it->src << " - " << it->tg << endl;
	console.gotoXY(0, 0);
}
void Interface::removeLastMove(){
	vector<Move *> move = game->history->move;
	if (move.size() < 2) return;
	console.gotoXY(27 + move.back()->id - 1, 0);
	cout << "               \n                ";
	console.gotoXY(22, 12); cout << "                            ";
	console.gotoXY(23, 12); cout << "                            ";
	string src, tg;
	for (int i = 3; i <= 4; i++){
		if (move.size() >= i){
			Move * mv = move[move.size() - i];
			if (mv->piece->team == Player::WHITE){
				console.gotoXY(22, 12); cout << mv->src << "-" << mv->tg;	
			} else {
				console.gotoXY(23, 12); cout << mv->src << "-" << mv->tg;
			}	
		}
	}
	console.gotoXY(0, 0);
}

void Interface::showWin(int team){
	console.gotoXY(20, 0);
	cout << "                                       ";
	console.gotoXY(20, 0);
	if (team == Player::WHITE){
		cout << "White win!";
	} else {
		cout << "Black win!";
	}
	getch(); 
	console.ShowPtr();
	getch();
}
void Interface::showDraw(){
	console.gotoXY(20, 0);
	cout << "                                          ";
	console.gotoXY(20, 0);
	cout << "Draw";
	getch(); 
	console.ShowPtr();
	getch();
}

