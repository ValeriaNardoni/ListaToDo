#ifndef IMPORTANT_H
#define IMPORTANT_H

#include <QDialog>
#include <ListToDo.h>
#include <mainWindow.h>
#include <task.h>

namespace Ui {
    class ListToDo;
    class Board;
    class Task;
    class Important;
}

class Important : public QDialog
{
Q_OBJECT

public:
    explicit Important(QVector<ListToDo*> mListToDosI, QWidget *parent = 0);
    ~Important();

signals:


private slots:
    int updateStatus(QVector<ListToDo*> mListToDosI);

private:
    Ui::Important *iui;
    QVector<ListToDo*> mListToDosI;
};

#endif // IMPORTANT_H
