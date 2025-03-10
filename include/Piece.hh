#ifndef PIECE_HH
#define PIECE_HH

#include <SFML/Graphics.hpp>
#include "Config.hh"

class Piece {
private:
    int x;
    int y;
    sf::Color color;
    bool alive;
    bool king;
    const Config& config;

public:
    Piece(int x, int y, sf::Color color, const Config& cfg);
    void getX() const;
    void getY() const;
    void isAlive() const;
    void isKing() const;
    void draw(sf::RenderWindow& window) const;
};

#endif // PIECE_HH