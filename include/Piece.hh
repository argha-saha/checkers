#ifndef PIECE_HH
#define PIECE_HH

class Piece {
private:
    int x;
    int y;
    sf::Color color;
    bool isAlive;
    bool isKing;

public:
    Piece(int x, int y, sf::Color color);
    void draw(sf::RenderWindow& window) const;
};

#endif // PIECE_HH