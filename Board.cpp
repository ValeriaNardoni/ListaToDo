#include <QtWidgets/QInputDialog>
#include "Board.h"
#include "ui_Board.h"
#include <mainWindow.h>
#include <ListToDo.h>
#include <task.h>
#include <QDebug>
#include <QScrollArea>
#include <QtWidgets/QtWidgets>

Board::Board(QVector<Task*> pTask, QString title, QWidget *parent) :
        QDialog(parent),
        bui(new Ui::Board),
        lTask()
        {
    copypTask(pTask);
   // updateStatus();
    bui->setupUi(this);
            for (auto t : lTask)
            {
                bui->TaskLayout->addWidget(t);
                connect(t, &Task::removed, this, &Board::removeTask);
                connect(t, &Task::statusChanged, this, &Board::taskstatusChanged);

            }

    this->setWindowTitle(title);
    bui->TaskLayout->activate()    ;

            updateStatus();






    qDebug() << parent;
    connect(bui->SaveTask, &QPushButton::clicked,
            [this] {
                emit TaskSaved(lTask);
                qDebug() << "emesso segnale" << lTask;
                qDebug() << this;

            });

    //connect(bui, TaskSaved(lTask), parent, &MainWindow::ContaImp);
}

Board::~Board()
{
    delete bui;
}

void Board::copypTask(QVector<Task*> pTask)
{
   lTask=pTask; //ptask variabile di passaggio mTask al ltask
}


void Board::on_Board_accepted()
{

}

QString Board::controlladata(QString data1,QString data2) // data da controllare. data in caso di errore
{
    QDate datacont = QDate::fromString(data1,"dd/MM/yyyy" ); // trasforma la stringa ingresso in QDate
    if (datacont.isValid( datacont.year(), datacont.month(), datacont.day() )) return data1;
    return data2;
}

void Board::on_addTaskButton_clicked()
{

    bool ok;


    QString name1 = QInputDialog::getText(this,
                                          tr("Add task name"),
                                          tr("Task name"),
                                          QLineEdit::Normal,
                                          tr("Untitled task"),
                                          &ok);

    if (ok && !name1.isEmpty()) {
        QDate data1 = QDate::currentDate();
        QString name2o=data1.toString("dd/MM/yyyy");

        QString name2 = QInputDialog::getText(this,
                                      tr("Add task date"),
                                      tr("Date dd/mm/yyyy"),
                                      QLineEdit::Normal,
                                      tr(name2o.toLatin1().data()),
                                      &ok);

        if (ok && !name2.isEmpty()) {
            QString name = name1 + " " + controlladata(name2, name2o);
            qDebug() << "Adding new task";

            Task *task = new Task(name);
            connect(task, &Task::removed, this, &Board::removeTask);
            connect(task, &Task::statusChanged, this, &Board::taskstatusChanged);
            lTask.append(task);

            bui->TaskLayout->addWidget(task);
            updateStatus();
        }
    }


}




void Board::removeTask(Task*task)
{
    lTask.removeOne(task);
    bui->TaskLayout->removeWidget(task);

    task->setParent(0);
    delete task;
    updateStatus();
}

void Board::taskstatusChanged(Task *task)
{
    updateStatus();
}




void Board::updateStatus()
{
    int completedCount = 0;

    for (auto t : lTask) {
        if (t->isCompleted()) {
            completedCount++;
        }
    }
    int todoCount = lTask.size() - completedCount;

    bui->statusLabel->setText(
            QString("Status: %1 todo / %2 completed")
                    .arg(todoCount)
                    .arg(completedCount));
}





void Board::closeEvent (QCloseEvent *event){

   int ret = QMessageBox::question(this,"Attention","Do you want to save your work before leaving?\n",
   QMessageBox::Save,QMessageBox::Cancel);
    if(ret == QMessageBox::Save)
            emit TaskSaved(lTask);

        // QMessageBox::information(this,"Attention","You pressed Save");

   // else QMessageBox::information(this,"Attention","You pressed Cancel");
}
