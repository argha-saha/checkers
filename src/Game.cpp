#include "Game.hh"
#include "Config.hh"
#include <iostream>

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
      redPiecesCount(0),
      blackPiecesCount(0),
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

        if (restartPending && restartClock.getElapsedTime().asSeconds() >= 2.0f) {
            restartGame();
            restartPending = false;
        }
    }
}

void Game::setupBoard() {
    gameActive = true;
    redPiecesCount = 0;
    blackPiecesCount = 0;

    // Setup black pieces
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 8; ++j) {
            // Alternate tiles
            if ((i + j) % 2 == 0) {
                blackPieces.push_back(std::make_unique<Piece>(j, i, sf::Color::Black, config));
                ++blackPiecesCount;
            }
        }
    }

    // Setup red pieces
    for (int i = 5; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            if ((i + j) % 2 == 0) {
                redPieces.push_back(std::make_unique<Piece>(j, i, sf::Color::Red, config));
                ++redPiecesCount;
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

            if (enemy->getColor() == sf::Color::Red) {
                --redPiecesCount;
            } else {
                --blackPiecesCount;
            }

            switchTurnColor();

            if (redPiecesCount == 0) {
                winner = TurnColor::BLACK;
                endGame();
            } else if (blackPiecesCount == 0) {
                winner = TurnColor::RED;
                endGame();
            }

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
        } else {
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

void Game::drawGameOver() {
    sf::Vector2f rectDim(
        (config.tileSize * config.boardSize) / 2, 
        (config.tileSize * config.boardSize) / 2
    );

    sf::RectangleShape rect(rectDim);
    rect.setFillColor(sf::Color::Black);
    rect.setOutlineColor(sf::Color::White);
    rect.setOutlineThickness(2);

    sf::Vector2f center(
        (config.tileSize * config.boardSize) / 4, 
        (config.tileSize * config.boardSize) / 4
    );

    rect.setPosition(center);

    sf::Font font("assets/Inter.ttf");
    sf::Text text(font, "", 32);
    text.setPosition({static_cast<float>(center.x) * 1.45f, static_cast<float>(center.y) * 1.5f});

    if (winner == TurnColor::RED) {
        text.setString("Red Wins!");
    } else {
        text.setString("Black Wins!");
    }

    text.setFillColor(sf::Color::White);

    window.draw(rect);
    window.draw(text);
}

void Game::endGame() {
    gameActive = false;
    restartClock.restart();
    restartPending = true;
}

void Game::restartGame() {
    // Clear pieces
    redPieces.clear();
    redPiecesCount = 0;
    blackPieces.clear();
    blackPiecesCount = 0;

    // Set initial state
    setupBoard();
    turn = TurnColor::RED;
    gameActive = true;
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

    // Draw game over screen
    if (!gameActive) {
        drawGameOver();
    }

    window.display();
}