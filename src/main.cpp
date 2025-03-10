#include "Config.hh"
#include "Game.hh"

int main() {
    Config config {80, 8};
    Game game(config);
    game.run();
    return 0;
}