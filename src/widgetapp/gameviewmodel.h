#ifndef GAMEVIEWMODEL_H
#define GAMEVIEWMODEL_H

#include <QObject>
#include <QRect>
#include <QPoint>

#include "game.h"

enum class UserMessages {
    None,
    StartGame
};

class GameViewModel : public QObject
{
    Q_OBJECT
public:
    explicit GameViewModel(Game* model, QObject *parent = nullptr);

    static constexpr int getTileSize() {return m_tile_size;}

    QRect getBoardDimensions() const;
    QList<QPoint> getSnakePositions() const;
    QPoint getFoodPosition() const;

    UserMessages getCurrentUserMessage() const;

    bool processKeyboardAction(int key_code);

signals:

private:
    static constexpr int m_tile_size = 20;

    Game* m_game_model;
    UserMessages m_current_message;
};

#endif // GAMEVIEWMODEL_H
