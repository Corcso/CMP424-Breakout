#include "GameManager.h"
#include "Ball.h"
#include "PowerupManager.h"
#include <iostream>

GameManager::GameManager(sf::RenderWindow* window)
    : _window(window), _paddle(nullptr), _ball(nullptr), _brickManager(nullptr), _powerupManager(nullptr),
    _messagingSystem(nullptr), _ui(nullptr), _pause(false), _time(0.f), _lives(3), _pauseHold(0.f), _levelComplete(false),
    _powerupInEffect({ none,0.f }), _timeLastPowerupSpawned(0.f), _timeLastPowerupRollDone(0.f), _twixifyRanThisRound(false), _tweenManager(nullptr)
{
    _font.loadFromFile("font/montS.ttf");
    _masterText.setFont(_font);
    _masterText.setPosition(50, 400);
    _masterText.setCharacterSize(48);
    _masterText.setFillColor(sf::Color::Yellow);
}

void GameManager::initialize()
{
    _paddle = new Paddle(_window);
    _brickManager = new BrickManager(_window, this);
    _messagingSystem = new MessagingSystem(_window);
    _ball = new Ball(_window, 400.0f, this); 
    _powerupManager = new PowerupManager(_window, _paddle, _ball, this);
    _ui = new UI(_window, _lives, this);
    _tweenManager = new TweenManager();

    // Create bricks
    _brickManager->createBricks(5, 10, 80.0f, 30.0f, 5.0f);

    // Load audio
    _death_sfx.loadFromFile("./Assets/death.wav");
    _death_Sound.setBuffer(_death_sfx);
}

void GameManager::update(float dt)
{
    _powerupInEffect = _powerupManager->getPowerupInEffect();
    _ui->updatePowerupText(_powerupInEffect);
    _powerupInEffect.second -= dt;
    

    if (_lives <= 0)
    {
        _masterText.setString("Game over.");
        return;
    }
    if (_levelComplete)
    {
        _masterText.setString("Level completed.");
        return;
    }
    // pause and pause handling
    if (_pauseHold > 0.f) _pauseHold -= dt;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::P))
    {
        if (!_pause && _pauseHold <= 0.f)
        {
            _pause = true;
            _masterText.setString("paused.");
            _pauseHold = PAUSE_TIME_BUFFER;
        }
        if (_pause && _pauseHold <= 0.f)
        {
            _pause = false;
            _masterText.setString("");
            _pauseHold = PAUSE_TIME_BUFFER;
        }
    }
    if (_pause)
    {
        return;
    }

    // timer.
    _time += dt;


    if (_time > _timeLastPowerupSpawned + POWERUP_FREQUENCY && _time > _timeLastPowerupRollDone + POWERUP_ROLL_FREQUENCY)
    {
        if (rand() % POWERUP_CHANCE_PER_ROLL == 0) {
            _powerupManager->spawnPowerup();
            _timeLastPowerupSpawned = _time;
        }
        _timeLastPowerupRollDone = _time;
    }

    // move paddle
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) _paddle->moveRight(dt);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) _paddle->moveLeft(dt);

    // update everything 
    _paddle->update(dt);
    _ball->update(dt);
    _powerupManager->update(dt);
    _tweenManager->update(dt);

    // If ball has done 5+ consecutive breaks, twixifify the board
    if (!_twixifyRanThisRound && _ball->getConsecutiveBrickHits() >= 5) {
        _brickManager->twixifyAllBricks();
        _twixifyRanThisRound = true;
    }
}

void GameManager::loseLife()
{
    _lives--;
    _ui->lifeLost(_lives);

    _tweenManager->addTweenWithCallback(0, 1, 2.f, TweenManager::EasingFunction::LINEAR_IN_OUT, [&](float value) {
        float interpolatedValue = sin(7 * value) * sin(45 * value);
        sf::View toEdit = _window->getDefaultView();
        toEdit.setRotation(interpolatedValue);
        _window->setView(toEdit);
        }, [&]() {
            _window->setView(_window->getDefaultView());
        });

    // Play audio
    _death_Sound.play();
}

void GameManager::render()
{
    _paddle->render();
    _ball->render();
    _brickManager->render();
    _powerupManager->render();
    _window->draw(_masterText);
    _ui->render();
}

void GameManager::levelComplete()
{
    _levelComplete = true;
}

sf::RenderWindow* GameManager::getWindow() const { return _window; }
TweenManager* GameManager::getTweenManager() const {return _tweenManager; }
UI* GameManager::getUI() const { return _ui; }
Paddle* GameManager::getPaddle() const { return _paddle; }
BrickManager* GameManager::getBrickManager() const { return _brickManager; }
PowerupManager* GameManager::getPowerupManager() const { return _powerupManager; }
