#include "Piece.hh"

Piece::Piece(int x, int y, sf::Color color)
     : x(x), y(y), alive(true), 
       king(false), color(color) {}

void Piece::getX() const {
    return x;
}

void Piece::getY() const {
    return y;
}

void Piece::isAlive() const {
    return alive;
}

void Piece::isKing() const {
    return king;
}