#include "Piece.hh"

Piece::Piece(int x, int y, sf::Color color, const Config& cfg)
     : x(x), 
       y(y), 
       alive(true), 
       king(false), 
       color(color), 
       config(cfg) {}

void Piece::getX() const {
    return x;
}

void Piece::getY() const {
    return y;
}

void Piece::isAlive() const {
    return alive;
}

void Piece::isKing() const {
    return king;
}

void Piece::draw(sf::RenderWindow& window) const {
    // Do not draw if piece is dead
    if (!alive) {
        return;
    }

    // Set piece dimensions based on config
    float pieceRadius = config.tileSize * 0.4f;
    float offset = (config.tileSize - (2 * pieceRadius)) / 2.0f;
    sf::CircleShape piece(pieceRadius);
    piece.setFillColor(color);

    // Highlight king for now
    if (isKing) {
        piece.setOutlineThickness(config.tileSize * 0.1f);
        piece.setOutlineColor(sf::Color::Yellow);
    }

    piece.setPosition({
        static_cast<float>(x) * config.tileSize + offset,
        static_cast<float>(y) * config.tileSize + offset
    });

    window.draw(piece);
}