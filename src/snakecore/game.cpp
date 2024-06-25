#include "game.h"
#include "snake.h"
#include "foodgenerator.h"
#include "snakecore.h"

Game::Game(int board_row_count, int board_column_count, int snake_body_length, QObject *parent) :
    QObject{parent},
    m_board_row_count(board_row_count),
    m_board_column_count(board_column_count)
{
    m_snake = new Snake(m_board_row_count, m_board_column_count, snake_body_length, this);
    m_food_generator = new FoodGenerator(m_board_row_count, m_board_column_count, this);
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

QPoint Game::getFoodPosition() const
{
    QList<QPoint> occupied_positions;
    addOccupiedPositions(occupied_positions);

    return m_food_generator->getFoodOnRandomEmptyPosition(occupied_positions);
}

DirectionChangeResult Game::setMoveDirection(Direction new_direction)
{
    if (!m_snake->isMoving() && (new_direction != Direction::NoMove))
    {
        emit isStarted();
    }

    return m_snake->setMoveDirection(new_direction);
}

void Game::executeMove()
{
    m_snake->executeMove();
}

void Game::addOccupiedPositions(QList<QPoint>& positions) const
{
    QList<QPoint> body = m_snake->getBody();
    foreach (QPoint element, body) {
        positions << element;
    }
    positions << m_snake->getHead();
    positions << m_food;
}

bool Game::isGameStarted()
{
    return m_snake->isMoving();
}
