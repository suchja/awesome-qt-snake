#include "gameviewmodel.h"
#include "snakecore.h"
#include "game.h"

GameViewModel::GameViewModel(Game *model, QObject *parent) :
    QObject{parent},
    m_game_model(model),
    m_current_message(UserMessages::StartGame)
{
    connect(m_game_model, SIGNAL(isStarted()), this, SLOT(startGame()));
}

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

UserMessages GameViewModel::getCurrentUserMessage() const
{
    return m_current_message;
}

void GameViewModel::startGame()
{
    emit gameStarted();
}

bool GameViewModel::processKeyboardAction(int key_code)
{
    switch (key_code)
    {
    case Qt::Key_Left:
        m_game_model->setMoveDirection(Direction::MoveLeft);
        break;
    case Qt::Key_Right:
        m_game_model->setMoveDirection(Direction::MoveRight);
        break;
    case Qt::Key_Up:
        m_game_model->setMoveDirection(Direction::MoveUp);
        break;
    case Qt::Key_Down:
        m_game_model->setMoveDirection(Direction::MoveDown);
        break;
    default:
        return false;
    }

    return true;
}

void GameViewModel::executeMove()
{
    m_game_model->executeMove();
}
