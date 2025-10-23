#pragma once
#include <SFML/Graphics.hpp>
#include "CONSTANTS.h"
#include "Paddle.h"
#include "Ball.h"
#include "BrickManager.h"
#include "PowerupManager.h"
#include "MessagingSystem.h"
#include "TweenManager.h"
#include "UI.h"



class GameManager {
public:
    GameManager(sf::RenderWindow* window);
    void initialize();
    void update(float dt);
    void loseLife();
    void render();
    void levelComplete();
    void powerupEffect(POWERUPS pu, float t);

    Paddle* getPaddle() const;
    BrickManager* getBrickManager() const;
    PowerupManager* getPowerupManager() const;
    sf::RenderWindow* getWindow() const;
    TweenManager* getTweenManager() const;
    UI* getUI() const;

    void renderDebugWindow();

private:
    bool _pause;
    bool _debugOpen;
    float _pauseHold;
    float _time;
    float _timeLastPowerupSpawned;
    float _timeLastPowerupRollDone;
    int _lives;
    bool _levelComplete;
    bool _twixifyRanThisRound;
    std::pair<POWERUPS, float> _powerupInEffect;

    sf::Font _font;
    sf::Text _masterText;

    sf::RenderWindow* _window;
    Paddle* _paddle;
    Ball* _ball;
    BrickManager* _brickManager;
    PowerupManager* _powerupManager;
    MessagingSystem* _messagingSystem;
    TweenManager* _tweenManager;
    UI* _ui;

    // Audio
    sf::SoundBuffer _death_sfx;
    sf::Sound _death_Sound;

    // Who Likes to Party (MacLeod, 2012) 
    sf::Music _win_Music;

    static constexpr float PAUSE_TIME_BUFFER = 0.5f;
    static constexpr float POWERUP_FREQUENCY = 7.5f;    // time between minimum powerup spawn
    static constexpr float POWERUP_ROLL_FREQUENCY = 0.1f;    // now the minimum time has passed per powerup, how often do we roll for one
    static constexpr int POWERUP_CHANCE_PER_ROLL = 10;    // when rolling, 1 in X chance of a powerup spawning this time
};
