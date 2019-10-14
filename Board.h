#ifndef BOARD_H
#define BOARD_H

#include <QDialog>
#include <ListToDo.h>
#include <task.h>


namespace Ui {
    class ListToDo;
    class Board;
    class Task;
    class Important;
}

class Board : public QDialog
{
Q_OBJECT

public:
    explicit Board(QVector<Task*> pTask, QString title,  QWidget *parent = 0);
    QString controlladata(QString data1,QString data2);
    void delAllTask();
    ~Board();

signals:
    void TaskSaved(QVector<Task*> pTask);

private slots:
    void on_Board_accepted();
    void on_addTaskButton_clicked();
    int on_searchTaskButton_clicked();
    void updateStatus();
    void removeTask(Task*task);
    void taskstatusChanged(Task *task);
    void closeEvent (QCloseEvent *event);




private:
    void copypTask(QVector<Task*> pTask);  //copia pTask in lTask
    Ui::Board *bui;
    QVector<Task*> lTask;
};

#endif // BOARD_H
