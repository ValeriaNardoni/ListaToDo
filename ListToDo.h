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
    void updatestat(const QString &textstat);
public slots:
    void rename();
    void saveTask(QVector<Task*> lTask); //salva lTask su mTask
    void aprifinestra(ListToDo *listToDo);

signals:
    void removed(ListToDo *listToDo);
    void statusChanged(ListToDo *listToDo);
    void cambioImp(ListToDo *listToDo);
private slots:

    void on_checkbox_clicked();
private:
    Ui::ListToDo *cui;
 //   Ui::Board *bui;
    QVector<Task*> mTask;
};

#endif // TASK_H
