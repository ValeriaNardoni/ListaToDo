#include "mainWindow.h"
#include "ui_mainWindow.h"
#include <QDebug>
#include <QInputDialog>
#include <QtWidgets/QFileDialog>
#include <QTextStream>
#include <QtWidgets/QMessageBox>


MainWindow::MainWindow(QWidget *parent) :
        QMainWindow(parent),
        ui(new Ui::MainWindow),
        mListToDos() //QVector
{

    ui->setupUi(this);

    connect(ui->addListToDoButton, &QPushButton::clicked,
            this, &MainWindow::addListToDo);


    updateStatus();

}

MainWindow::~MainWindow()
{

    delete ui;
}


void MainWindow::addListToDo()  //la funzione  mi permette di aggiungere nuove checklist
{
    bool ok;


    QString name = QInputDialog::getText(this,
                                         tr("Add listToDo"),
                                         tr("ListToDo name"),
                                         QLineEdit::Normal,
                                         tr("Untitled listToDo"), &ok);
    if (ok && !name.isEmpty()) {
        qDebug() << "Adding new listToDo";
        ListToDo *listToDo = new ListToDo(name);
        connect(listToDo, &ListToDo::removed, this, &MainWindow::removeListToDo);
        connect(listToDo, &ListToDo::statusChanged, this, &MainWindow::listToDoStatusChanged);
        mListToDos.append(listToDo); //la nuova checklist viene aggiunta al QVector

        ui->listToDosLayout->addWidget(listToDo);
        updateStatus();
    }
}





void MainWindow::removeListToDo(ListToDo *listToDo) //la funzione mi permette di eliminare una checklist
{
    mListToDos.removeOne(listToDo);
    ui->listToDosLayout->removeWidget(listToDo);

    //listToDo->setParent(0);
    delete listToDo;
    updateStatus();
}

void MainWindow::listToDoStatusChanged(ListToDo *listToDo)
{
    updateStatus();
}

void MainWindow::updateStatus()
{

    int todoCount = mListToDos.size() ;

    ui->statusLabel->setText(
            QString("Status: %1 Checklist ")
                    .arg(todoCount)
                    );
}

void MainWindow::on_Save_clicked()
{
    QString nomeFile = QFileDialog::getSaveFileName(this,
                                                    tr("File di Testo (*.txt);;C++ File (*.cpp *.h)"));
    if (nomeFile != "") {
        QFile file(nomeFile);

        if (file.open(QIODevice::ReadWrite)) {
            QTextStream stream(&file);
            qDebug() << "save file";
            qDebug() << mListToDos.size();
            //qDebug() << mListToDos;
            // fare cicli per listtodo e sottocicli per task
            stream << mListToDos.size() <<endl; // flusso sul file

            for (auto t : mListToDos)
            {


                qDebug() << t->name();  //nome ListToDo
                stream << t->name() <<endl;

                qDebug()<< t->retTask().size();  // numero di task della lista
                stream << t->retTask().size() <<endl;

                // qDebug()<< t->retTask(); // Puntatori ai Task
                for (auto a : t->retTask())
                {
                    // qDebug() << a;  // puntatori ai singoli Task
                    qDebug() << a->name(); // nome task
                    stream << a->name() <<endl;
                    qDebug() << a->isCompleted(); // task completato
                    stream << a->isCompleted() <<endl;
                    qDebug() << a->isImportant();
                    stream << a->isImportant() <<endl;
                }


                // qDebug()<< ListToDo::t::name();

              //  qDebug()<< t->listToDosLayout;

            }

            file.flush(); //svuota il buffer
            file.close();
        }
        else {
            QMessageBox::critical(this, tr("Errore"), tr("Non posso salvare il file"));
            return;
        }
    }
};
void MainWindow::on_OpenFile_clicked()
{

    QString fileName = QFileDialog::getOpenFileName(this,
                                                    tr("Text Files ('''.txt);;C++ Files ('''.cpp '''.h)"));

    if (fileName != "") {
        QFile file(fileName);
        if (!file.open(QIODevice::ReadOnly)) {
            QMessageBox::critical(this, tr("Error"),
                                  tr("Could not open file"));
            return;
        }
        QTextStream stream(&file);
        int nl= stream.readLine().toInt(); // nl=numero listodo
        qDebug()<< nl<< endl;
        for (int n=0; n<nl; n++)
        {
            QString name = stream.readLine();

            qDebug()<< name << " nome listtodo";

            ListToDo *listToDo = new ListToDo(name);
            connect(listToDo, &ListToDo::removed, this, &MainWindow::removeListToDo);
            connect(listToDo, &ListToDo::statusChanged, this, &MainWindow::listToDoStatusChanged);
            mListToDos.append(listToDo);

            ui->listToDosLayout->addWidget(listToDo);
            updateStatus();



            int nt= stream.readLine().toInt(); // numero task



            for (int m=0; m<nt; m++) //inserisce task
            {
                QString nameTask = stream.readLine();
                qDebug()<< nameTask << " nome task";
                qDebug() << "Adding new task";

                Task *task = new Task(nameTask);
                // connect(task, &Task::removed, this, &Board::removeTask);
                // connect(task, &Task::statusChanged, this, &Board::taskstatusChanged);connect(task, &Task::removed, this, &Board::removeTask);
                // connect(task, &Task::statusChanged, this, &Board::taskstatusChanged);

                // listToDo->addTask(task); // da spostare dopo caricati gli attributi

                QString Tfatto = stream.readLine();
                qDebug()<< Tfatto << " fatto";

                if (Tfatto=="1"){
                   qDebug() << "XXXXXXXXXXXXXXXXXXXXXXXXXXXX";
                    task->setCompleted();
                }

                QString Timp = stream.readLine();
                qDebug()<< Timp << " importante";
                if (Timp=="1"){
                    qDebug() << "IIIIIIIIIIIIIIIIIIIIIIIIII";
                    task->setImportant();
                }

                listToDo->addTask(task);
            }



        }

        //while( !stream.atEnd() )
        //{
        //    qDebug()<< stream.readLine();
        //}

        //QString contents = file.readAll().constData();
        //qDebug() << contents; // scrive tutto il file su debug

        //textEdit->setPlainText(contents);
        file.close();
    }



}