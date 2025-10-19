#pragma once
#include <SFML/Graphics.hpp>

class Brick {
public:
    Brick(float x, float y, float width, float height, std::shared_ptr<sf::Texture> twixTexture);
    void render(sf::RenderWindow& window);
    sf::FloatRect getBounds() const;

    /// <summary>
    /// Set this bricks sprite image to a twix
    /// </summary>
    void twixify();

private:
    sf::RectangleShape _shape;
    std::shared_ptr<sf::Texture> _twixTexture;
    bool _isDestroyed;
};