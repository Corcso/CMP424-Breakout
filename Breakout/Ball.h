#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>


class GameManager;  // forward declaration



class Ball {
public:
    Ball(sf::RenderWindow* window, float velocity, GameManager* gameManager);
    ~Ball();
    void update(float dt);
    void render();
    void setVelocity(float coeff, float duration);
    void setFireBall(float duration);

    /// <summary>
    /// Returns the number of brick hits in a row
    /// </summary>
    /// <returns>Number of consecutive brick hits</returns>
    int getConsecutiveBrickHits();
private:
    sf::CircleShape _sprite;
    sf::Vector2f _direction;
    sf::RenderWindow* _window;
    float _velocity;
    bool _isAlive;
    bool _isFireBall;
    int _consecutiveBrickHits;
    float _timeWithPowerupEffect;

    GameManager* _gameManager;  // Reference to the GameManager

    // Sound Effects
    sf::SoundBuffer _brickSmash_sfx;
    sf::Sound _brickSmash_Sound;

    static constexpr float RADIUS = 10.0f;      
    static constexpr float VELOCITY = 350.0f;   // for reference.
};

