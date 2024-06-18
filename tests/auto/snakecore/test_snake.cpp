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

QTEST_APPLESS_MAIN(test_Snake)

#include "test_snake.moc"
