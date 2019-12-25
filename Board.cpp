#include <QtWidgets/QInputDialog>
#include "Board.h"
#include "ui_Board.h"
#include <mainWindow.h>
#include <ListToDo.h>
#include <task.h>
#include <QDebug>
#include <QScrollArea>
#include <QtWidgets/QtWidgets>

Board::Board(QVector<Task *> pTask, QString title, QWidget *parent) :
        QDialog(parent),
        bui(new Ui::Board),
        lTask() {
    copypTask(pTask);

    bui->setupUi(this);
    for (auto t : lTask) {
        bui->TaskLayout->addWidget(t);
        connect(t, &Task::removed, this, &Board::removeTask);
        connect(t, &Task::statusChanged, this, &Board::taskstatusChanged);

    }

    this->setWindowTitle(title);
    bui->TaskLayout->activate();

    updateStatus();


}

Board::~Board() {
    delete bui;
}

void Board::copypTask(QVector<Task *> pTask) {
    lTask = pTask; //ptask variabile di passaggio mTask al ltask
}


void Board::on_Board_accepted() {

}

QString Board::controlladata(QString data1, QString data2) // data da controllare. data in caso di errore
{
    QDate datacont = QDate::fromString(data1, "dd/MM/yyyy"); // trasforma la stringa ingresso in QDate
    if (datacont.isValid(datacont.year(), datacont.month(), datacont.day())) return data1;
    return data2;
}

void Board::on_addTaskButton_clicked() {

    bool ok;


    QString name1 = QInputDialog::getText(this,
                                          tr("Add task name"),
                                          tr("Task name"),
                                          QLineEdit::Normal,
                                          tr("Untitled task"),
                                          &ok);

    if (ok && !name1.isEmpty()) {
        QDate data1 = QDate::currentDate();
        QString name2o = data1.toString("dd/MM/yyyy");

        QString name2 = QInputDialog::getText(this,
                                              tr("Add task date"),
                                              tr("Date dd/mm/yyyy"),
                                              QLineEdit::Normal,
                                              tr(name2o.toLatin1().data()),
                                              &ok);

        if (ok && !name2.isEmpty()) {
            QString name = name1 + " " + controlladata(name2, name2o);


            Task *task = new Task(name);

            connect(task, &Task::removed, this, &Board::removeTask);
            connect(task, &Task::statusChanged, this, &Board::taskstatusChanged);
            lTask.append(task);

            bui->TaskLayout->addWidget(task);
            updateStatus();
        }
    }


}

int Board::on_searchTaskButton_clicked() {

    bool ok;
    QString searchtxt = QInputDialog::getText(this,
                                              tr("Search Task"),
                                              tr("Task name"),
                                              QLineEdit::Normal,
                                              tr("Untitled task"), &ok);
    int found = 0;


    QString nomeFile = "TMPINTT.LTD";
    if (nomeFile != "") {
        QFile file(nomeFile);

        if (file.open(QIODevice::ReadWrite)) {
            QTextStream stream(&file);

            stream << lTask.size() << endl; // flusso sul file
            for (auto t : lTask) {
                if ((t->name()).contains(searchtxt, Qt::CaseInsensitive)) {
                    found++;

                    stream << t->name() << endl;
                    stream << t->isCompleted() << endl;
                    stream << t->isImportant() << endl;

                }

            }
            for (auto t : lTask) {
                if (!(t->name()).contains(searchtxt, Qt::CaseInsensitive)) {

                    stream << t->name() << endl;
                    stream << t->isCompleted() << endl;
                    stream << t->isImportant() << endl;
                }


            }

            file.flush(); //svuota il buffer
            file.close();
        } else {
            QMessageBox::critical(this, tr("Errore"), tr("Non posso salvare il file"));
            return 0;
        }
    }

    if (found == 0) {
        QMessageBox::critical(0, tr("Alert"), tr("Task not found.\n"), QMessageBox::Ok);


    }

    delAllTask();
    if (nomeFile != "") {
        QFile file(nomeFile);
        if (!file.open(QIODevice::ReadOnly)) {
            QMessageBox::critical(this, tr("Error"),
                                  tr("Could not open file"));
            return 0;
        }
        QTextStream stream(&file);
        int nt = stream.readLine().toInt(); // nl=numero listodo
        for (int n = 0; n < nt; n++) //inserisce task
        {

            QString nameTask = stream.readLine();
            Task *task = new Task(nameTask);
            lTask.append(task);
            bui->TaskLayout->addWidget(lTask[n]);
            connect(lTask[n], &Task::removed, this, &Board::removeTask);
            connect(lTask[n], &Task::statusChanged, this, &Board::taskstatusChanged);

            QString Tfatto = stream.readLine();

            if (Tfatto == "1") {
                task->setCompleted();
            }

            QString Timp = stream.readLine();

            if (Timp == "1") {
                task->setImportant();
            }


        }
        bui->TaskLayout->activate();


        file.close();
    }

    updateStatus();
    return found;


};

void Board::delAllTask() {
    int size = lTask.size();
    if (size != 0) {
        for (int n = 0; n < size; n++) {
            removeTask(lTask[0]);
        }
    }
}

void Board::removeTask(Task *task) {
    lTask.removeOne(task);
    bui->TaskLayout->removeWidget(task);

    task->setParent(0);
    delete task;
    updateStatus();
}

void Board::taskstatusChanged(Task *task) {
    updateStatus();
}


void Board::updateStatus() {
    int completedCount = 0;

    for (auto t : lTask) {
        if (t->isCompleted()) {
            completedCount++;
        }
    }
    int todoCount = lTask.size() - completedCount;

    bui->statusLabel->setText(
            QString("Status: %1 todo / %2 completed")
                    .arg(lTask.size())
                    .arg(completedCount));
}


void Board::closeEvent(QCloseEvent *event) {

    emit TaskSaved(lTask);


}
