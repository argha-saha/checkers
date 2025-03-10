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
    int getX() const;
    int getY() const;
    bool isAlive() const;
    bool isKing() const;
    bool isOpponent(const Piece& other) const;
    void draw(sf::RenderWindow& window) const;
};

#endif // PIECE_HH