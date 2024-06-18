#ifndef FOODGENERATOR_H
#define FOODGENERATOR_H

#include <QObject>
#include <QRandomGenerator>

class FoodGenerator : public QObject
{
    Q_OBJECT
public:
    explicit FoodGenerator(int board_row_count, int board_column_count, QObject *parent = nullptr);

    QPoint getFoodOnRandomPosition() const;

signals:

private:
    QRandomGenerator* m_random;

    const int m_board_row_count;
    const int m_board_column_count;
};

#endif // FOODGENERATOR_H
