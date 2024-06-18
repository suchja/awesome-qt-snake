#include "game.h"
#include "snake.h"

Game::Game(int board_row_count, int board_column_count, QObject *parent) :
    QObject{parent},
    m_board_row_count(board_row_count),
    m_board_column_count(board_column_count)
{
    m_snake = new Snake(m_board_row_count, m_board_column_count, this);
}

QRect Game::getBoardDimensions() const
{
    return QRect(0, 0, m_board_column_count, m_board_row_count);
}

QPoint Game::getSnakeHeadPosition() const
{
    return m_snake->getHead();
}

QList<QPoint> Game::getSnakeBodyPositions() const
{
    return m_snake->getBody();
}
