#include "Brick.h"

Brick::Brick(float x, float y, float width, float height, std::shared_ptr<sf::Texture> twixTexture)
    : _isDestroyed(false), _twixTexture(twixTexture)
{
    _shape.setPosition(x, y);
    _shape.setSize(sf::Vector2f(width, height));
    _shape.setFillColor(sf::Color::Red);
}

void Brick::render(sf::RenderWindow& window)
{
    if (!_isDestroyed) {
        window.draw(_shape);
    }
}

sf::FloatRect Brick::getBounds() const
{
    return _shape.getGlobalBounds();
}

void Brick::twixify()
{
    _shape.setTexture(_twixTexture.get());
    _shape.setFillColor(sf::Color::White);
}
