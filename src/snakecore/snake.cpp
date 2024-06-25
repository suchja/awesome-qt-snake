#include "snake.h"

Snake::Snake(int board_row_count, int board_column_count, int body_count, QObject *parent) :
    QObject{parent},
    m_board_row_count(board_row_count),
    m_board_column_count(board_column_count),
    m_moved_since_last_change(true)
{
    m_move_direction = Direction::NoMove;

    m_head = QPoint(m_board_row_count/2, m_board_column_count/2);
    for (int i = 0; i < body_count; ++i) {
        m_body.prepend(QPoint(m_head.x() - (i + 1), m_head.y()));
    }
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

DirectionChangeResult Snake::setMoveDirection(Direction new_direction)
{
    if (!m_moved_since_last_change)
        return DirectionChangeResult::TooManyPerMove;

    m_moved_since_last_change = false;

    if (m_move_direction == Direction::MoveLeft && new_direction == Direction::MoveRight)
        return DirectionChangeResult::OppositeDirection;
    if (m_move_direction == Direction::MoveRight && new_direction == Direction::MoveLeft)
        return DirectionChangeResult::OppositeDirection;
    if (m_move_direction == Direction::MoveUp && new_direction == Direction::MoveDown)
        return DirectionChangeResult::OppositeDirection;
    if (m_move_direction == Direction::MoveDown && new_direction == Direction::MoveUp)
        return DirectionChangeResult::OppositeDirection;

    m_move_direction = new_direction;
    return DirectionChangeResult::Succeeded;
}

void Snake::executeMove()
{
    m_moved_since_last_change = true;

    m_body << m_head;
    m_body.removeFirst();

    if (m_move_direction == Direction::MoveRight)
    {
        m_head.rx() += 1;
        if (m_head.x() >= m_board_column_count)
            m_head.rx() = 0;
    }
    else if (m_move_direction == Direction::MoveLeft)
    {
        m_head.rx() -= 1;
        if (m_head.x() < 0)
            m_head.rx() = m_board_column_count - 1;
    }
    else if (m_move_direction == Direction::MoveDown)
    {
        m_head.ry() += 1;
        if (m_head.y() >= m_board_row_count)
            m_head.ry() = 0;
    }
    else if (m_move_direction == Direction::MoveUp)
    {
        m_head.ry() -= 1;
        if (m_head.y() < 0)
            m_head.ry() = m_board_row_count - 1;
    }
}
