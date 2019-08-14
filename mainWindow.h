#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QVector>
#include <QMainWindow>
#include "ListToDo.h"

namespace Ui {
    class MainWindow;
}

/* Inherits from QMainWindow. Q_OBJECT macro must be first thing
 * declared to setup some Qt magic stuff. We also declare a
 * pointer to a MainWindow class, member variable 'ui', this
 * will allow us to interact with our UI components (buttons, text
 * entries, etc.) from C++, as Qt will set it up for us.
 *
 * We set up our slots here too, to hook signals to.
 */
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


private:
    Ui::MainWindow *ui;
    /* QVector is Qt container class for dynamic arrays, like std::vector
     * but more Qt specific features
     */
    QVector<ListToDo*> mListToDos;
};

#endif // MAINWINDOW_H
