#ifndef SNAKECORE_H
#define SNAKECORE_H

enum class Direction {
    NoMove,
    MoveLeft,
    MoveRight,
    MoveUp,
    MoveDown
};

enum class DirectionChangeResult {
    Succeeded,
    OppositeDirection,
    TooManyPerMove
};

#endif // SNAKECORE_H
