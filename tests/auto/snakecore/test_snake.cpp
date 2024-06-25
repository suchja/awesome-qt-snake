#include <QTest>

// add necessary includes here
#include "snake.h"

class test_Snake : public QObject
{
    Q_OBJECT

public:
    test_Snake();
    ~test_Snake();

private slots:
    void getHead_shouldReturnCenterOfBoard_whenCalledAfterConstructor();
    void getBody_shouldReturnSpecifiedAmountOfElements_whenCalledAfterConstructor();
    void getBody_shouldReturnElementsConnectedLeftToHead_whenCalledAfterConstructor();

    void shouldStayOnDirection_whenCalledWithOppositeDirectionAndExecutingMove_data();
    void shouldStayOnDirection_whenCalledWithOppositeDirectionAndExecutingMove();
    void shouldStayOnDirection_whenCalledWithSameDirectionAndExecutingMove();

    void getHead_shouldReturnPositionOnOtherSide_whenExecuteMoveOnBorder_data();
    void getHead_shouldReturnPositionOnOtherSide_whenExecuteMoveOnBorder();
    void getBody_shouldReturnPositionOnOtherSide_whenExecuteMoveOnBorder_data();
    void getBody_shouldReturnPositionOnOtherSide_whenExecuteMoveOnBorder();

    void setMoveDirection_shouldReturnWhetherNewDirectionWasAccepted_data();
    void setMoveDirection_shouldReturnWhetherNewDirectionWasAccepted();
};

test_Snake::test_Snake() {}

test_Snake::~test_Snake() {}

void test_Snake::getHead_shouldReturnCenterOfBoard_whenCalledAfterConstructor() {
    // ARRANGE
    Snake sut(20, 20);
    QPoint expected(10, 10);

    // ACT
    QPoint actual = sut.getHead();

    // ASSERT
    QCOMPARE(actual, expected);
}

void test_Snake::getBody_shouldReturnSpecifiedAmountOfElements_whenCalledAfterConstructor() {
    // ARRANGE
    Snake sut(20, 20, 2);

    // ACT
    QList<QPoint> actual = sut.getBody();

    // ASSERT
    QCOMPARE(actual.count(), 2);
}

void test_Snake::getBody_shouldReturnElementsConnectedLeftToHead_whenCalledAfterConstructor() {
    // ARRANGE
    Snake sut(20, 20, 2);
    QList<QPoint> expected_elements;
    expected_elements << QPoint(8, 10) << QPoint(9, 10);

    // ACT
    QList<QPoint> actual = sut.getBody();

    // ASSERT
    QCOMPARE(actual, expected_elements);
}

void test_Snake::getHead_shouldReturnPositionOnOtherSide_whenExecuteMoveOnBorder_data() {
    QTest::addColumn<Direction>("move_direction");
    QTest::addColumn<int>("move_count");
    QTest::addColumn<QPoint>("expected_position");

    QTest::newRow("right border") << Direction::MoveRight << 10 << QPoint(0, 10);
    QTest::newRow("left border") << Direction::MoveLeft << 11 << QPoint(19, 10);
    QTest::newRow("bottom border") << Direction::MoveDown << 10 << QPoint(10, 0);
    QTest::newRow("upper border") << Direction::MoveUp << 11 << QPoint(10, 19);
}

void test_Snake::getHead_shouldReturnPositionOnOtherSide_whenExecuteMoveOnBorder() {
    // ARRANGE
    QFETCH(Direction, move_direction);
    QFETCH(int, move_count);
    QFETCH(QPoint, expected_position);

    Snake sut(20, 20);

    sut.setMoveDirection(move_direction);

    // ACT
    for (int i = 0; i < move_count; ++i)
        sut.executeMove();

    QPoint actual = sut.getHead();

    // ASSERT
    QCOMPARE(actual, expected_position);
}

void test_Snake::shouldStayOnDirection_whenCalledWithOppositeDirectionAndExecutingMove_data() {
    QTest::addColumn<Direction>("initial_direction");
    QTest::addColumn<Direction>("opposing_direction");
    QTest::addColumn<QPoint>("expected_position");

    QTest::newRow("down -> up") << Direction::MoveDown << Direction::MoveUp << QPoint(10, 12);
    QTest::newRow("up -> down") << Direction::MoveUp << Direction::MoveDown << QPoint(10, 8);
    QTest::newRow("left -> right") << Direction::MoveLeft << Direction::MoveRight << QPoint(8, 10);
    QTest::newRow("right -> left") << Direction::MoveRight << Direction::MoveLeft << QPoint(12, 10);
}

void test_Snake::shouldStayOnDirection_whenCalledWithOppositeDirectionAndExecutingMove() {
    // ARRANGE
    QFETCH(Direction, initial_direction);
    QFETCH(Direction, opposing_direction);
    QFETCH(QPoint, expected_position);

    Snake sut(20, 20);

    //   start game and move down to prepare for the test
    sut.setMoveDirection(initial_direction);
    sut.executeMove();

    // ACT
    sut.setMoveDirection(opposing_direction);
    sut.executeMove();
    QPoint actual = sut.getHead();

    // ASSERT
    QCOMPARE(actual, expected_position);
}

void test_Snake::shouldStayOnDirection_whenCalledWithSameDirectionAndExecutingMove() {
    // ARRANGE
    Snake sut(20, 20);
    QPoint expected(10, 8);

    //   start game and move up to prepare for the test
    sut.setMoveDirection(Direction::MoveUp);
    sut.executeMove();

    // ACT
    sut.setMoveDirection(Direction::MoveUp);
    sut.executeMove();
    QPoint actual = sut.getHead();

    // ASSERT
    QCOMPARE(actual, expected);
}

void test_Snake::getBody_shouldReturnPositionOnOtherSide_whenExecuteMoveOnBorder_data() {
    QTest::addColumn<Direction>("move_direction");
    QTest::addColumn<int>("move_count");
    QTest::addColumn<QList<QPoint>>("expected_positions");

    QTest::newRow("right border") << Direction::MoveRight << 11 << (QList<QPoint>() << QPoint(0, 10));
    QTest::newRow("left border") << Direction::MoveLeft << 12 << (QList<QPoint>() << QPoint(19, 10));
    QTest::newRow("bottom border") << Direction::MoveDown << 11 << (QList<QPoint>() << QPoint(10, 0));
    QTest::newRow("upper border") << Direction::MoveUp << 12 << (QList<QPoint>() << QPoint(10, 19));
}

void test_Snake::getBody_shouldReturnPositionOnOtherSide_whenExecuteMoveOnBorder() {
    // ARRANGE
    QFETCH(Direction, move_direction);
    QFETCH(int, move_count);
    QFETCH(QList<QPoint>, expected_positions);

    Snake sut(20, 20);

    sut.setMoveDirection(move_direction);

    // ACT
    for (int i = 0; i < move_count; ++i)
        sut.executeMove();

    QList<QPoint> actual = sut.getBody();

    // ASSERT
    QCOMPARE(actual, expected_positions);
}

void test_Snake::setMoveDirection_shouldReturnWhetherNewDirectionWasAccepted_data() {
    QTest::addColumn<Direction>("initial_direction");
    QTest::addColumn<Direction>("new_direction");
    QTest::addColumn<DirectionChangeResult>("expected");

    QTest::newRow("down -> up") << Direction::MoveDown << Direction::MoveUp << DirectionChangeResult::OppositeDirection;
    QTest::newRow("up -> down") << Direction::MoveUp << Direction::MoveDown << DirectionChangeResult::OppositeDirection;
    QTest::newRow("left -> right") << Direction::MoveLeft << Direction::MoveRight << DirectionChangeResult::OppositeDirection;
    QTest::newRow("right -> left") << Direction::MoveRight << Direction::MoveLeft << DirectionChangeResult::OppositeDirection;
    QTest::newRow("up -> left") << Direction::MoveUp << Direction::MoveLeft << DirectionChangeResult::Succeeded;
    QTest::newRow("down -> left") << Direction::MoveDown << Direction::MoveLeft << DirectionChangeResult::Succeeded;
    QTest::newRow("down -> right") << Direction::MoveDown << Direction::MoveRight << DirectionChangeResult::Succeeded;
}

void test_Snake::setMoveDirection_shouldReturnWhetherNewDirectionWasAccepted() {
    // ARRANGE
    QFETCH(Direction, initial_direction);
    QFETCH(Direction, new_direction);
    QFETCH(DirectionChangeResult, expected);

    Snake sut(20, 20);

    // ACT
    sut.setMoveDirection(initial_direction);
    DirectionChangeResult actual = sut.setMoveDirection(new_direction);

    // ASSERT
    QCOMPARE(actual, expected);
}

QTEST_APPLESS_MAIN(test_Snake)

#include "test_snake.moc"
