#ifndef GAME_HH
#define GAME_HH

#include <SFML/Graphics.hpp>

class Game {
private:
    sf::RenderWindow window;
public:
    Game();
    void run();
};

#endif // GAME_HH