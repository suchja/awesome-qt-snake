#include <QTest>
#include <QSignalSpy>

#define QVERIFY_LIST_NOT_INCLUDES_POINT(list, point) \
do { \
    for (int i = 0; i < (list).size(); ++i) { \
        if ((list)[i] == point) { \
            QString msg = QString("Point (%1, %2) included in list at position %3 (%4, %5)") \
                  .arg(point.x()).arg(point.y()) \
                  .arg(i) \
                  .arg((list)[i].x()).arg((list)[i].y()); \
            QTest::qFail(qPrintable(msg), __FILE__, __LINE__); \
        } \
    } \
} while (0)

// add necessary includes here
#include "snakecore.h"
#include "game.h"

class test_Game : public QObject
{
    Q_OBJECT

public:
    test_Game();
    ~test_Game();

private slots:
    void getBoardDimensions_shouldReturnInitialGridCoordinates_whenCalledAfterConstructor();

    void getSnakeHeadPosition_shouldReturnCenterOfBoard_whenCalledAfterConstructor();
    void getSnakeBodyPositions_shouldReturnOneElement_whenCalledAfterConstructor();

    void getFoodPosition_shouldReturnPositionNotColidingWithSnake_whenCalled();

    void isStarted_shouldBeEmitted_whenMoveDirectionIsSetFromNoMoveToSomethingElse_data();
    void isStarted_shouldBeEmitted_whenMoveDirectionIsSetFromNoMoveToSomethingElse();
    void isStarted_shouldReturnFalse_whenGameWasNotStarted();
    void isStarted_shouldReturnTrue_whenGameWasStarted();

    void getSnakeHeadPosition_shouldMoveOneTiletoNewDirection_whenCalledAfterSettingDirectionAndExecutingMove_data();
    void getSnakeHeadPosition_shouldMoveOneTiletoNewDirection_whenCalledAfterSettingDirectionAndExecutingMove();
};

test_Game::test_Game() {}

test_Game::~test_Game() {}

void test_Game::getBoardDimensions_shouldReturnInitialGridCoordinates_whenCalledAfterConstructor() {
    // ARRANGE
    Game sut(20, 20);
    QRect expected(0, 0, 20, 20);

    // ACT
    QRect actual = sut.getBoardDimensions();

    // ASSERT
    QCOMPARE(actual, expected);
}

void test_Game::getSnakeHeadPosition_shouldReturnCenterOfBoard_whenCalledAfterConstructor() {
    // ARRANGE
    Game sut(20, 20);
    QPoint expected(10, 10);

    // ACT
    QPoint actual = sut.getSnakeHeadPosition();

    // ASSERT
    QCOMPARE(actual, expected);
}

void test_Game::getSnakeBodyPositions_shouldReturnOneElement_whenCalledAfterConstructor() {
    // ARRANGE
    Game sut(20, 20);

    // ACT
    QList<QPoint> actual = sut.getSnakeBodyPositions();

    // ASSERT
    QCOMPARE(actual.count(), 1);
}

void test_Game::getFoodPosition_shouldReturnPositionNotColidingWithSnake_whenCalled() {
    // ARRANGE
    Game sut(20, 20);

    // ACT
    QPoint actual = sut.getFoodPosition();

    // ASSERT
    QList<QPoint> snake = sut.getSnakeBodyPositions();
    snake << sut.getSnakeHeadPosition();

    QVERIFY_LIST_NOT_INCLUDES_POINT(snake, actual);
}

void test_Game::isStarted_shouldBeEmitted_whenMoveDirectionIsSetFromNoMoveToSomethingElse_data()
{
    QTest::addColumn<Direction>("move_direction");
    QTest::addColumn<int>("expected_signal_count");

    QTest::newRow("NoMove") << Direction::NoMove << 0;
    QTest::newRow("Right") << Direction::MoveRight << 1;
    QTest::newRow("Left") << Direction::MoveLeft << 1;
    QTest::newRow("Up") << Direction::MoveUp << 1;
    QTest::newRow("Down") << Direction::MoveDown << 1;
}

void test_Game::isStarted_shouldBeEmitted_whenMoveDirectionIsSetFromNoMoveToSomethingElse()
{
    // ARRANGE
    QFETCH(Direction, move_direction);
    QFETCH(int, expected_signal_count);

    Game sut(20, 20);

    QSignalSpy is_started_signal(&sut, &Game::isStarted);

    // ACT
    sut.setMoveDirection(move_direction);

    // ASSERT
    QCOMPARE(is_started_signal.count(), expected_signal_count);
}

void test_Game::isStarted_shouldReturnFalse_whenGameWasNotStarted() {
    // ARRANGE
    Game sut(20, 20);

    // ACT
    bool actual = sut.isGameStarted();

    // ASSERT
    QCOMPARE(actual, false);
}

void test_Game::isStarted_shouldReturnTrue_whenGameWasStarted() {
    // ARRANGE
    Game sut(20, 20);

    sut.setMoveDirection(Direction::MoveLeft); // required to start game!

    // ACT
    bool actual = sut.isGameStarted();

    // ASSERT
    QCOMPARE(actual, true);
}

void test_Game::getSnakeHeadPosition_shouldMoveOneTiletoNewDirection_whenCalledAfterSettingDirectionAndExecutingMove_data()
{
    QTest::addColumn<Direction>("move_direction");
    QTest::addColumn<QPoint>("expected_position");

    QTest::newRow("Right") << Direction::MoveRight << QPoint(11, 10);
    QTest::newRow("Left") << Direction::MoveLeft << QPoint(9, 10);
    QTest::newRow("Down") << Direction::MoveDown << QPoint(10, 11);
    QTest::newRow("Up") << Direction::MoveUp << QPoint(10, 9);
}

void test_Game::getSnakeHeadPosition_shouldMoveOneTiletoNewDirection_whenCalledAfterSettingDirectionAndExecutingMove() {
    // ARRANGE
    QFETCH(Direction, move_direction);
    QFETCH(QPoint, expected_position);

    Game sut(20, 20);

    // ACT
    sut.setMoveDirection(move_direction);
    sut.executeMove();
    QPoint actual = sut.getSnakeHeadPosition();

    // ASSERT
    QCOMPARE(actual, expected_position);
}

QTEST_APPLESS_MAIN(test_Game)

#include "test_game.moc"
