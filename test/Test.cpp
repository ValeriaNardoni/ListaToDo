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
    void TestSave();
};

void Test::TestSave()
{

}

QTEST_MAIN(Test)
#include "Test.moc"

