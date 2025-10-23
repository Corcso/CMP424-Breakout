#include "PowerupManager.h"
#include "GameManager.h"
#include "imgui.h"


PowerupManager::PowerupManager(sf::RenderWindow* window, Paddle* paddle, Ball* ball, GameManager* gameManager)
    : _window(window), _paddle(paddle), _ball(ball), _gameManager(gameManager)
{
}

PowerupManager::~PowerupManager()
{
    for (auto powerup : _powerups)
    {
        delete powerup;
    }
    _powerups.clear();
}

void PowerupManager::update(float dt)
{
    // tick down powerup effect time. Reset if elapsed.
    if (_powerupInEffect)
    {
        _powerupInEffect->second -= dt;
        if (_powerupInEffect->second <= 0)
        {
            _powerupInEffect.reset();
        }
    }


    for (auto it = _powerups.begin(); it != _powerups.end(); )
    {
        checkCollision();
        
        // Delete powerups queued for removal
        (*it)->update(dt);
        if (!(*it)->isAlive())
        {
            delete* it;
            it = _powerups.erase(it);
        }
        else
        {
            ++it;
        }
    }
}

void PowerupManager::render()
{
    for (auto& powerup : _powerups)
    {
        powerup->render();
    }
}

void PowerupManager::spawnPowerup()
{
    switch (rand() % 6)
    {
    case 0:
        _powerups.push_back(new PowerupBigPaddle(_window, _paddle, _ball));
        break;
    case 1:
        _powerups.push_back(new PowerupSlowBall(_window, _paddle, _ball));
        break;
    case 2:
        _powerups.push_back(new PowerupFastBall(_window, _paddle, _ball));
        break;
    case 3:
        _powerups.push_back(new PowerupSmallPaddle(_window, _paddle, _ball));
        break;
    case 4:
        _powerups.push_back(new PowerupFireBall(_window, _paddle, _ball));
        break;
    case 5:
        _powerups.push_back(new PowerupThanosSnap(_window, _paddle, _ball, _gameManager->getBrickManager()));
       break;
    }

}

void PowerupManager::checkCollision()
{
    for (auto& powerup : _powerups)
    {

        if (powerup->checkCollisionWithPaddle())
        {
            _powerupInEffect = powerup->applyEffect();
            powerup->setAlive(false);
        }
    }
}

int PowerupManager::getPowerupsSpawned()
{
    return _powerups.size();
}

std::pair<POWERUPS, float> PowerupManager::getPowerupInEffect()
{
    if (!_powerupInEffect) return { none, 0.f };
    return *_powerupInEffect;
}

void PowerupManager::renderDebugWindow()
{
    ImGui::Begin("Powerup Manager");

    if (ImGui::Button("Spawn Random Powerup")) {
        spawnPowerup();
    }
    if (ImGui::Button("Spawn Big Paddle Powerup")) {
        _powerups.push_back(new PowerupBigPaddle(_window, _paddle, _ball));
    }
    if (ImGui::Button("Spawn Slow Ball Powerup")) {
        _powerups.push_back(new PowerupSlowBall(_window, _paddle, _ball));
    }
    if (ImGui::Button("Spawn Fast Ball Powerup")) {
        _powerups.push_back(new PowerupFastBall(_window, _paddle, _ball));
    }
    if (ImGui::Button("Spawn Small Paddle Powerup")) {
        _powerups.push_back(new PowerupSmallPaddle(_window, _paddle, _ball));
    }
    if (ImGui::Button("Spawn Fireball Powerup")) {
        _powerups.push_back(new PowerupFireBall(_window, _paddle, _ball));
    }
    if (ImGui::Button("Spawn Thanos Snap Powerup")) {
        _powerups.push_back(new PowerupThanosSnap(_window, _paddle, _ball, _gameManager->getBrickManager()));
    }

    ImGui::End();
}
