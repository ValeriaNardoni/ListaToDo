#ifndef ListToDo_H
#define ListToDo_H

#include <QWidget>
#include <Board.h>
#include <task.h>

namespace Ui {
    class ListToDo;
    class Board;
  //  class Task;
}

class ListToDo : public QWidget
{
Q_OBJECT

public:
    explicit ListToDo(const QString &name, QWidget *parent=0);
    ~ListToDo();

    void setName(const QString &name);
    QString name() const;
    QVector<Task*> retTask() const;
    bool isCompleted() const;
    void recmTask(); //copia pTask in mTask
 //   QVector<Task*> pTask;
  //  void saveTask(QVector<Task*> lTask); //salva lTask su mTask
    void addTask(Task *task); // aggiunge un task a mTask
public slots:
    void rename();
    void saveTask(QVector<Task*> lTask); //salva lTask su mTask

signals:
    void removed(ListToDo *listToDo);
    void statusChanged(ListToDo *listToDo);
private slots:
    void checked(bool checked);
    void on_checkbox_clicked();
private:
    Ui::ListToDo *cui;
 //   Ui::Board *bui;
    QVector<Task*> mTask;
};

#endif // TASK_H
