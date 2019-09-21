#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QVector>
#include <QMainWindow>
#include "ListToDo.h"

namespace Ui {
    class MainWindow;
}


class MainWindow : public QMainWindow
{
Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void updateStatus();

public slots:
    void addListToDo();
    void removeListToDo(ListToDo *listToDo);
    void listToDoStatusChanged(ListToDo *listToDo);
private slots:
    void on_Save_clicked();
    void on_OpenFile_clicked();
    void on_searchButton_clicked();


private:
    Ui::MainWindow *ui;

    QVector<ListToDo*> mListToDos;
};

#endif // MAINWINDOW_H
