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

    void processKeyboardInput_shouldReturnFalse_whenCalledWithNonArrowKey();
    void processKeyboardInput_shouldReturnFalse_whenCalledWithNonArrowKey_data();
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

void test_GameViewModel::processKeyboardInput_shouldReturnFalse_whenCalledWithNonArrowKey_data() {
    QTest::addColumn<Qt::Key>("key_code");
    QTest::addColumn<bool>("expected_result");

    QTest::newRow("'Space' Key") << Qt::Key_Space << false;
    QTest::newRow("'Return' Key") << Qt::Key_Return << false;
    QTest::newRow("'Esc' Key") << Qt::Key_Escape << false;
    QTest::newRow("'w' Key") << Qt::Key_W << false;
    QTest::newRow("'1' Key") << Qt::Key_1 << false;
}

void test_GameViewModel::processKeyboardInput_shouldReturnFalse_whenCalledWithNonArrowKey() {
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

QTEST_APPLESS_MAIN(test_GameViewModel)

#include "test_gameviewmodel.moc"
