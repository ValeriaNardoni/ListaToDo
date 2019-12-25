//
// Created by Valeria on 13/08/19.
//

#include "mainWindow.h"
#include <QApplication>
#include <QtTest/QtTest>
#include <QCoreApplication>


class Test : public QObject {
Q_OBJECT
private slots:

    void TestNameList();

    void TestTestCompleted();

    void TestTestCompleted1();

    void TestContaImp();

    void TestContaImp1();

    void TestContaImp2();

    void TestSearchList();

    void TestSearchList1();

    void TestSearchList2();

};

void Test::TestNameList() {
    ListToDo *listToDo = new ListToDo("TestNameList");
    QCOMPARE(listToDo->name(), QString("TestNameList"));


}

void Test::TestTestCompleted() {

    Task *task = new Task("nameTask");
    QCOMPARE(task->isCompleted(), 0);


}

void Test::TestTestCompleted1() {

    Task *task = new Task("nameTask");
    task->setCompleted();
    QCOMPARE(task->isCompleted(), 1);

}


void Test::TestContaImp() {
    MainWindow w;
    w.addListToDoTest("TestNameList");
    QCOMPARE(w.ContaImp(), 0);

}

void Test::TestContaImp1() {
    MainWindow w;
    w.addListToDoTest("TestNameList");
    w.caricaTest("TESTNONTOCCARE");
    QCOMPARE(w.ContaImp(), 1);

}

void Test::TestContaImp2() {
    MainWindow w;
    w.addListToDoTest("TestNameList");
    w.caricaTest("TESTNONTOCCARE");
    w.caricaTest("TESTNONTOCCARE2");
    QCOMPARE(w.ContaImp(), 6);
}


void Test::TestSearchList() {
    MainWindow w;
    w.caricaTest("TESTNONTOCCARE");
    w.caricaTest("TESTNONTOCCARE2");
    QCOMPARE(w.searchList("pippo"), 0);

}

void Test::TestSearchList1() {
    MainWindow w;
    w.caricaTest("TESTNONTOCCARE");
    QCOMPARE(w.searchList("test"), 1);
}


void Test::TestSearchList2() {
    MainWindow w;
    w.caricaTest("TESTNONTOCCARE");
    w.caricaTest("TESTNONTOCCARE2");
    QCOMPARE(w.searchList("test"), 3);
}

QTEST_MAIN(Test)

#include "Test.moc"

