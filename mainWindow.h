#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QVector>
#include <QMainWindow>
#include "ListToDo.h"
#include "Important.h"


namespace Ui {
    class MainWindow;
    class Important;
}


class MainWindow : public QMainWindow
{
Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void updateStatus();
    void delAllList();
    void caricaTest(QString nometest);
    QString inputSearch();
    int searchList(QString text);

public slots:
    void addListToDo();
    void addListToDoTest(QString name);
    void removeListToDo(ListToDo *listToDo);
    void listToDoStatusChanged(ListToDo *listToDo);
    int ContaImp();
private slots:

    void on_Save_clicked();
    void on_OpenFile_clicked();
    int on_searchButton_clicked();
    void on_importantButton_clicked();

private:
    Ui::MainWindow *ui;

    QVector<ListToDo*> mListToDos;
   // QVector<ListToDo*> mListOrd;
};

#endif // MAINWINDOW_H
