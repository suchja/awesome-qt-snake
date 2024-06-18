#include "gameviewmodel.h"


GameViewModel::GameViewModel(Game *model, QObject *parent) :
    QObject{parent},
    m_game_model(model)
{}

QRect GameViewModel::getBoardDimensions() const
{
    QRect internal = m_game_model->getBoardDimensions();
    return QRect(internal.left() * m_tile_size,
                 internal.top() * m_tile_size,
                 internal.width() * m_tile_size,
                 internal.height() * m_tile_size);
}

QList<QPoint> GameViewModel::getSnakePositions() const
{
    QPoint head = m_game_model->getSnakeHeadPosition();
    QList<QPoint> snake = m_game_model->getSnakeBodyPositions();
    snake.push_front(head);

    for (QPoint &s : snake) {
        s *= m_tile_size;
    }

    return snake;
}

QPoint GameViewModel::getFoodPosition() const
{
    return m_game_model->getFoodPosition() * m_tile_size;
}
