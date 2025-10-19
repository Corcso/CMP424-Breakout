#include "PowerupThanosSnap.h"

PowerupThanosSnap::PowerupThanosSnap(sf::RenderWindow* window, Paddle* paddle, Ball* ball, BrickManager* brickManager) : PowerupBase(window, paddle, ball), _brickManager(brickManager)
{
	_sprite.setFillColor(thanosSnapEffectsColour); // Purple of sorts
}

PowerupThanosSnap::~PowerupThanosSnap()
{
}

std::pair<POWERUPS, float> PowerupThanosSnap::applyEffect()
{
	// Remove half the bricks (floor to not remove all bricks when 1 left)
	_brickManager->removeBricksRandom(floor(_brickManager->getBricksLeft() / 2.0f));
	// Its an instant powerup so no time but include 1 second for the display
	return std::pair<POWERUPS, float>(thanosSnap, 1.0f);
}
