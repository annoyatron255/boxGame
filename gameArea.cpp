#include <iostream>
#include <SDL2/SDL.h>
//#include "deathBar.h"
#include "gameArea.h"
#include "gfx.h"
#include "input.h"

gameArea::gameArea(int startResXIn, int startResYIn, int screenwIn, int screenhIn, bool playerNumber) {
	startResX = startResXIn;
	startResY = startResYIn;

	screenw = screenwIn;
	screenh = screenhIn;

	if ( !playerNumber ) {
		keyUp = SDLK_UP;
		keyDown = SDLK_DOWN;
		keyLeft = SDLK_LEFT;
		keyRight = SDLK_RIGHT;
	} else if ( playerNumber ) {
		keyUp = SDLK_w;
		keyDown = SDLK_s;
		keyLeft = SDLK_a;
		keyRight = SDLK_d;
	}
	
	fourthScreenw = (screenw / 4) + startResX;
	halfScreenh = (screenh / 2) + startResY;
}

int gameArea::renderArea() {
	changeColor();
	moveLines();

	int dir = getInput();

	drawObjects();
	return dir;
}


// Ok putting this upfront. yes, we thought and even tried using classes for each of the four "deathBars", however there were a few hicups and bugs which were pretty difficult to squash. We thought I'd be best to just have something that works over something that's cleaner ( as much as it pains me! )
int gameArea::getInput() { // Get input and perform "defense" ( backwards ) movement
	defenseSpeed = .55;
	if ( input::getKeyState(keyUp) ) {
		upCounter -= defenseSpeed;
		return 0;
	} else if ( input::getKeyState(keyDown) ) {
		downCounter -= defenseSpeed;
		return 1;
	} else if ( input::getKeyState(keyLeft) ) {
		leftCounter -= defenseSpeed; 
		return 2;
	} else if ( input::getKeyState(keyRight) ) {
		rightCounter -= defenseSpeed;
		return 3;
	}
	return 4;
}

void gameArea::moveLines() { // Progressive Movement of the four lines ( Camp Protection )
	speed = .2;
	upCounter += speed;
	downCounter += speed;
	leftCounter += speed;
	rightCounter += speed;
}

void gameArea::drawObjects() { // draw lines cast internal floats to ints for rendering

	if ( upCounter < 0 ) { upCounter = 0; }
	if ( downCounter < 0 ) { downCounter = 0; }
	if ( leftCounter < 0 ) { leftCounter = 0; }
	if ( rightCounter < 0 ) { rightCounter = 0; }

	upCounterRender = static_cast<int>(upCounter);
	downCounterRender = static_cast<int>(downCounter);
	leftCounterRender = static_cast<int>(leftCounter);
	rightCounterRender = static_cast<int>(rightCounter);	

	centerRect = { fourthScreenw, halfScreenh, 2, 2 };
	gfx::drawRect( centerRect, 255, 255, 255 );

	gfx::drawLine( // Down
		fourthScreenw - downCounterRender, 
		halfScreenh + downCounterRender,
		fourthScreenw + downCounterRender,
		halfScreenh + downCounterRender,
		redDown, greenDown, blueDown );
	gfx::drawLine( // Right
		fourthScreenw + rightCounterRender,
		halfScreenh + rightCounterRender,
		fourthScreenw + rightCounterRender,
		halfScreenh - rightCounterRender, 
		redRight, greenRight, blueRight );
	gfx::drawLine( // Up
		fourthScreenw - upCounterRender,
		halfScreenh - upCounterRender,
		fourthScreenw + upCounterRender,
		halfScreenh - upCounterRender,
		redUp, greenUp, blueUp );
	gfx::drawLine( // Left 
		fourthScreenw - leftCounterRender,
		halfScreenh + leftCounterRender,
		fourthScreenw - leftCounterRender,
		halfScreenh - leftCounterRender,
		redLeft, greenLeft, blueLeft );
}

void gameArea::resetArea() { // reset position of line to the center
	upCounter = 0;
	downCounter = 0;
	leftCounter = 0;
	rightCounter = 0;
}

bool gameArea::checkIfDead() { // check whether lines have hit borders and cause a "death"
	return ( (upCounter >= halfScreenh) || (downCounter >= halfScreenh) || (leftCounter >= halfScreenh) || (rightCounter >= halfScreenh) );
}

void gameArea::changeColor() { // change color of the line based on the danger level green -> red ( distance to borders)
	// Copy Paste Color line changer with magic numbers ( blame Spencer not Jack )
	float am = downCounterRender * 
3.2075471698113207547169811320754716981132075471698;

	int amount = static_cast<int>(am);

	if ( amount < 255 && amount >= 0) {
		redDown = amount;
		greenDown = 255;
		blueDown = 0;
	} else if ( amount > 255 && amount < 510 ) {
		redDown = 255;
		greenDown = -amount + 510;
		blueDown = 0;
	}
	
	am = rightCounterRender * 3.20755;

	amount = static_cast<int>(am);

	if ( amount < 255 && amount >= 0) {
		redRight = amount;
		greenRight = 255;
		blueRight = 0;
	} else if ( amount > 255 && amount < 510 ) {
		redRight = 255;
		greenRight = -amount + 510;
		blueRight = 0;
	}

	am = upCounterRender * 3.20755;

	amount = static_cast<int>(am);

	if ( amount < 255 && amount >= 0) {
		redUp = amount;
		greenUp = 255;
		blueUp = 0;
	} else if ( amount > 255 && amount < 510 ) {
		redUp = 255;
		greenUp = -amount + 510;
		blueUp = 0;
	}

	am = leftCounterRender * 3.20755;

	amount = static_cast<int>(am);

	if ( amount < 255 && amount >= 0) {
		redLeft = amount;
		greenLeft = 255;
		blueLeft = 0;
	} else if ( amount > 255 && amount < 510 ) {
		redLeft = 255;
		greenLeft = -amount + 510;
		blueLeft = 0;
	}
}
