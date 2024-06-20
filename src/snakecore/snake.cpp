#include "snake.h"

Snake::Snake(int board_row_count, int board_column_count, QObject *parent) :
    QObject{parent},
    m_board_row_count(board_row_count),
    m_board_column_count(board_column_count)
{
    m_move_direction = Direction::NoMove;

    m_head = QPoint(m_board_row_count/2, m_board_column_count/2);
    QPoint body_element(m_head.x() - 1, m_head.y());
    m_body << body_element;
}

QPoint Snake::getHead() const
{
    return m_head;
}

QList<QPoint> Snake::getBody() const
{
    return m_body;
}

bool Snake::isMoving() const
{
    return m_move_direction != Direction::NoMove;
}

void Snake::setMoveDirection(Direction new_direction)
{
    m_move_direction = new_direction;
}

void Snake::executeMove()
{
    m_body << m_head;
    m_body.removeFirst();

    if (m_move_direction == Direction::MoveRight)
    {
        m_head = QPoint(m_head.x() + 1, m_head.y());
    }
    else if (m_move_direction == Direction::MoveLeft)
    {
        m_head = QPoint(m_head.x() - 1, m_head.y());
    }
    else if (m_move_direction == Direction::MoveDown)
    {
        m_head = QPoint(m_head.x(), m_head.y() + 1);
    }
    else if (m_move_direction == Direction::MoveUp)
    {
        m_head = QPoint(m_head.x(), m_head.y() - 1);
    }
}
