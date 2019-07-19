#ifndef CALC_H
#define CALC_H

#include <iostream>
using namespace std;
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <ostream>
#include "object.h"
#include "audio.h"
#include "button.h"
#include <list>
class Calc
{
public:
	Calc();
	~Calc();
	void loop();
	void render();
	void input();
	void drawButton(Object o);
	void draw(const char* msg, int x, int y, int r, int g, int b);
	void addButtons();
	void addPoint();
	void addToScreen(const char* x);
	void handleButton(const char* s);
	void handleNumber(string s);
	void handleFunc(string s);
	void handleOperator(string s);
	void setOperator(string s) { operatoor = s; }
	string getOperator() { return operatoor; }
	void execute();
	void backSpace();

private:
	SDL_Renderer* renderer;
	SDL_Window* window;  
	TTF_Font* font;
	const char* tstr = "Welcome";
	string onScreen = " ";
	string last;
	string operatoor;
	bool isRunning, operating, musicPlaying, dot, justExecuted, justDeleted;
	double prevNumb, currNumb, a;
	int mousex, mousey;
	Audio relax, buttonPress;
	string prevPress, currPress;
	Object bg;
	Button off, del ,c, percent, root, one, two, three, four, five, six, seven, eight, nine, zero;
	Button point, divide, multiply, minus, plus, equal, enter, ex, ln, squared, music;
	list<Button> buttons;
	SDL_Rect screen;
};


#endif //CALC_H