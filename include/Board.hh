#ifndef BOARD_HH
#define BOARD_HH

#include <SFML/Graphics.hpp>

class Board {
public:
    Board();
    void draw(sf::RenderWindow& window) const;
    void highlightTile(sf::RenderWindow& window, int x, int y);
};

#endif // BOARD_HH
