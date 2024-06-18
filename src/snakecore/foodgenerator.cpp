#include "foodgenerator.h"

#include <QPoint>

FoodGenerator::FoodGenerator(int board_row_count, int board_column_count, QObject *parent) :
    QObject{parent},
    m_board_row_count(board_row_count),
    m_board_column_count(board_column_count)
{
    // TODO: js, it would be better to get this injected!
    m_random = QRandomGenerator::global();
}

QPoint FoodGenerator::getFoodOnRandomPosition() const
{
    int x = m_random->bounded(m_board_row_count);
    int y = m_random->bounded(m_board_column_count);

    return QPoint(x, y);
}
