#include "Game.hh"
#include "Config.hh"

Game::Game(const Config& cfg) 
    : config(cfg),
      window(sf::VideoMode({
          static_cast<unsigned int>(config.tileSize * config.boardSize),
          static_cast<unsigned int>(config.tileSize * config.boardSize)
      }), "Checkers"),
      board(cfg),
      turn(TurnColor::RED),
      selectedPiece(nullptr)
{
    setupBoard();
}

void Game::run() {
    while (window.isOpen()) {
        processEvents();
        updateState();
        render();
    }
}

void Game::setupBoard() {
    // Setup black pieces
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 8; ++j) {
            // Alternate tiles
            if ((i + j) % 2 == 0) {
                blackPieces.push_back(std::make_unique<Piece>(j, i, sf::Color::Black, config));
            }
        }
    }

    // Setup red pieces
    for (int i = 5; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            if ((i + j) % 2 == 0) {
                redPieces.push_back(std::make_unique<Piece>(j, i, sf::Color::Red, config));
            }
        }
    }
}

void Game::processEvents() {
    while (const std::optional event = window.pollEvent()) {
        // Handle window close
        if (event->is<sf::Event::Closed>()) {
            window.close();
        }

        // Handle mouse click
        if (event->is<sf::Event::MouseButtonPressed>()) {
            handleMouseClick();
        }
    }
}

void Game::handleMouseClick() {

}

Piece* Game::getPieceAt(int x, int y) const {
    for (const auto& piece : redPieces) {
        if (piece->getX() == x && piece->getY() == y) {
            return piece.get();
        }
    }

    for (const auto& piece : blackPieces) {
        if (piece->getX() == x && piece->getY() == y) {
            return piece.get();
        }
    }

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
        piece->draw(window);
    }

    // Draw black pieces
    for (const auto& piece : blackPieces) {
        piece->draw(window);
    }

    window.display();
}