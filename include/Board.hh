#ifndef BOARD_HH
#define BOARD_HH

#include <SFML/Graphics.hpp>
#include "Config.hh"

class Board {
private:
    const Config& config;
public:
    Board(const Config& cfg);
    void draw(sf::RenderWindow& window) const;
    void highlightTile(sf::RenderWindow& window, int x, int y);
};

#endif // BOARD_HH
