/** Jack Sweeney and Spencer Mein 2016
 *  boxGame -- a simple local multiplayer game with boxes!
 */

#include "gfx.h" // general gfx lib I made for SDL
#include "input.h"
//#include "deathBar.h"
#include "gameArea.h"
#include <iostream>
#define screenw 640
#define screenh 318

int leftStartResX = 0;
int leftStartResY = 0;

int rightStartResX = ( screenw / 2 ) + 4;
int rightStartResY = 0;

float attackSpeed = .2;//= .15;

int leftScore = 0;
int rightScore = 0;

int pointsToWin = 3; // 1 - 9 possible

bool startMode = 1;
bool victoryMode = 1;

gameArea leftArea( leftStartResX, leftStartResY, screenw, screenh, true );
gameArea rightArea( rightStartResX, rightStartResY, screenw, screenh, false );
// Rect Definitions

SDL_Rect borderLine = { 319, 0, 4, 318 };

void resetArea(void) {
	leftArea.resetArea();
	rightArea.resetArea();
}

int main ( int argc, char** argv ) {
	gfx::gfxinit(screenw, screenh); // open window with a 640 by 318 resolutions ( 2:1 aspect ratio with a 4 pixel border )
	
	SDL_Texture* numbers[] = { gfx::createTexture("./gfx/0.bmp"),
					gfx::createTexture("./gfx/1.bmp"),
					gfx::createTexture("./gfx/2.bmp"),
					gfx::createTexture("./gfx/3.bmp"),
					gfx::createTexture("./gfx/4.bmp"),
					gfx::createTexture("./gfx/5.bmp"),
					gfx::createTexture("./gfx/6.bmp"),
					gfx::createTexture("./gfx/7.bmp"),
					gfx::createTexture("./gfx/8.bmp"),
					gfx::createTexture("./gfx/9.bmp") };
	SDL_Texture* victory = gfx::createTexture("./gfx/victory.bmp");
	SDL_Texture* pressSpace = gfx::createTexture("./gfx/pressSpace.bmp");
	
	SDL_Texture* wasdTutorial = gfx::createTexture("./gfx/wasd.bmp");
	SDL_Texture* arrowKeysTutorial = gfx::createTexture("./gfx/arrowkeys.bmp");
	/* program main loop */
	while (!(input::getKeyState(SDLK_ESCAPE) || input::getQuit())) {
		
		gfx::clearScreen(0, 0, 0);

		// draw border line
		gfx::drawRect(borderLine, 92, 92, 92);
		// draw left guide lines
		gfx::drawLine(leftStartResX, leftStartResY, screenh, screenh, 42, 42, 42);
		gfx::drawLine(leftStartResX, screenh, screenh, leftStartResY, 42, 42, 42);
		// draw right guide lines
		gfx::drawLine(rightStartResX, leftStartResY, screenh + rightStartResX, screenh + rightStartResY, 42, 42, 42);
		gfx::drawLine(rightStartResX, screenh, screenw, rightStartResY, 42, 42, 42);

		int leftDir = leftArea.renderArea();
		int rightDir = rightArea.renderArea();
		// Game Logic Starts Here
		// Check if Game in Over
		if ( rightArea.checkIfDead() ) {
			resetArea();
			leftScore++;
		} else if ( leftArea.checkIfDead() ) {
			resetArea();
			rightScore++;
		} 

		// Add Attacks ( Left )
		switch ( leftDir ) { // Yes I'm aware of enums! Just wasn't worth the issues that may arise in dependancies in this short time frame.
			case 0: // Up
				rightArea.upCounter += attackSpeed;
				break;
			case 1: // Down
				rightArea.downCounter += attackSpeed;
				break;
			case 2: // Left
				rightArea.leftCounter += attackSpeed;
				break;
			case 3: // Right
				rightArea.rightCounter += attackSpeed;
				break;
		}
		// Add Attacks ( Right )
		switch ( rightDir ) {
			case 0: // Up
				leftArea.upCounter += attackSpeed;
				break;
			case 1: // Down
				leftArea.downCounter += attackSpeed;
				break;
			case 2: // Left
				leftArea.leftCounter += attackSpeed;
				break;
			case 3: // Right
				leftArea.rightCounter += attackSpeed;
				break;
		}
		
		gfx::drawTexture(numbers[leftScore], { 25, 25, 40, 50 }); // Draw leftScore
		gfx::drawTexture(numbers[rightScore], { 575, 24, 40, 50 }); // Draw rightScore
		// Check if anyone won the game
		if ( leftScore >= pointsToWin ) { 
			resetArea();
			//gfx::drawTexture(wasdTutorial, { 84, 104, 150, 110 });
			//gfx::drawTexture(arrowKeysTutorial, { 406, 104, 150, 110 });
			gfx::drawTexture(victory, { 11, 134, 300, 50 });
			victoryMode = 1;
		}
		if ( rightScore >= pointsToWin ) {
			resetArea();
			//gfx::drawTexture(wasdTutorial, { 84, 104, 150, 110 });
			//gfx::drawTexture(arrowKeysTutorial, { 406, 104, 150, 110 });
			gfx::drawTexture(victory, { 333, 134, 300, 50 });
			victoryMode = 1;
		}
		

		gfx::update(); // Draw to Screen
		if ( victoryMode ) { // Go to paused victory loop ( also used for boot up )
			if ( startMode ) {
				gfx::drawTexture(wasdTutorial, { 84, 104, 150, 110 });
				gfx::drawTexture(arrowKeysTutorial, { 406, 104, 150, 110 });
				startMode = 0;
			}
			while (!(input::getKeyState(SDLK_ESCAPE) || input::getQuit() || input::getKeyState(SDLK_SPACE))) {
				//SDL_Delay(1);
				gfx::drawTexture(pressSpace, { 110, 238, 420, 50 });
				gfx::update();
			}
			leftScore = 0;
			rightScore = 0;
			victoryMode = 0;
		}
	}

	gfx::close(); // Clean Up

	return 0; // return success! (cuz why not?)
}
