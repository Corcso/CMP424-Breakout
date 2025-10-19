#pragma once
#include <vector>
#include "Brick.h"
#include <SFML/Graphics.hpp>

class GameManager;

class BrickManager {
public:
    BrickManager(sf::RenderWindow* window, GameManager* gameManager);
    void createBricks(int rows, int cols, float brickWidth, float brickHeight, float spacing);
    void render();
    int checkCollision(sf::CircleShape& ball, sf::Vector2f& direction);
    /// <summary>
    /// Returns the number of active bricks on the board.
    /// </summary>
    /// <returns>Nuber of bricks</returns>
    int getBricksLeft();
    
    /// <summary>
    /// Removes the provided number of bricks
    /// </summary>
    /// <param name="count">Number to remove, default 1</param>
    void removeBricksRandom(int count = 1);

    /// <summary>
    /// Twixifies all bricks, see Brick::twixify()
    /// </summary>
    void twixifyAllBricks();
private:
    std::vector<Brick> _bricks;
    sf::RenderWindow* _window;
    std::shared_ptr<sf::Texture> _twixTexture; // Hold here for all bricks

    GameManager* _gameManager;
    static constexpr float TOP_PADDING = 100.0f;
};
