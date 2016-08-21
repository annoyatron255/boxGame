#ifndef gameArea_h
#define gameArea_h

#include <iostream>
//#include "deathBar.h"

class gameArea {
	public:
		gameArea(int startResXIn, int startResYIn, int screenwIn, int screenhIn, bool playerNumber);
		int renderArea();
		bool checkIfDead();
		void resetArea();

		float upCounter;
		float downCounter;
		float leftCounter;
		float rightCounter;

		/*bool lastPressedUp = false;
		bool lastPressedDown = false;
		bool lastPressedLeft = false;
		bool lastPressedRight = false;*/

	private:
		void changeColor();
		void drawObjects();
		void moveLines();
		int getInput();

		SDL_Keycode keyUp;
		SDL_Keycode keyDown;
		SDL_Keycode keyLeft;
		SDL_Keycode keyRight;

		SDL_Rect centerRect;
		int upCounterRender;
		int downCounterRender;
		int leftCounterRender;
		int rightCounterRender;

		float speed;
		float defenseSpeed;

		int redUp;
		int redDown;
		int redLeft;
		int redRight;
		
		int greenUp;
		int greenDown;
		int greenLeft;
		int greenRight;

		int blueUp;
		int blueDown;
		int blueLeft;
		int blueRight;

		int startResX;
		int startResY;

		int screenw;
		int screenh;

		int fourthScreenw;
		int halfScreenh;
};
#endif
