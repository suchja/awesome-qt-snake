#include "game.h"

#include <QDebug>

Game::Game(int board_row_count, int board_column_count, QObject *parent) :
    QObject{parent},
    m_board_row_count(board_row_count),
    m_board_column_count(board_column_count)
{}

QRect Game::getBoardDimensions() const
{
    return QRect(0, 0, m_board_column_count, m_board_row_count);
}
