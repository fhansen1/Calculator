#include "button.h"

/*
	Sets an indentifier for the button
*/
void Button::setMath(const char* s) {
	this->math = s;
}
/*
	Calculates if the mouse pointer is within the button's bounds
*/
const char* Button::mouse(int x, int y) {
	int tmp;
	if (this->getDest().w > this->getDest().h) {
		tmp = this->getDest().w;
	}
	else { tmp = this->getDest().h; }
	if ((this->getDest().x < x) && (this->getDest().x + tmp > x)) {
		if ((this->getDest().y < y) && (this->getDest().y + this->getDest().h > y)) {
			return this->math;
		}
	}
	return " ";
}

