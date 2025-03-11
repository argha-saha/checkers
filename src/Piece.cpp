#include "Piece.hh"

Piece::Piece(int x, int y, sf::Color color, const Config& cfg)
     : x(x), 
       y(y), 
       color(color), 
       alive(true), 
       king(false), 
       config(cfg) {}

int Piece::getX() const {
    return x;
}

int Piece::getY() const {
    return y;
}

sf::Color Piece::getColor() const {
    return color;
}

bool Piece::isAlive() const {
    return alive;
}

bool Piece::isKing() const {
    return king;
}

bool Piece::isOpponent(Piece* other) const {
    return color != other->getColor();
}

void Piece::setX(int _x) {
    x = _x;
}

void Piece::setY(int _y) {
    y = _y;
}

void Piece::setAlive(bool _alive) {
    alive = _alive;
}

void Piece::setKing(bool _king) {
    king = _king;
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
    if (king) {
        piece.setOutlineThickness(config.tileSize * 0.1f);
        piece.setOutlineColor(sf::Color::Yellow);
    }

    piece.setPosition({
        static_cast<float>(x) * config.tileSize + offset,
        static_cast<float>(y) * config.tileSize + offset
    });

    window.draw(piece);
}