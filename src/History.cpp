#include "SubHeader.h"

History::History(){
	move.clear();
}

void History::free(){
	while (size() > 0){
		Move * t = pop();
		std::free(t);
	}
}

void History::push(Move * mv){
	if (mv == NULL) return;
	mv->id = size() + 1;
	move.push_back(mv);
}
Move * History::pop(){
	if (empty()) return NULL;
	Move * t = move.back();
	move.pop_back();
	return t;
}
Move * History::top(){
	if (empty()) return NULL;
	return move.back();
}
int History::size(){
	return move.size();
}
bool History::empty(){
	return move.empty();
}



