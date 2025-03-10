#ifndef GAME_HH
#define GAME_HH

#include <SFML/Graphics.hpp>
#include <memory>
#include "Board.hh"
#include "Checkers.hh"
#include "Piece.hh"

class Game {
private:
    sf::RenderWindow window;
    Board board;
    std::vector<std::unique_ptr<Piece>> redPieces;
    std::vector<std::unique_ptr<Piece>> blackPieces;
    TurnColor turn;
    Piece* selectedPiece;

    void setupBoard();
    Piece* getPieceAt(int x, int y) const;
    sf::Color getTurnColor() const;
    void switchTurn();
    void updateGameState();
    void render();
public:
    Game();
    void run();
};

#endif // GAME_HH