#ifndef TASK_H
#define TASK_H

#include <QWidget>
#include <QtWidgets/QListView>
#include <QDebug>

#include <QAbstractItemModel>
#include <QListView>
#include <QMouseEvent>

namespace Ui {
    class ListToDo;
    class Board;
    class Task;
}

class Task : public QWidget
{
Q_OBJECT

public:
    explicit Task(const QString &name, QWidget *parent=0);
    ~Task();

    void setName(const QString &name);
    QString name() const;
    bool isCompleted() const;
    bool isImportant() const;
    void setCompleted();
    void setImportant();

public slots:
    void rename();

signals:
    void removed(Task *task);
    void statusChanged(Task *task);
private slots:
    void checked(bool checked);
void on_Important_clicked();




private:
    Ui::Task *tui;
    bool Important;
};

#endif // TASK_H
