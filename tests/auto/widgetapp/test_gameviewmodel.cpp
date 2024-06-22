#include <QTest>
#include <QSignalSpy>

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
    void getCurrentUserMessage_shouldReturnNone_whenGameIsStarted();

    void processKeyboardInput_shouldReturnX_whenCalledWithYKey_data();
    void processKeyboardInput_shouldReturnX_whenCalledWithYKey();
    void processKeyboardInput_shouldResultInGameStartedSignal_whenInitiallyCalledWithDirection();
    void processKeyboardInput_shouldSignalUserMessageUpdated_whenGameStarted();
    void processKeyboardInput_shouldSignalUserMessageUpdated_whenUnsupportedKeyAfterGameStarted();
    void processKeyboardInput_shouldSignalUserMessageUpdated_whenSupportedKeyAfterUnsupportedAndGameStarted();
    void processKeyboardInput_shouldSignalUserMessageUpdated_whenOppositeDirectionIsPressed();
    void processKeyboardInput_shouldNotSignalUserMessageUpdated_whenUnsupportedKeyPressedBeforeGameStarted();
    void processKeyboardInput_shouldNotSignalUserMessageUpdated_whenMessageDoesNotChange();

    void getSnakePostions_shouldBeChangedToNewPosition_whenCalledAfterKeyEventAndExecuteMove_data();
    void getSnakePostions_shouldBeChangedToNewPosition_whenCalledAfterKeyEventAndExecuteMove();

    void executeMove_shouldSignalGameUpdated_whenItIsCalled();
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
    QPoint expected_head = QPoint(200, 200);
    QList<QPoint> expected_body;
    expected_body << QPoint(180, 200);

    GameViewModel sut(&game_dependency);

    // ACT
    QPoint actual_head = sut.getSnakeHeadPosition();
    QList<QPoint> actual_body = sut.getSnakeBodyPositions();

    // ASSERT
    QCOMPARE(actual_head, expected_head);
    QCOMPARE(actual_body, expected_body);
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

void test_GameViewModel::getCurrentUserMessage_shouldReturnNone_whenGameIsStarted() {
    // ARRANGE
    Game game_dependency = Game(20, 20);

    GameViewModel sut(&game_dependency);

    // ACT
    sut.processKeyboardAction(Qt::Key_Down); // game starts with arrow key press!
    UserMessages actual = sut.getCurrentUserMessage();

    // ASSERT
    QCOMPARE(actual, UserMessages::None);
}

void test_GameViewModel::processKeyboardInput_shouldResultInGameStartedSignal_whenInitiallyCalledWithDirection() {
    // ARRANGE
    Game game_dependency = Game(20, 20);

    GameViewModel sut(&game_dependency);

    QSignalSpy is_started_signal(&sut, SIGNAL(gameStarted()));

    // TODO: JS, why is this not working???
    //QSignalSpy is_started_signal(&sut, &GameViewModel::gameStarted);

    // ACT
    sut.processKeyboardAction(Qt::Key_Right);

    // ASSERT
    QCOMPARE(is_started_signal.count(), 1);
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

void test_GameViewModel::processKeyboardInput_shouldSignalUserMessageUpdated_whenGameStarted() {
    // ARRANGE
    Game game_dependency = Game(20, 20);

    GameViewModel sut(&game_dependency);
    QSignalSpy is_updated_signal(&sut, SIGNAL(userMessageUpdated(UserMessages)));

    // ACT
    // test doesn't care about return value!
    sut.processKeyboardAction(Qt::Key_Down);

    // ASSERT
    QCOMPARE(is_updated_signal.count(), 1);
    QList<QVariant> arguments = is_updated_signal.takeFirst();
    QCOMPARE((UserMessages)arguments.at(0).toInt(), UserMessages::None);
}

void test_GameViewModel::processKeyboardInput_shouldSignalUserMessageUpdated_whenSupportedKeyAfterUnsupportedAndGameStarted() {
    // ARRANGE
    Game game_dependency = Game(20, 20);

    GameViewModel sut(&game_dependency);
    sut.processKeyboardAction(Qt::Key_Up); // start game
    sut.processKeyboardAction(Qt::Key_Escape); // set to unsupported key
    QSignalSpy is_updated_signal(&sut, SIGNAL(userMessageUpdated(UserMessages)));

    // ACT
    // test doesn't care about return value!
    sut.processKeyboardAction(Qt::Key_Up);

    // ASSERT
    QCOMPARE(is_updated_signal.count(), 1);
    QList<QVariant> arguments = is_updated_signal.takeFirst();
    QCOMPARE((UserMessages)arguments.at(0).toInt(), UserMessages::None);
}
void test_GameViewModel::processKeyboardInput_shouldNotSignalUserMessageUpdated_whenUnsupportedKeyPressedBeforeGameStarted() {
    // ARRANGE
    Game game_dependency = Game(20, 20);

    GameViewModel sut(&game_dependency);
    QSignalSpy is_updated_signal(&sut, SIGNAL(userMessageUpdated(UserMessages)));

    // ACT
    // test doesn't care about return value!
    sut.processKeyboardAction(Qt::Key_Return);

    // ASSERT
    QCOMPARE(is_updated_signal.count(), 0);
}

void test_GameViewModel::processKeyboardInput_shouldNotSignalUserMessageUpdated_whenMessageDoesNotChange() {
    // ARRANGE
    Game game_dependency = Game(20, 20);

    GameViewModel sut(&game_dependency);
    sut.processKeyboardAction(Qt::Key_Up); // start game
    sut.processKeyboardAction(Qt::Key_Escape); // set to unsupported key
    QSignalSpy is_updated_signal(&sut, SIGNAL(userMessageUpdated(UserMessages)));

    // ACT
    // test doesn't care about return value!
    sut.processKeyboardAction(Qt::Key_Escape);

    // ASSERT
    QCOMPARE(is_updated_signal.count(), 0);
}

void test_GameViewModel::processKeyboardInput_shouldSignalUserMessageUpdated_whenUnsupportedKeyAfterGameStarted() {
    // ARRANGE
    Game game_dependency = Game(20, 20);

    GameViewModel sut(&game_dependency);
    sut.processKeyboardAction(Qt::Key_Left); // we need to start game first!
    QSignalSpy is_updated_signal(&sut, SIGNAL(userMessageUpdated(UserMessages)));

    // ACT
    //   test doesn't care about return value!
    sut.processKeyboardAction(Qt::Key_Return);

    // ASSERT
    QCOMPARE(is_updated_signal.count(), 1);
    QList<QVariant> arguments = is_updated_signal.takeFirst();
    QCOMPARE((UserMessages)arguments.at(0).toInt(), UserMessages::KeyNotSupported);
}

void test_GameViewModel::processKeyboardInput_shouldSignalUserMessageUpdated_whenOppositeDirectionIsPressed() {
    // ARRANGE
    Game game_dependency = Game(20, 20);

    GameViewModel sut(&game_dependency);
    sut.processKeyboardAction(Qt::Key_Left); // we need to start game first!

    QSignalSpy is_updated_signal(&sut, SIGNAL(userMessageUpdated(UserMessages)));

    // ACT
    //   test doesn't care about return value!
    sut.processKeyboardAction(Qt::Key_Right);

    // ASSERT
    QCOMPARE(is_updated_signal.count(), 1);
    QList<QVariant> arguments = is_updated_signal.takeFirst();
    QCOMPARE((UserMessages)arguments.at(0).toInt(), UserMessages::WrongDirection);
}

void test_GameViewModel::getSnakePostions_shouldBeChangedToNewPosition_whenCalledAfterKeyEventAndExecuteMove_data() {
    QTest::addColumn<Qt::Key>("key_code");
    QTest::addColumn<QPoint>("expected_head");
    QTest::addColumn<QList<QPoint>>("expected_body");

    QTest::newRow("Left") << Qt::Key_Left << QPoint(180, 200) << (QList<QPoint>() << QPoint(200, 200));
    QTest::newRow("Right") << Qt::Key_Right << QPoint(220, 200) << (QList<QPoint>() << QPoint(200, 200));
    QTest::newRow("Up") << Qt::Key_Up << QPoint(200, 180) << (QList<QPoint>() << QPoint(200, 200));
    QTest::newRow("Down") << Qt::Key_Down << QPoint(200, 220) << (QList<QPoint>() << QPoint(200, 200));
}

void test_GameViewModel::getSnakePostions_shouldBeChangedToNewPosition_whenCalledAfterKeyEventAndExecuteMove() {
    // ARRANGE
    QFETCH(Qt::Key, key_code);
    QFETCH(QPoint, expected_head);
    QFETCH(QList<QPoint>, expected_body);

    Game game_dependency = Game(20, 20);

    GameViewModel sut(&game_dependency);

    // ACT
    sut.processKeyboardAction(key_code);
    sut.executeMove();
    QPoint actual_head = sut.getSnakeHeadPosition();
    QList<QPoint> actual_body = sut.getSnakeBodyPositions();

    // ASSERT
    QCOMPARE(actual_head, expected_head);
    QCOMPARE(actual_body, expected_body);
}

void test_GameViewModel::executeMove_shouldSignalGameUpdated_whenItIsCalled()
{
    // ARRANGE
    Game game_dependency = Game(20, 20);

    GameViewModel sut(&game_dependency);

    QSignalSpy is_updated_signal(&sut, SIGNAL(gameUpdated()));

    // ACT
    sut.executeMove();

    // ASSERT
    QCOMPARE(is_updated_signal.count(), 1);

}

QTEST_APPLESS_MAIN(test_GameViewModel)

#include "test_gameviewmodel.moc"
