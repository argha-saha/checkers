#include "Game.hh"
#include <iostream>

using std::cout;
using std::endl;

void tests() {
    Config config {80, 8};
    Game game(config);
    
    sf::Color color = game.getTurnColor();
    
    if (color == sf::Color::Black) {
        cout << "Color is black" << endl;
    } else {
        cout << "Color is red" << endl;
    }
}

int main() {
    tests();
    return 0;
}