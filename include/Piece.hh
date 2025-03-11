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

    // Getters
    int getX() const;
    int getY() const;
    sf::Color getColor() const;
    bool isAlive() const;
    bool isKing() const;
    bool isOpponent(Piece* other) const;

    // Setters
    void setX(int _x);
    void setY(int _y);
    void setAlive(bool _alive);
    void setKing(bool _king);

    /*
    Returns a pair of booleans: 
    pair.first is true if move is allowed
    pair.second is true if it's a capture move
    */
    std::pair<bool, bool> allowedMove(int toX, int toY);
    void draw(sf::RenderWindow& window) const;
};

#endif // PIECE_HH