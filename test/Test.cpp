//
// Created by Valeria on 13/08/19.
//

#include "mainWindow.h"
#include <QApplication>
#include <QtTest/QtTest>
#include <QCoreApplication>


/*
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
*/

class Test: public QObject
{
Q_OBJECT
private slots:
    void TestNameList();
    void TestTestCompleted();
};

void Test::TestNameList()
{
    ListToDo *listToDo = new ListToDo("TestNameList");
    QCOMPARE( listToDo->name(), QString("TestNameList"));
    // qDebug() << "Test Funziona";

}

void Test::TestTestCompleted()
{
    // ListToDo *listToDo = new ListToDo("TestNameList");
    Task *task = new Task("nameTask");
    QCOMPARE( task->isCompleted(), 0);
    task->setCompleted();
    QCOMPARE( task->isCompleted(), 1);

}


QTEST_MAIN(Test)
#include "Test.moc"

