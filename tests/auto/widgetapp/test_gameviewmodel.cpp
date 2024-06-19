#include <QTest>

// add necessary includes here
#include "game.h"
#include "gameviewmodel.h"

class test_GameViewModel : public QObject
{
    Q_OBJECT

public:
    test_GameViewModel();
    ~test_GameViewModel();

private slots:
    void getBoardDimensions_shouldReturnSceneCoordinates_whenCalledAfterConstructor();
    void getSnakePositions_shouldReturnTwoSceneCoordinatesInTheCenter_whenCalledAfterConstructor();

    void getCurrentUserMessage_shouldReturnStartGame_whenCalledAfterConstructor();

    void processKeyboardInput_shouldReturnX_whenCalledWithYKey_data();
    void processKeyboardInput_shouldReturnX_whenCalledWithYKey();

    void getSnakePostions_shouldBeChangedToNewPosition_whenCalledAfterKeyEventAndExecuteMove_data();
    void getSnakePostions_shouldBeChangedToNewPosition_whenCalledAfterKeyEventAndExecuteMove();
};

test_GameViewModel::test_GameViewModel() {}

test_GameViewModel::~test_GameViewModel() {}

void test_GameViewModel::getBoardDimensions_shouldReturnSceneCoordinates_whenCalledAfterConstructor() {
    // ARRANGE
    Game game_dependency = Game(20, 20);
    QRect expected(0, 0, 400, 400);

    GameViewModel sut(&game_dependency);

    // ACT
    QRect actual = sut.getBoardDimensions();

    // ASSERT
    QCOMPARE(actual, expected);
}

void test_GameViewModel::getSnakePositions_shouldReturnTwoSceneCoordinatesInTheCenter_whenCalledAfterConstructor() {
    // ARRANGE
    int tile_size = GameViewModel::getTileSize();

    Game game_dependency = Game(20, 20);
    QList<QPoint> expected;
    expected << QPoint(200, 200) << QPoint(180, 200);

    GameViewModel sut(&game_dependency);

    // ACT
    QList<QPoint> actual = sut.getSnakePositions();

    // ASSERT
    QCOMPARE(actual, expected);
}

void test_GameViewModel::getCurrentUserMessage_shouldReturnStartGame_whenCalledAfterConstructor() {
    // ARRANGE
    Game game_dependency = Game(20, 20);

    GameViewModel sut(&game_dependency);

    // ACT
    UserMessages actual = sut.getCurrentUserMessage();

    // ASSERT
    QCOMPARE(actual, UserMessages::StartGame);
}

void test_GameViewModel::processKeyboardInput_shouldReturnX_whenCalledWithYKey_data() {
    QTest::addColumn<Qt::Key>("key_code");
    QTest::addColumn<bool>("expected_result");

    QTest::newRow("'Space' Key") << Qt::Key_Space << false;
    QTest::newRow("'Return' Key") << Qt::Key_Return << false;
    QTest::newRow("'Esc' Key") << Qt::Key_Escape << false;
    QTest::newRow("'w' Key") << Qt::Key_W << false;
    QTest::newRow("'1' Key") << Qt::Key_1 << false;
    QTest::newRow("'Left' Key") << Qt::Key_Left << true;
    QTest::newRow("'Right' Key") << Qt::Key_Right << true;
    QTest::newRow("'Up' Key") << Qt::Key_Up << true;
    QTest::newRow("'Down' Key") << Qt::Key_Down << true;
}

void test_GameViewModel::processKeyboardInput_shouldReturnX_whenCalledWithYKey() {
    // ARRANGE
    QFETCH(Qt::Key, key_code);
    QFETCH(bool, expected_result);

    Game game_dependency = Game(20, 20);

    // A valid key event might look like this:
    // QKeyEvent space_key_event(QEvent::KeyPress, Qt::Key_Space, Qt::NoModifier);

    GameViewModel sut(&game_dependency);

    // ACT
    bool actual = sut.processKeyboardAction(key_code);

    // ASSERT
    QCOMPARE(actual, expected_result);
}

void test_GameViewModel::getSnakePostions_shouldBeChangedToNewPosition_whenCalledAfterKeyEventAndExecuteMove_data() {
    QTest::addColumn<Qt::Key>("key_code");
    QTest::addColumn<QList<QPoint>>("expected_positions");

    QTest::newRow("Left") << Qt::Key_Left << (QList<QPoint>() << QPoint(180, 200) << QPoint(200, 200));
    QTest::newRow("Right") << Qt::Key_Right << (QList<QPoint>() << QPoint(220, 200) << QPoint(200, 200));
    QTest::newRow("Up") << Qt::Key_Up << (QList<QPoint>() << QPoint(200, 180) << QPoint(200, 200));
    QTest::newRow("Down") << Qt::Key_Down << (QList<QPoint>() << QPoint(200, 220) << QPoint(200, 200));
}

void test_GameViewModel::getSnakePostions_shouldBeChangedToNewPosition_whenCalledAfterKeyEventAndExecuteMove() {
    // ARRANGE
    QFETCH(Qt::Key, key_code);
    QFETCH(QList<QPoint>, expected_positions);

    Game game_dependency = Game(20, 20);

    GameViewModel sut(&game_dependency);

    // ACT
    sut.processKeyboardAction(key_code);
    sut.executeMove();
    QList<QPoint> actual = sut.getSnakePositions();

    // ASSERT
    QCOMPARE(actual, expected_positions);

}
QTEST_APPLESS_MAIN(test_GameViewModel)

#include "test_gameviewmodel.moc"
