#ifndef GAME_HH
#define GAME_HH

#include <SFML/Graphics.hpp>
#include <memory>
#include "Board.hh"
#include "Checkers.hh"
#include "Piece.hh"

class Game {
private:
    Config config;
    sf::RenderWindow window;
    Board board;
    std::vector<std::unique_ptr<Piece>> redPieces;
    std::vector<std::unique_ptr<Piece>> blackPieces;
    TurnColor turn;
    Piece* selectedPiece;

    void setupBoard();
    void processEvents();
    Piece* getPieceAt(int x, int y) const;
    sf::Color getTurnColor() const;
    void switchTurnColor();
    void handleMouseClick();
    void updateState();
    void render();

public:
    Game(const Config& cfg);
    bool isValidMove(Piece* piece, int toX, int toY);
    void run();

    // For Testing
    // sf::Color getTurnColor() const;
};

#endif // GAME_HH