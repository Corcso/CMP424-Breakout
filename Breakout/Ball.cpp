#include "Ball.h"
#include "GameManager.h" // avoid cicular dependencies

Ball::Ball(sf::RenderWindow* window, float velocity, GameManager* gameManager)
    : _window(window), _velocity(velocity), _gameManager(gameManager),
    _timeWithPowerupEffect(0.f), _isFireBall(false), _isAlive(true), _direction({1,1}), _consecutiveBrickHits(0)
{
    _sprite.setRadius(RADIUS);
    _sprite.setFillColor(sf::Color::Cyan);
    _sprite.setPosition(0, 300);

    _brickSmash_sfx.loadFromFile("./Assets/brickHit.wav");
    _paddleHit_sfx.loadFromFile("./Assets/paddleHit.wav");
    _wallHit_sfx.loadFromFile("./Assets/wallHit.wav");
    _brickSmash_Sound.setBuffer(_brickSmash_sfx);
    _paddleHit_Sound.setBuffer(_paddleHit_sfx);
    _wallHit_Sound.setBuffer(_wallHit_sfx);
}

Ball::~Ball()
{
}

void Ball::update(float dt)
{
    // check for powerup, tick down or correct
    if (_timeWithPowerupEffect > 0.f)
    {
        _timeWithPowerupEffect -= dt;
    }
    else
    {
        if (_velocity != VELOCITY)
            _velocity = VELOCITY;   // reset speed.
        else
        {
            setFireBall(0);    // disable fireball
            _sprite.setFillColor(sf::Color::Cyan);  // back to normal colour.
        }        
    }

    // Fireball effect
    if (_isFireBall)
    {
        // Flickering effect
        int flicker = rand() % 50 + 205; // Random value between 205 and 255
        _sprite.setFillColor(sf::Color(flicker, flicker / 2, 0)); // Orange flickering color
    }

    // Update position with a subtle floating-point error
    _sprite.move(_direction * _velocity * dt);

    // check bounds and bounce
    sf::Vector2f position = _sprite.getPosition();
    sf::Vector2u windowDimensions = _window->getSize();

    // bounce on walls
    if ((position.x >= windowDimensions.x - 2 * RADIUS && _direction.x > 0) || (position.x <= 0 && _direction.x < 0))
    {
        _direction.x *= -1;

        _wallHit_Sound.play();
    }

    // bounce on ceiling
    if (position.y <= 0 && _direction.y < 0)
    {
        _direction.y *= -1;

        _wallHit_Sound.play();
    }

    // lose life bounce
    if (position.y > windowDimensions.y)
    {
        _sprite.setPosition(0, 300);
        _direction = { 1, 1 };
        _gameManager->loseLife();
        _consecutiveBrickHits = 0;
    }

    // collision with paddle
    if (_sprite.getGlobalBounds().intersects(_gameManager->getPaddle()->getBounds()))
    {
        _direction.y *= -1; // Bounce vertically

        float paddlePositionProportion = (_sprite.getPosition().x - _gameManager->getPaddle()->getBounds().left) / _gameManager->getPaddle()->getBounds().width;
        _direction.x = paddlePositionProportion * 2.0f - 1.0f;

        // Adjust position to avoid getting stuck inside the paddle
        _sprite.setPosition(_sprite.getPosition().x, _gameManager->getPaddle()->getBounds().top - 2 * RADIUS);

        // Set consecutive brick count to 0
        _consecutiveBrickHits = 0;

        // Paddle jiggle
        _gameManager->getTweenManager()->addTweenWithCallback(1, 1.5f, 10, TweenManager::EasingFunction::SINE_IN_OUT,
            [&](float value) {
                _gameManager->getPaddle()->setWidth(value, 1.0f);
            },
            [&]() {
                _gameManager->getTweenManager()->addTween(1.5f, 1, 5, TweenManager::EasingFunction::BOUNCE_OUT,
                    [&](float value) {
                        _gameManager->getPaddle()->setWidth(value, 1.0f);
                    });
            });

        // Audio
        _paddleHit_Sound.play();
    }

    // collision with bricks
    int collisionResponse = _gameManager->getBrickManager()->checkCollision(_sprite, _direction);
    if (_isFireBall) return; // no collisisons when in fireBall mode.
    if (collisionResponse != 0) {
        ++_consecutiveBrickHits;
        _gameManager->getTweenManager()->addTweenWithCallback(RADIUS, RADIUS * 1.5f, 10, TweenManager::EasingFunction::SINE_IN_OUT,
            [&](float value) {
                _sprite.setRadius(value);
            },
            [&]() {
                _gameManager->getTweenManager()->addTween(RADIUS * 1.5f, RADIUS, 10, TweenManager::EasingFunction::SINE_IN_OUT,
                    [&](float value) {
                        _sprite.setRadius(value);
                    });
            });

        // Play sound with pitch increase
        _brickSmash_Sound.setPitch(1 + 0.1f * _consecutiveBrickHits);
        _brickSmash_Sound.play();
    }
    if (collisionResponse == 1)
    {
        _direction.x *= -1; // Bounce horizontally
    }
    else if (collisionResponse == 2)
    {
        _direction.y *= -1; // Bounce vertically
    }
}

void Ball::render()
{
    _window->draw(_sprite);
}

void Ball::setVelocity(float coeff, float duration)
{
    _velocity = coeff * VELOCITY;
    _timeWithPowerupEffect = duration;
}

void Ball::setFireBall(float duration)
{
    if (duration) 
    {
        _isFireBall = true;
        _timeWithPowerupEffect = duration;        
        return;
    }
    _isFireBall = false;
    _timeWithPowerupEffect = 0.f;    
}

int Ball::getConsecutiveBrickHits()
{
    return _consecutiveBrickHits;
}
