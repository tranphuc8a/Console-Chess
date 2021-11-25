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
		for (int j = 0; j <= 32; j++){
			char &it = chessBoard[i][j];
			switch (it)	{
				case '|':
					it = char(179);
					break;
				case '-':
					it = char(196);
					break;
				case '+':
					if (i == 1){
						if (j == 0){
							it = char(218);
						} else if (j == 32){
							it = char(191);
						} else {
							it = char(194);
						}
					} else if (i == 17){
						if (j == 0){
							it = char(192);
						} else if (j == 32){
							it = char(217);
						} else {
							it = char(193);
						}
					} else {
						if (j == 0){
							it = char(195);
						} else if (j == 32){
							it = char(180);
						} else {
							it = char(197);
						}
					}
					break;
			}
		}
		
	}
	chessBoard[18] = "  a   b   c   d   e   f   g   h";
	
	x = 1, y = 5;
}

Interface::Interface(Game * game) : Interface(){
	this->game = game;
}

void Interface::free(){
	
}

void Interface::show(){
	system("cls");
	console.gotoXY(0, y);
	cout << "\tGAME CO VUA AI by C++";
	showChessBoard();
	console.gotoXY(19, y);
	cout << "===============BAN CO================";
	console.gotoXY(27, y);
	cout << "==============BIEN BAN===============";
	showHistory();
	showForm();
	console.gotoXY(0, 0);
}

void Interface::showChessBoard(){
	for (int i = 1; i <= 18; i++) {
		console.gotoXY(x + i - 1, y);
		cout << chessBoard[i].c_str() << endl;
	}
	console.gotoXY(0, 0);
	ChessBoard * table = game->chessBoard;
	for (int i = 1; i <= 8; i++){
		for (int j = 1; j <= 8; j++){
			Piece * p = table->piece[i][j];
			if (p != NULL){
				p->show(p->r, p->c);
			}
		}
	}
}

void Interface::showForm(){
	// show:
	console.gotoXY(20, y); cout << "\tESC = Quit, Backspace = Back" << endl;		// 20
	console.gotoXY(21, y); cout << "Last move:  " << endl;				// 21
	console.gotoXY(22, y); cout << "    White:  " << endl;				// 22
	console.gotoXY(23, y); cout << "    Black:  " << endl;				// 23
	console.gotoXY(24, y); cout << "Input move: " << endl;				// 24
	console.gotoXY(25, y); cout << "    Source: " << endl;				// 25
	console.gotoXY(26, y); cout << "    Target: " << endl;				// 26
}

void Interface::getMove(){
	if (game->turn == Player::WHITE){
		show(23, 1 + y, " ");
		show(22, 1 + y, ">");
	} else {
		show(22, 1 + y, " ");
		show(23, 1 + y, ">");
	}
	string src, tg;
	while (1) {
		// input:
		console.ShowPtr();
		console.gotoXY(25, 12 + y); cout << "                            ";
		console.gotoXY(26, 12 + y); cout << "                            ";
		console.gotoXY(25, 12 + y);
		getline(cin, src);
		console.gotoXY(26, 12 + y);
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
				console.gotoXY(22, 12 + y); 
			else console.gotoXY(23, 12 + y);
			cout << "Nuoc di khong hop le!";
		} else {
			// game->history->push(mv);
			if (game->turn == Player::WHITE){
				console.gotoXY(22, 12 + y); cout << "                            ";
				console.gotoXY(22, 12 + y); cout << src.c_str() << "-" << tg.c_str();
			} else {
				console.gotoXY(23, 12 + y); cout << "                            ";
				console.gotoXY(23, 12 + y); cout << src.c_str() << "-" << tg.c_str();
			}
			showMove(game->history->top());
			break;
		}
	}
}

void Interface::showHistory(){
	console.gotoXY(28, y);
	vector<Move *> move = game->history->move;
	for (auto it : move){
		showMove(it);
	}
	console.gotoXY(0, 0);
}

void Interface::showMove(Move * it){
	if (it == NULL) return;
	console.gotoXY(it->id + 27, y);
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
	console.gotoXY(27 + move.back()->id - 1, y);
	cout << "                            \n                                 ";
	console.gotoXY(22, 12 + y); cout << "                            ";
	console.gotoXY(23, 12 + y); cout << "                            ";
	string src, tg;
	for (int i = 3; i <= 4; i++){
		if (move.size() >= i){
			Move * mv = move[move.size() - i];
			if (mv->piece->team == Player::WHITE){
				show(22, 12 + y, mv->src + "-" + mv->tg);
			} else {
				show(23, 12 + y, mv->src + "-" + mv->tg);
			}	
		}
	}
	console.gotoXY(0, 0);
}

void Interface::showWin(int team){
	show(20, y, "                                          ");
	console.gotoXY(20, y);
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
	show(20, y, "                                          ");
	show(20, y, "Draw");
	getch(); 
	console.ShowPtr();
	getch();
}

void Interface::show(int x, int y, string content){
	console.gotoXY(x, y);
	cout << content;
}
void Interface::show(string content, int x, int y){
	console.gotoXY(x, y);
	cout << content;
}

