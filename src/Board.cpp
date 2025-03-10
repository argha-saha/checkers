#include "Board.hh"

Board::Board(const Config& cfg) : config(cfg) {}

void Board::draw(sf::RenderWindow& window) const {
    sf::RectangleShape tile({
        static_cast<float>(config.tileSize),
        static_cast<float>(config.tileSize)
    });

    for (int i = 0; i < config.boardSize; ++i) {
        for (int j = 0; j < config.boardSize; ++j) {
            tile.setPosition({
                static_cast<float>(i) * config.tileSize,
                static_cast<float>(j) * config.tileSize
            });
            
            if ((i + j) % 2 == 0) {
                tile.setFillColor(sf::Color(255, 240, 200));
            } else {
                tile.setFillColor(sf::Color(150, 105, 100));
            }
            
            window.draw(tile);
        }
    }
}

void Board::highlightTile(sf::RenderWindow& window, int x, int y) {
    sf::RectangleShape tile({
        static_cast<float>(config.tileSize),
        static_cast<float>(config.tileSize)
    });

    // Configure tile
    tile.setFillColor(sf::Color(128, 0, 255, 128));
    tile.setPosition({
        static_cast<float>(x) * config.tileSize,
        static_cast<float>(y) * config.tileSize
    });

    window.draw(tile);
}