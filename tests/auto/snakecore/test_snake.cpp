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
    void getBody_shouldReturnOneElement_whenCalledAfterConstructor();
    void getBody_shouldReturnElementConnectedLeftToHead_whenCalledAfterConstructor();

    void getHead_shouldReturnNewPosition_whenCalledAfter_setToHeadPosition();
    void getBody_shouldReturnNewPosition_whenCalledAfter_setToHeadPosition_data();
    void getBody_shouldReturnNewPosition_whenCalledAfter_setToHeadPosition();

    void getHead_shouldReturnPositionOnOtherSide_whenExecuteMoveOnBorder_data();
    void getHead_shouldReturnPositionOnOtherSide_whenExecuteMoveOnBorder();
    void getBody_shouldReturnPositionOnOtherSide_whenExecuteMoveOnBorder_data();
    void getBody_shouldReturnPositionOnOtherSide_whenExecuteMoveOnBorder();
};

test_Snake::test_Snake() {}

test_Snake::~test_Snake() {}

void test_Snake::getHead_shouldReturnCenterOfBoard_whenCalledAfterConstructor() {
    // ARRANGE
    Snake sut(20, 20, this);
    QPoint expected(10, 10);

    // ACT
    QPoint actual = sut.getHead();

    // ASSERT
    QCOMPARE(actual, expected);
}

void test_Snake::getBody_shouldReturnOneElement_whenCalledAfterConstructor() {
    // ARRANGE
    Snake sut(20, 20, this);

    // ACT
    QList<QPoint> actual = sut.getBody();

    // ASSERT
    QCOMPARE(actual.count(), 1);
}

void test_Snake::getBody_shouldReturnElementConnectedLeftToHead_whenCalledAfterConstructor() {
    // ARRANGE
    Snake sut(20, 20, this);
    QPoint expected(9, 10);

    // ACT
    QPoint actual = sut.getBody().at(0);

    // ASSERT
    QCOMPARE(actual, expected);
}

void test_Snake::getHead_shouldReturnNewPosition_whenCalledAfter_setToHeadPosition() {
    // ARRANGE
    Snake sut(20, 20, this);
    QPoint new_position(5, 5);

    // ACT
    sut.setToHeadPosition(new_position);
    QPoint actual = sut.getHead();

    // ASSERT
    QCOMPARE(actual, new_position);
}

void test_Snake::getBody_shouldReturnNewPosition_whenCalledAfter_setToHeadPosition_data() {
    QTest::addColumn<QPoint>("new_head_position");
    QTest::addColumn<QList<QPoint>>("expected_positions");

    QTest::newRow("move up and left") << QPoint(5, 5) << (QList<QPoint>() << QPoint(4, 5));
    QTest::newRow("move up") << QPoint(10, 1) << (QList<QPoint>() << QPoint(9, 1));
    QTest::newRow("move up and right") << QPoint(19, 2) << (QList<QPoint>() << QPoint(18, 2));
    QTest::newRow("move right") << QPoint(18, 10) << (QList<QPoint>() << QPoint(17, 10));
    QTest::newRow("move down and right") << QPoint(17, 11) << (QList<QPoint>() << QPoint(16, 11));
    QTest::newRow("move down") << QPoint(10, 13) << (QList<QPoint>() << QPoint(9, 13));
    QTest::newRow("move down and left") << QPoint(8, 15) << (QList<QPoint>() << QPoint(7, 15));
    QTest::newRow("move left") << QPoint(1, 10) << (QList<QPoint>() << QPoint(0, 10));
}

void test_Snake::getBody_shouldReturnNewPosition_whenCalledAfter_setToHeadPosition() {
    // ARRANGE
    QFETCH(QPoint, new_head_position);
    QFETCH(QList<QPoint>, expected_positions);

    Snake sut(20, 20, this);

    // ACT
    sut.setToHeadPosition(new_head_position);
    QList<QPoint> actual = sut.getBody();

    // ASSERT
    QCOMPARE(actual, expected_positions);
}

void test_Snake::getHead_shouldReturnPositionOnOtherSide_whenExecuteMoveOnBorder_data() {
    QTest::addColumn<QPoint>("start_head_position");
    QTest::addColumn<Direction>("move_direction");
    QTest::addColumn<int>("move_count");
    QTest::addColumn<QPoint>("expected_position");

    QTest::newRow("right border") << QPoint(18, 10) << Direction::MoveRight << 2 << QPoint(0, 10);
    QTest::newRow("left border") << QPoint(1, 10) << Direction::MoveLeft << 2 << QPoint(19, 10);
    QTest::newRow("bottom border") << QPoint(19, 18) << Direction::MoveDown << 2 << QPoint(19, 0);
    QTest::newRow("upper border") << QPoint(2, 1) << Direction::MoveUp << 2 << QPoint(2, 19);
}

void test_Snake::getHead_shouldReturnPositionOnOtherSide_whenExecuteMoveOnBorder() {
    // ARRANGE
    QFETCH(QPoint, start_head_position);
    QFETCH(Direction, move_direction);
    QFETCH(int, move_count);
    QFETCH(QPoint, expected_position);

    Snake sut(20, 20, this);

    sut.setToHeadPosition(start_head_position);
    sut.setMoveDirection(move_direction);

    // ACT
    for (int i = 0; i < move_count; ++i)
        sut.executeMove();

    QPoint actual = sut.getHead();

    // ASSERT
    QCOMPARE(actual, expected_position);
}

void test_Snake::getBody_shouldReturnPositionOnOtherSide_whenExecuteMoveOnBorder_data() {
    QTest::addColumn<QPoint>("start_head_position");
    QTest::addColumn<Direction>("move_direction");
    QTest::addColumn<QList<QPoint>>("expected_positions");

    QTest::newRow("right border") << QPoint(19, 10) << Direction::MoveRight << (QList<QPoint>() << QPoint(0, 10));
    QTest::newRow("left border") << QPoint(0, 10) << Direction::MoveLeft << (QList<QPoint>() << QPoint(19, 10));
    QTest::newRow("bottom border") << QPoint(19, 19) << Direction::MoveDown << (QList<QPoint>() << QPoint(19, 0));
    QTest::newRow("upper border") << QPoint(2, 0) << Direction::MoveUp << (QList<QPoint>() << QPoint(2, 19));
}

void test_Snake::getBody_shouldReturnPositionOnOtherSide_whenExecuteMoveOnBorder() {
    // ARRANGE
    QFETCH(QPoint, start_head_position);
    QFETCH(Direction, move_direction);
    QFETCH(QList<QPoint>, expected_positions);

    Snake sut(20, 20, this);

    sut.setToHeadPosition(start_head_position);
    sut.setMoveDirection(move_direction);

    // ACT
    sut.executeMove();
    sut.executeMove(); // body "flips" to other side after head!
    QList<QPoint> actual = sut.getBody();

    // ASSERT
    QCOMPARE(actual, expected_positions);
}

QTEST_APPLESS_MAIN(test_Snake)

#include "test_snake.moc"
