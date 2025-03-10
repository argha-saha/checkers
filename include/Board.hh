#ifndef BOARD_HH
#define BOARD_HH

#include <SFML/Graphics.hpp>

class Board {
public:
    Board();
    void draw(sf::RenderWindow& window) const;
};

#endif // BOARD_HH
