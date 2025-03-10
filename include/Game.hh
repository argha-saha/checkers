#ifndef GAME_HH
#define GAME_HH

#include <SFML/Graphics.hpp>
#include <memory>
#include "Board.hh"
#include "Checkers.hh"
#include "Piece.hh"

class Game {
private:
    const Config& config;
    sf::RenderWindow window;
    Board board;
    std::vector<std::unique_ptr<Piece>> redPieces;
    std::vector<std::unique_ptr<Piece>> blackPieces;
    TurnColor turn;
    Piece* selectedPiece;

    void setupBoard();
    void processEvents();
    void handleMouseClick();
    Piece* getPieceAt(int x, int y) const;
    sf::Color getTurnColor() const;
    void switchTurn();
    void updateState();
    void render();
public:
    Game();
    Game(const Config& cfg);
    void run();

    // For Testing
    // sf::Color getTurnColor() const;
};

#endif // GAME_HH