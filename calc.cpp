#include "calc.h"
#include <math.h>
#include <random>
#include <stdlib.h>
#include <ostream>
#include <string>
#include <sstream>
#include <Windows.h>

using namespace std;


/*
	Initiates the window, renderer, audio and the objects which will be drawn.
*/
Calc::Calc() {

	isRunning = true;
	TTF_Init();
	SDL_Init(SDL_INIT_AUDIO);
	SDL_CreateWindowAndRenderer(576,785, 0, &window, &renderer);
	SDL_SetWindowTitle(window, "The calculator");
	
	
	font = TTF_OpenFont("resources/fonts/calc.ttf", 78);
	buttonPress.load("resources/audio/click.wav");
	relax.load("resources/audio/relax.wav");
	SDL_Rect fillRect = { 0, 0, 576,785 };
	SDL_SetRenderDrawColor(renderer, 158, 190, 161, 0);
	SDL_RenderFillRect(renderer, &fillRect);

	screen = { 54, 54, 470,133 };
	bg.setImage("resources/img/calc.png", renderer);
	bg.setDest(0,0, 576,785);
	drawButton(bg);
	addButtons();
	
	loop();

}

Calc::~Calc() {
	TTF_Quit();
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}
/*
	The program loop. Inputs and rendering are handled continuously
*/
void Calc::loop() {
	while (isRunning) {
		input();
		render();
	}
	
}
/*
	Updates the render. Only redraws the screen for each render.
*/
void Calc::render() {
	SDL_SetRenderDrawColor(renderer, 158, 190, 161, 0);
	SDL_RenderFillRect(renderer, &screen);
	draw(onScreen.c_str(), 69, 69, 64, 64, 65);
	SDL_RenderPresent(renderer);
}

/*
	Draws a button to the renderer and adds the texture.
*/

void Calc::drawButton(Object o) {
	SDL_Rect src = o.getDest();
	SDL_Texture* tex = o.getTex();
	SDL_RenderCopy(renderer, tex, NULL, &src);
	SDL_DestroyTexture(tex);
}
/*
	Draws the screen of the calculator
*/
void Calc::draw(const char* msg, int x, int y, int r, int g, int b) {
	SDL_Surface* surf;
	SDL_Texture* tex;
	SDL_Color color;
	color.r = r;
	color.g = g;
	color.b = b;
	color.a = 255;
	SDL_Rect rect;
	surf = TTF_RenderText_Solid(font, msg, color);
	tex = SDL_CreateTextureFromSurface(renderer, surf);
	rect.x = x;
	rect.y = y;
	rect.w = surf->w;
	rect.h = surf->h;
	SDL_FreeSurface(surf);
	SDL_RenderCopy(renderer, tex, NULL, &rect);
	SDL_DestroyTexture(tex);
}

/*
	Handles button presses. Gets the button identifier and acts according to its identifier.
*/
void Calc::handleButton(const char* s) {
	string press;
	press += s;

	if (press == "enter") {
		execute();
	}
	if (press == "0") {
		if (onScreen != " 0") {
			handleNumber(press);
			addToScreen(s);
		}
	}
	if (press == "1") {
		handleNumber(press);
		addToScreen(s);	
	}
	if (press == "2") {
		handleNumber(press);
		addToScreen(s);
	}
	if (press == "3") {
		handleNumber(press);
		addToScreen(s);
	}
	if (press == "4") {
		handleNumber(press);
		addToScreen(s);
	}
	if (press == "5") {
		handleNumber(press);
		addToScreen(s);
	}
	if (press == "6") {
		handleNumber(press);
		addToScreen(s);
	}
	if (press == "7") {
		handleNumber(press);
		addToScreen(s);
	}
	if (press == "8") {
		handleNumber(press);
		addToScreen(s);
	}
	if (press == "9") {
		handleNumber(press);
		addToScreen(s);
	}
	if (press == "music") {
		if (!musicPlaying) {
			relax.play();
			musicPlaying = true;
		}
		else {
			relax.stopAudio();
			musicPlaying = false;
		}
		
	}
	if (press == "off") {
		cout << press << endl;
		isRunning = false;
	}
	if (press == "c") {
		currNumb = 0;
		prevNumb = 0;
		operating = false;
		onScreen = " ";
	}
	if ((press == "ln") || (press == "x^2") || (press == "root") || (press == "ex")) {
		handleFunc(press);
	}
	if (press == "delete") {
		backSpace();
	}
	if ((press == "+") || (press == "-") || (press == "/") || (press == "x")) {
		handleOperator(press);
	}
	if (press == ".") {
		stringstream x;
		x << currNumb;
		string tmp = x.str();
		if (!tmp.find('.') != string::npos) {
			if (onScreen != " ") {
				addPoint();
			}
		}
		
	}

}
/*
	Removes the last character of the string on screen as long as the string is greater than one.
*/
void Calc::backSpace() {
	if (onScreen.size() > 1) {
		onScreen = onScreen.substr(0, onScreen.size() - 1);
		
		if (onScreen.back() == '.') {
			dot = true;
		}
		currNumb = atof(onScreen.c_str());
		justDeleted = true;
	}
}
/*
	Adding characters to the onScreen string which is continuously drawn on the screen.
	Only so many characters can fit on screen. Therefore there is a 13 characters limit.
	If the calculator is not currently using operators the screen will concatenate the number.
	If it is operating then the onScreen string will the (last number) (operator) (current number)
	Special case for points/dots(.)
*/
void Calc::addToScreen(const char* x) {
	currPress = x;
	if (onScreen.length() < 13) {
		if (dot) {
			stringstream x;
			if (justExecuted) {
				x << a << "." << currPress;
			}
			else if (justDeleted) {
				currNumb = atof(onScreen.c_str());
				x << currNumb << "." << currPress;
			}
			else {
				x << prevPress << "." << currPress;
			}
			
			string tmp = x.str();
			currNumb = atof(tmp.c_str());
			dot = false;
			justExecuted = false;
		}
		
		stringstream curr, prev, screen;
		
		curr << currNumb;
		prev << prevNumb;
		string cNumb = curr.str();
		string pNumb = prev.str();
		
		if (!operating) {
			screen << cNumb;
		}
		else {
			screen << pNumb << getOperator() << cNumb;
		}
		onScreen = screen.str();
		
	}
}
/*
	Setting the dot bool to true. Can now use the special case in addToScreen()
*/
void Calc::addPoint() {
	prevPress = currPress;
	dot = true;
}
/*
	Calculates according to what the operator, current number and the last number are.
*/
void Calc::execute() {
	string s = getOperator();
	
	if (s == "-") {
		a = prevNumb - currNumb;
	}
	else if (s == "+") {
		a = prevNumb + currNumb;
	}
	else if (s == "x") {
		a = prevNumb * currNumb;
	}
	else if (s == "/") {
		a = prevNumb / currNumb;
	}
	stringstream x;
	x << a;
	onScreen = x.str();
	prevNumb = currNumb;
	currNumb = a;
	operating = false;
	justExecuted = true;
}
/*
	Sets the operator variable.
*/
void Calc::handleOperator(string s) {
	if ( (currNumb > 0) && (prevNumb > 0) && (operating) ) {
		execute();
	}
	setOperator(s);
	operating = true;
	prevNumb = currNumb;
	currNumb = 0;
}
/*
	Takes the number on screen and runs the selected math function on it.
*/
void Calc::handleFunc(string s) {
	
	if (s == "ex") {
		a = exp(currNumb);
	}
	if (s == "ln") {
		a = log(currNumb);
	}
	if (s == "x^2") {
		a = pow(currNumb, 2.0);
	}
	if(s == "root") {
		a = sqrt(currNumb);
	}
	prevNumb = 0;
	currNumb = a;
	stringstream ss;
	ss << a;
	onScreen = ss.str();
}
/*
	Concatenates the number on screen with the one that was pressed
*/
void Calc::handleNumber(string s) {
	stringstream ss;
	int a = currNumb;
	ss << a;
	string nr = ss.str();
	nr += s;
	currNumb = atof(nr.c_str());
	
}
/*
	Handles inputs from the mouse and keyboard.
	For the mouse button down event it loops through the list of buttons. If the mouse pointer intersected with any of them
	on the click event the button identifer is sent to the handleButton function.
*/
void Calc::input() {
	SDL_Event e;
	while (SDL_PollEvent(&e)) {

		if (e.type == SDL_WINDOWEVENT && e.window.event == SDL_WINDOWEVENT_CLOSE) {
			SDL_DestroyWindow(window);
			SDL_Quit();
			isRunning = false;
		}
		if (e.type == SDL_MOUSEBUTTONDOWN) {
			
			SDL_GetMouseState(&mousex, &mousey);
			tstr = off.mouse(mousex, mousey);
			
			list<Button>::iterator it;
			for (it = buttons.begin(); it != buttons.end(); ++it) {
				if (it->mouse(mousex, mousey) != " ") {
					buttonPress.play();				
					tstr = it->mouse(mousex, mousey);
					handleButton(it->mouse(mousex, mousey));
				}
	
			}
		}
		if (e.type == SDL_MOUSEBUTTONUP) {
			last = tstr;
		}
		if (e.type == SDL_KEYDOWN) {
			buttonPress.play();
			if (e.key.keysym.sym == SDLK_ESCAPE) { isRunning = false; }
			
			if (e.key.keysym.sym == SDLK_0) {
				handleButton("0");
			}
			if ( e.key.keysym.sym == SDLK_1 ) {
				handleButton("1");
			}
			if (e.key.keysym.sym == SDLK_2) {
				handleButton("2");
			}
			if (e.key.keysym.sym == SDLK_3) {
				handleButton("3");
			}
			if (e.key.keysym.sym == SDLK_4) {
				handleButton("4");
			}
			if (e.key.keysym.sym == SDLK_5) {
				handleButton("5");
			}
			if (e.key.keysym.sym == SDLK_6) {
				handleButton("6");
			}
			if (e.key.keysym.sym == SDLK_7) {
				handleButton("7");
			}
			if (e.key.keysym.sym == SDLK_8) {
				handleButton("8");
			}
			if (e.key.keysym.sym == SDLK_9) {
				handleButton("9");
			}
			if ( (e.key.keysym.sym == SDLK_KP_MINUS) || (e.key.keysym.sym == SDLK_MINUS)) {
				handleButton("-");
			}
			if ((e.key.keysym.sym == SDLK_KP_PLUS) || (e.key.keysym.sym == SDLK_PLUS)) {
				handleButton("+");
			}
			if ( (e.key.keysym.sym == SDLK_BACKSPACE) || (e.key.keysym.sym == SDLK_DELETE)) {
				handleButton("delete");
			}
			if (e.key.keysym.sym == SDLK_RETURN) {
				handleButton("enter");
			}
		}
	

	}
	
}
/*
	1 .Setting up each button with an image, identifier, size and coordinates.
	2. Adds it to the renderer to be drawn.
	3. Adds it to a list off buttons which is looped through on button clicks.
*/
void Calc::addButtons() {
	off.setImage("resources/img/buttons/off.png", renderer);
	off.setMath("off");
	off.setDest(47, 241, 78, 78);

	music.setImage("resources/img/buttons/music.png", renderer);
	music.setMath("music");
	music.setDest(47, 441, 78, 78);

	c.setImage("resources/img/buttons/c.png", renderer);
	c.setMath("c");
	c.setDest(47, 341, 78, 78);

	root.setImage("resources/img/buttons/root.png", renderer);
	root.setMath("root");
	root.setDest(47, 541, 78, 78);

	zero.setImage("resources/img/buttons/zero.png", renderer);
	zero.setMath("0");
	zero.setDest(147, 641, 78, 78);

	point.setImage("resources/img/buttons/point.png", renderer);
	point.setMath(".");
	point.setDest(249, 641, 78, 78);

	one.setImage("resources/img/buttons/one.png", renderer);
	one.setMath("1");
	one.setDest(147, 541, 78, 78);

	two.setImage("resources/img/buttons/two.png", renderer);
	two.setMath("2");
	two.setDest(249, 541, 78, 78);

	three.setImage("resources/img/buttons/three.png", renderer);
	three.setMath("3");
	three.setDest(349, 541, 78, 78);

	four.setImage("resources/img/buttons/four.png", renderer);
	four.setMath("4");
	four.setDest(147, 440, 78, 78);

	five.setImage("resources/img/buttons/five.png", renderer);
	five.setMath("5");
	five.setDest(249, 440, 78, 78);

	six.setImage("resources/img/buttons/six.png", renderer);
	six.setMath("6");
	six.setDest(349, 440, 78, 78);

	seven.setImage("resources/img/buttons/seven.png", renderer);
	seven.setMath("7");
	seven.setDest(147, 340, 78, 78);

	eight.setImage("resources/img/buttons/eight.png", renderer);
	eight.setMath("8");
	eight.setDest(249, 340, 78, 78);

	nine.setImage("resources/img/buttons/nine.png", renderer);
	nine.setMath("9");
	nine.setDest(349, 340, 78, 78);

	plus.setImage("resources/img/buttons/plus.png", renderer);
	plus.setMath("+");
	plus.setDest(450, 442, 78, 78);

	minus.setImage("resources/img/buttons/minus.png", renderer);
	minus.setMath("-");
	minus.setDest(450, 542, 78, 78);

	multiply.setImage("resources/img/buttons/multiply.png", renderer);
	multiply.setMath("x");
	multiply.setDest(450, 340, 78, 78);

	divide.setImage("resources/img/buttons/divide.png", renderer);
	divide.setMath("/");
	divide.setDest(450, 241, 78, 78);

	enter.setImage("resources/img/buttons/enter.png", renderer);
	enter.setMath("enter");
	enter.setDest(349, 641, 191, 78);

	squared.setImage("resources/img/buttons/squared.png", renderer);
	squared.setMath("x^2");
	squared.setDest(47, 641, 78, 78);

	ex.setImage("resources/img/buttons/ex.png", renderer);
	ex.setMath("ex");
	ex.setDest(349, 241, 78, 78);

	ln.setImage("resources/img/buttons/ln.png", renderer);
	ln.setMath("ln");
	ln.setDest(249, 241, 78, 78);

	del.setImage("resources/img/buttons/delete.png", renderer);
	del.setMath("delete");
	del.setDest(148, 241, 78, 78);

	buttons.push_back(off);
	buttons.push_back(music);
	buttons.push_back(c);
	buttons.push_back(root);
	buttons.push_back(zero);
	buttons.push_back(point);
	buttons.push_back(one);
	buttons.push_back(two);
	buttons.push_back(three);
	buttons.push_back(four);
	buttons.push_back(five);
	buttons.push_back(six);
	buttons.push_back(seven);
	buttons.push_back(eight);
	buttons.push_back(nine);
	buttons.push_back(plus);
	buttons.push_back(minus);
	buttons.push_back(multiply);
	buttons.push_back(divide);
	buttons.push_back(enter);
	buttons.push_back(squared);
	buttons.push_back(ex);
	buttons.push_back(ln);
	buttons.push_back(del);

	drawButton(off);
	drawButton(music);
	drawButton(c);
	drawButton(root);
	drawButton(zero);
	drawButton(point);
	drawButton(one);
	drawButton(two);
	drawButton(three);
	drawButton(four);
	drawButton(five);
	drawButton(six);
	drawButton(seven);
	drawButton(eight);
	drawButton(nine);
	drawButton(plus);
	drawButton(minus);
	drawButton(multiply);
	drawButton(divide);
	drawButton(enter);
	drawButton(squared);
	drawButton(ex);
	drawButton(ln);
	drawButton(del);

	
}

int main(int argc, char *argv[]) {
	HWND windowHandle = GetConsoleWindow();
	ShowWindow(windowHandle, SW_HIDE);
	Calc c;
	return 0;
}