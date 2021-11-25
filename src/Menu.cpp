#include "SubHeader.h"

Menu::Menu(){
	game = new Game();
}

void Menu::show(){
	int stt = 0;
	do {
		console.SetColor(TEAL, BLACK);
		console.HidePtr();
		system("cls");
		cout << "  Choi game" << endl;
		cout << "  Quit" << endl;
		console.gotoXY(1 - stt, 0); cout << " ";
		console.gotoXY(stt, 0); cout << ">";
		console.gotoXY(0, 0);
		Event e;
		do {
			e = (Event) getch();
		} while (!(e == ENTER | e == UP | e == DOWN));
		
		switch (e){
			case UP:
			case DOWN:
				stt = 1 - stt;
				break;
			case ENTER:
				if (stt == 1){
					return;
				} else {
					game->start();	
				}
				break;
		}
	} while (1);
}
