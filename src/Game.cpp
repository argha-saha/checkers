#include "Game.hh"
#include "Config.hh"
#include <SFML/Window/ContextSettings.hpp>
#include <SFML/Window/WindowEnums.hpp>

Game::Game(const Config& cfg) 
    : config(cfg),
      window(sf::VideoMode({
          static_cast<unsigned int>(config.tileSize * config.boardSize),
          static_cast<unsigned int>(config.tileSize * config.boardSize)
      }), 
      "Checkers",
      sf::State::Windowed,
      sf::ContextSettings{0, 0, 4}),
      board(cfg),
      turn(TurnColor::RED),
      selectedPiece(nullptr),
      gameActive(false)
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
    gameActive = true;

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

Piece* Game::getPieceAt(int x, int y) const {
    for (const auto& piece : redPieces) {
        // Check if piece is alive and at the correct position
        if (piece->isAlive() && piece->getX() == x && piece->getY() == y) {
            return piece.get();
        }
    }

    for (const auto& piece : blackPieces) {
        if (piece->isAlive() && piece->getX() == x && piece->getY() == y) {
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

bool Game::isValidMove(Piece* piece, int toX, int toY) {
    // Bounds check
    if (toX < 0 || toX >= config.boardSize || toY < 0 || toY >= config.boardSize) {
        return false;
    }

    bool allowed = piece->allowedMove(toX, toY).first;
    bool capture = piece->allowedMove(toX, toY).second;

    // Check if move is allowed
    if (!allowed) {
        return false;
    }
    
    // Tile must be unoccupied
    if (getPieceAt(toX, toY)) {
        return false;
    }

    // Non-capture move
    if (!capture) {
        piece->setX(toX);
        piece->setY(toY);
        switchTurnColor();
        return true;
    }

    // Capture move
    if (capture) {
        int midRow = (toX + piece->getX()) / 2;
        int midCol = (toY + piece->getY()) / 2;

        // Check if enemy piece exists
        Piece* enemy = getPieceAt(midRow, midCol);

        if (enemy && piece->isOpponent(enemy)) {
            // Update position and kill enemy
            piece->setX(toX);
            piece->setY(toY);
            enemy->setAlive(false);
            switchTurnColor();
            return true;
        }
    }

    return false;
}

void Game::handleMouseClick() {
    int x = sf::Mouse::getPosition(window).x / config.tileSize;
    int y = sf::Mouse::getPosition(window).y / config.tileSize;
    Piece* clicked = getPieceAt(x, y);

    if (clicked && clicked->getColor() == getTurnColor()) {
        selectedPiece = clicked;
    } else if (selectedPiece) {
        // Deselect piece
        if (isValidMove(selectedPiece, x, y)) {
            selectedPiece = nullptr;
        }
    }
}

void Game::switchTurnColor() {
    if (turn == TurnColor::RED) {
        turn = TurnColor::BLACK;
    } else {
        turn = TurnColor::RED;
    }
}

void Game::updateState() {
    for (auto& piece : redPieces) {
        // If red piece reaches the top, upgrade to king
        if (piece->isAlive() && piece->getY() == 0) {
            piece->setKing(true);
        }
    }

    for (auto& piece : blackPieces) {
        // If black piece reaches the bottom, upgrade to king
        if (piece->isAlive() && piece->getY() == config.boardSize - 1) {
            piece->setKing(true);
        }
    }
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

void Game::endGame() {
    gameActive = false;
}

void Game::restartGame() {
    gameActive = true;
    setupBoard();
}