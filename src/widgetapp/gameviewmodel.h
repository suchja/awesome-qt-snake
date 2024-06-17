#ifndef GAMEVIEWMODEL_H
#define GAMEVIEWMODEL_H

#include <QObject>
#include <QRect>

#include "game.h"

class GameViewModel : public QObject
{
    Q_OBJECT
public:
    explicit GameViewModel(Game* model, QObject *parent = nullptr);

    QRect getBoardDimensions() const;
    static constexpr int getTileSize() {return m_tile_size;};

signals:

private:
    static constexpr int m_tile_size = 20;

    Game* m_game_model;
};

#endif // GAMEVIEWMODEL_H
