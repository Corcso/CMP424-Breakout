#include "BrickManager.h"
#include "GameManager.h"

BrickManager::BrickManager(sf::RenderWindow* window, GameManager* gameManager)
    : _window(window), _gameManager(gameManager)
{
    _twixTexture = std::make_shared<sf::Texture>();
    _twixTexture->loadFromFile("./Assets/twix.png");
}

void BrickManager::createBricks(int rows, int cols, float brickWidth, float brickHeight, float spacing)
{
    float leftEdge;
    if (cols % 2 == 0) 
        leftEdge = _window->getSize().x / 2 - ((cols / 2.0f) * brickWidth + (cols / 2.0f - 0.5f) * spacing);
    else
        leftEdge = _window->getSize().x / 2 - ((cols / 2.0f - 0.5f) * brickWidth + (cols / 2.0f) * spacing);

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            float x = j * (brickWidth + spacing) + leftEdge;
            float y = i * (brickHeight + spacing) + TOP_PADDING;
            _bricks.emplace_back(x, y, brickWidth, brickHeight, _twixTexture);
        }
    }
}

void BrickManager::render()
{
    for (auto& brick : _bricks) {
        brick.render(*_window);
    }
}

int BrickManager::checkCollision(sf::CircleShape& ball, sf::Vector2f& direction)
{
    int collisionResponse = 0;  // set to 1 for horizontal collision and 2 for vertical.
    for (auto& brick : _bricks) {
        if (!brick.getBounds().intersects(ball.getGlobalBounds())) continue;    // no collision, skip.

        sf::Vector2f ballPosition = ball.getPosition();
        float ballY = ballPosition.y + 0.5f * ball.getGlobalBounds().height;
        sf::FloatRect brickBounds = brick.getBounds();

        // default vertical bounce (collision is top/bottom)
        collisionResponse = 2;
        if (ballY > brickBounds.top && ballY < brickBounds.top + brickBounds.height)
            // unless it's horizontal (collision from side)
            collisionResponse = 1;

        // Mark the brick as destroyed (for simplicity, let's just remove it from rendering)
        // In a complete implementation, you would set an _isDestroyed flag or remove it from the vector
        brick = _bricks.back();
        _bricks.pop_back();
        break;
    }
    if (_bricks.size() == 0)
    {
        _gameManager->levelComplete();
    }
    return collisionResponse;
}

int BrickManager::getBricksLeft()
{
    return _bricks.size();
}

void BrickManager::removeBricksRandom(int count)
{
    for (int b = 0; b < count; b++) {
        int toRemoveIndex = rand() % _bricks.size();

        _bricks.erase(_bricks.begin() + toRemoveIndex);
    }
}

void BrickManager::twixifyAllBricks()
{
    for (auto& brick : _bricks) {
        brick.twixify();
    }
}

void BrickManager::createPartyBricks(int rows, int cols, float brickWidth, float brickHeight, float spacing)
{
    float leftEdge;
    if (cols % 2 == 0)
        leftEdge = _window->getSize().x / 2 - ((cols / 2.0f) * brickWidth + (cols / 2.0f - 0.5f) * spacing);
    else
        leftEdge = _window->getSize().x / 2 - ((cols / 2.0f - 0.5f) * brickWidth + (cols / 2.0f) * spacing);

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            float x = j * (brickWidth + spacing) + leftEdge;
            float y = i * (brickHeight + spacing) + TOP_PADDING;
            _bricks.emplace_back(x, y, brickWidth, brickHeight, _twixTexture);
        }
    }

    for (auto& brick : _bricks) {
        brick.twixify();
    }
    
    for (auto& brick : _bricks) {
        _gameManager->getTweenManager()->addTween(0, 1000, 0.001f, TweenManager::EasingFunction::LINEAR_IN_OUT,
            [&](float value) {
                value = value - floor(value);
                float r = (value < 0.33f) ? (0.33f - value) * 3.0f : (value < 0.66f) ? 0.0f : (value - 0.66f) * 3.0f;
                float g = (value < 0.33f) ? (value - 0.0f) * 3.0f : (value < 0.66f) ? (0.66f - value) * 3.0f : 0.0f;
                float b = (value < 0.33f) ? 0.0f : (value < 0.66f) ? (value - 0.33f) * 3.0f : (1.0f - value) * 3.0f;
                r *= 255;
                g *= 255;
                b *= 255;
                brick.setColor(sf::Color(r, g, b));
            });
    }
    
}
