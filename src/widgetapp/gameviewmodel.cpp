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

QPoint GameViewModel::getSnakeHeadPosition() const
{
    QPoint head = m_game_model->getSnakeHeadPosition();
    return head * m_tile_size;
}

QList<QPoint> GameViewModel::getSnakeBodyPositions() const
{
    QList<QPoint> body = m_game_model->getSnakeBodyPositions();

    for (QPoint &s : body) {
        s *= m_tile_size;
    }

    return body;
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
    updateUserMessage(UserMessages::None);
    m_current_message = UserMessages::None;
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
        updateUserMessage(UserMessages::KeyNotSupported);
        return false;
    }

    updateUserMessage(UserMessages::None);
    return true;
}

void GameViewModel::executeMove()
{
    m_game_model->executeMove();
    emit gameUpdated();
}

void GameViewModel::updateUserMessage(UserMessages new_message)
{
    if (m_current_message == new_message)
        return;

    if (!m_game_model->isGameStarted())
    {
        if (new_message != UserMessages::None)
            return;
    }

    m_current_message = new_message;
    emit userMessageUpdated(m_current_message);
}
