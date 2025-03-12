#ifndef GAME_HH
#define GAME_HH

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
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
    int redPiecesCount;
    int blackPiecesCount;
    TurnColor turn;
    Piece* selectedPiece;
    bool gameActive;
    TurnColor winner;
    sf::Clock restartClock;
    bool restartPending = false;

    void setupBoard();
    void processEvents();
    Piece* getPieceAt(int x, int y) const;
    sf::Color getTurnColor() const;
    void switchTurnColor();
    void handleMouseClick();
    void updateState();
    void endGame();
    void drawGameOver();
    void restartGame();
    void render();

public:
    Game(const Config& cfg);
    bool isValidMove(Piece* piece, int toX, int toY);
    void run();
};

#endif // GAME_HH