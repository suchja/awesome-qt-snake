#ifndef GAMEVIEWMODEL_H
#define GAMEVIEWMODEL_H

#include <QObject>
#include <QRect>
#include <QPoint>

class Game;

enum class UserMessages {
    None,
    StartGame,
    KeyNotSupported,
    WrongDirection,
    TooManyKeysPerMove
};

class GameViewModel : public QObject
{
    Q_OBJECT

public:
    explicit GameViewModel(Game* model, QObject *parent = nullptr);

    static constexpr int getTileSize() {return m_tile_size;}

    QRect getBoardDimensions() const;
    QPoint getSnakeHeadPosition() const;
    QList<QPoint> getSnakeBodyPositions() const;
    QPoint getFoodPosition() const;

    UserMessages getCurrentUserMessage() const;

    bool processKeyboardAction(int key_code);

public slots:
    void executeMove();

private slots:
    void startGame();

signals:
    void gameStarted();
    void gameUpdated();
    void userMessageUpdated(UserMessages message);

private:
    void updateUserMessage(UserMessages new_message);

    Game* m_game_model;
    UserMessages m_current_message;

    static constexpr int m_tile_size = 20;
};

#endif // GAMEVIEWMODEL_H
