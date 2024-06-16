#ifndef GAME_H
#define GAME_H

#include <QRect>

class Game
{
public:
    Game(int board_row_count, int board_column_count);

    QRect getBoardDimensions();

private:
    int m_board_row_count;
    int m_board_column_count;
};

#endif // GAME_H
