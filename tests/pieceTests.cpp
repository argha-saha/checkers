#include "Piece.hh"
#include <cassert>
#include <SFML/Graphics.hpp>

void tests() {
    Piece piece(0, 0, sf::Color::Red);
    assert(piece.getX() == 0);
    assert(piece.getY() == 0);
    assert(piece.isAlive() == true);
    assert(piece.isKing() == false);
}

int main() {
    tests();
    return 0;
}