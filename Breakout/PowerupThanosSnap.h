#pragma once
#include "PowerupBase.h"
#include "BrickManager.h"
class PowerupThanosSnap :
    public PowerupBase
{
public:
    PowerupThanosSnap(sf::RenderWindow* window, Paddle* paddle, Ball* ball, BrickManager* brickManager);
    ~PowerupThanosSnap();

    std::pair<POWERUPS, float> applyEffect() override;
private:
    BrickManager* _brickManager;
};

