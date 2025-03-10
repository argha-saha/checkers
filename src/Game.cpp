#include "Game.hh"
#include "Config.hh"

Game::Game() 
    : config(Config(80, 8)),
      window(sf::VideoMode({
          config.tileSize * config.boardSize,
          config.tileSize * config.boardSize
      }), "Checkers"),
      board(config),
      turn(TurnColor::RED),
      selectedPiece(nullptr)
{
    setupBoard();
}

Game::Game(const Config& cfg) 
    : config(cfg),
      window(sf::VideoMode({
          config.tileSize * config.boardSize,
          config.tileSize * config.boardSize
      }), "Checkers"),
      board(cfg),
      turn(TurnColor::RED),
      selectedPiece(nullptr)
{
    setupBoard();
}

void Game::run() {
    processEvents();
}

void Game::setupBoard() {
    // Setup black pieces
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 8; ++j) {
            // Alternate tiles
            if ((i + j) % 2 == 0) {
                blackPieces.push_back(std::make_unique<Piece>(j, i, sf::Color::Black));
            }
        }
    }

    // Setup red pieces
    for (int i = 5; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            if ((i + j) % 2 == 0) {
                redPieces.push_back(std::make_unique<Piece>(j, i, sf::Color::Red));
            }
        }
    }
}

void Game::processEvents() {
    while (auto event = window.pollEvent()) {
        // Handle window close
        if (event->is<sf::Event::Closed>()) {
            window.close();
        }

        // Handle mouse click
        if (event->is<sf::Event::MouseButtonPressed>()) {
            handleClick();
        }
    }
}

void Game::handleMouseClick() {

}

Piece* Game::getPieceAt(int x, int y) const {
    return nullptr;
}

sf::Color Game::getTurnColor() const {
    if (turn == TurnColor::RED) {
        return sf::Color::Red;
    } else {
        return sf::Color::Black;
    }
}

void Game::switchTurn() {
    if (turn == TurnColor::RED) {
        turn = TurnColor::BLACK;
    } else {
        turn = TurnColor::RED;
    }
}

void Game::updateState() {

}

void Game::render() {
    window.clear();
    board.draw(window);

    if (selectedPiece) {
        board.highlightTile(window, selectedPiece->getX(), selectedPiece->getY());
    }

    // Draw red pieces
    for (const auto& piece : redPieces) {
        // TODO: Check if piece needs config argument
        piece->draw(window);
    }

    // Draw black pieces
    for (const auto& piece : blackPieces) {
        piece->draw(window);
    }

    window.display();
}