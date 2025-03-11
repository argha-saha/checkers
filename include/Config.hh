#ifndef CONFIG_HH
#define CONFIG_HH

struct Config {
    int tileSize;
    int boardSize;

    Config(int tileSize, int boardSize) : tileSize(tileSize), boardSize(boardSize) {}
};

#endif // CONFIG_HH