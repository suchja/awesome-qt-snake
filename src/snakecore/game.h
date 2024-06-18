#ifndef GAME_H
#define GAME_H

#include <QObject>
#include <QRect>

class Snake;

class Game : public QObject
{
    Q_OBJECT

public:
    Game(int board_row_count, int board_column_count, QObject* parent = nullptr);

    QRect getBoardDimensions() const;
    QPoint getSnakeHeadPosition() const;

private:
    Snake* m_snake;
    const int m_board_row_count;
    const int m_board_column_count;
};

#endif // GAME_H
