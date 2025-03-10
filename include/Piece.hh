#ifndef PIECE_HH
#define PIECE_HH

class Piece {
private:
    int x;
    int y;
    sf::Color color;
    bool alive;
    bool king;

public:
    Piece(int x, int y, sf::Color color);
    void draw(sf::RenderWindow& window) const;
    void getX() const;
    void getY() const;
    void isAlive() const;
    void isKing() const;
};

#endif // PIECE_HH