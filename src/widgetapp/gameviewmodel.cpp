#include "gameviewmodel.h"


GameViewModel::GameViewModel(std::unique_ptr<Game> model, QObject *parent) :
    QObject{parent},
    m_game_model(std::move(model))
{}

QRect GameViewModel::getBoardDimensions()
{
    QRect internal = m_game_model->getBoardDimensions();
    return QRect(internal.left() * m_tile_size,
                 internal.top() * m_tile_size,
                 internal.width() * m_tile_size,
                 internal.height() * m_tile_size);
}
