#ifndef BUTTON_H
#define BUTTON_H

#include "object.h"
#include <vector>

class Button : public Object {
public:
	Button() { }
	void setMath(const char* s);
	const char* mouse(int x, int y);
	const char* getMath() { return math; }
	
private:
	char symbol; 
	const char* math;
};
#endif // !BUTTON_H

