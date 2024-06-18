#include "snake.h"

Snake::Snake(int board_row_count, int board_column_count, QObject *parent) :
    QObject{parent},
    m_board_row_count(board_row_count),
    m_board_column_count(board_column_count)
{
    m_head_position = QPoint(m_board_row_count/2, m_board_column_count/2);
}

QPoint Snake::getHeadPosition() const
{
    return m_head_position;
}
