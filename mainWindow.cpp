#include "mainWindow.h"
#include "ui_mainWindow.h"
#include <QDebug>
#include <QInputDialog>
#include <QtWidgets/QFileDialog>
#include <QTextStream>
#include <QtWidgets/QMessageBox>
#include <Important.h>
#include <ui_Important.h>


MainWindow::MainWindow(QWidget *parent) :
        QMainWindow(parent),
        ui(new Ui::MainWindow),
        mListToDos() //QVector
{

    ui->setupUi(this);
   // connect(board, &Board::TaskSaved, this, &ListToDo::saveTask  ); //kkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkk
    connect(ui->addListToDoButton, &QPushButton::clicked,
            this, &MainWindow::addListToDo);
    //connect(ListToDo, &ListToDo::cambioImp, ui ,&MainWindow::ContaImp);
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
        //qDebug() << "Adding new listToDo";
        ListToDo *listToDo = new ListToDo(name);
        connect(listToDo, &ListToDo::removed, this, &MainWindow::removeListToDo);
        connect(listToDo, &ListToDo::statusChanged, this, &MainWindow::listToDoStatusChanged);
        connect(listToDo, &ListToDo::cambioImp, this, &MainWindow::listToDoStatusChanged);
        mListToDos.append(listToDo); //la nuova checklist viene aggiunta al QVector

        ui->listToDosLayout->addWidget(listToDo);
        updateStatus();
    }
}

void MainWindow::addListToDoTest(QString name)  //funzione Test mi permette di aggiungere nuove checklist nei test
{

        //qDebug() << "Adding new listToDo";
        ListToDo *listToDo = new ListToDo(name);
        connect(listToDo, &ListToDo::removed, this, &MainWindow::removeListToDo);
        connect(listToDo, &ListToDo::statusChanged, this, &MainWindow::listToDoStatusChanged);
        connect(listToDo, &ListToDo::cambioImp, this, &MainWindow::listToDoStatusChanged);
        mListToDos.append(listToDo); //la nuova checklist viene aggiunta al QVector

        ui->listToDosLayout->addWidget(listToDo);
        updateStatus();

}



void MainWindow::removeListToDo(ListToDo *listToDo)//la funzione mi permette di eliminare una checklist
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
    int importt=0;

    ui->statusLabel->setText(
            QString("Status: %1 Checklist ")
                    .arg(todoCount)
                    );
    importt=ContaImp();
    //qDebug()<<"numero importanti: "<< importt;
    ui->importantButton->setText(QString("%1 Importants Tasks to do") .arg(importt));
    // aggiornare il Bottone quando si carica file o da salva task !!!!!!!!!!!!!!!!!!!!!!!XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXxx
}

void MainWindow::on_Save_clicked()
{
    QString nomeFile = QFileDialog::getSaveFileName(this,
                                                    tr("File di Testo (*.txt);;C++ File (*.cpp *.h)"));
    if (nomeFile != "") {
        QFile file(nomeFile);

        if (file.open(QIODevice::ReadWrite)) {
            QTextStream stream(&file);
            //qDebug() << "save file";
            //qDebug() << mListToDos.size();
            //qDebug() << mListToDos;
            // fare cicli per listtodo e sottocicli per task
            stream << mListToDos.size() <<endl; // flusso sul file

            for (auto t : mListToDos)
            {


                //qDebug() << t->name();  //nome ListToDo
                stream << t->name() <<endl;

                //qDebug()<< t->retTask().size();  // numero di task della lista
                stream << t->retTask().size() <<endl;

                // qDebug()<< t->retTask(); // Puntatori ai Task
                for (auto a : t->retTask())
                {
                    // qDebug() << a;  // puntatori ai singoli Task
                    //qDebug() << a->name(); // nome task
                    stream << a->name() <<endl;
                    //qDebug() << a->isCompleted(); // task completato
                    stream << a->isCompleted() <<endl;
                    //qDebug() << a->isImportant();
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

int MainWindow::ContaImp()
{
    int importantCount = 0;

    for (auto t : mListToDos) {
        int taskCount=0;
        int compCount=0;

        // qDebug()<< t->retTask(); // Puntatori ai Task
        for (auto a : t->retTask()) {
            taskCount++;
            if (a->isImportant() && !a->isCompleted()){
                importantCount ++;

            }
            if (a->isCompleted()){
                compCount ++;

            }
        }
        t->updatestat(QString("%1 todo / %2 compl.") .arg(taskCount) .arg(compCount));
    }
    ui->importantButton->setText(QString("%1 Importants Tasks to do") .arg(importantCount));

    return importantCount;

}


void MainWindow::on_importantButton_clicked()
{
    //qDebug()<< "IMPORTANT WINDOW";
    Important *important = new Important(mListToDos);

    important->setModal(true);
    important->exec();
}

int MainWindow::on_searchButton_clicked(){
    if ( searchList(inputSearch())==0){
        QMessageBox::critical(0, tr("Alert"), tr("List not found.\n"), QMessageBox::Ok);
        //qDebug() << "NOT FOUND";

    }

}

QString MainWindow::inputSearch(){
    bool ok;
    QString searchtxt = QInputDialog::getText(this,
                                              tr("Search listToDo"),
                                              tr("ListToDo name"),
                                              QLineEdit::Normal,
                                              tr("Untitled listToDo"), &ok);
    return searchtxt;
}

int MainWindow::searchList(QString searchtxt)
{
    int found=0;
    // XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX salva il file ordinato su disco
    QString nomeFile = "TMPINT.LTD";
    if (nomeFile != "") {
        QFile file(nomeFile);

        if (file.open(QIODevice::ReadWrite)) {
            QTextStream stream(&file);
            //qDebug() << "save file";
            //qDebug() << mListToDos.size();
            stream << mListToDos.size() <<endl; // flusso sul file
            for (auto t : mListToDos)
            {   if ((t->name()).contains(searchtxt, Qt::CaseInsensitive))
                {
                    found++;
                    //qDebug() << "va bene " + t->name();  //nome ListToDo
                    stream << t->name() <<endl;
                    stream << t->retTask().size() <<endl;
                    for (auto a : t->retTask())
                    {
                        // qDebug() << a;  // puntatori ai singoli Task
                        stream << a->name() <<endl;
                        stream << a->isCompleted() <<endl;
                        stream << a->isImportant() <<endl;
                    }
                }

            }
            for (auto t : mListToDos)
            {
                if (!(t->name()).contains(searchtxt, Qt::CaseInsensitive))
                {
                    //qDebug() << "non va bene " + t->name();  //nome ListToDo
                    stream << t->name() <<endl;
                    stream << t->retTask().size() <<endl;
                    for (auto a : t->retTask())
                    {
                        // qDebug() << a;  // puntatori ai singoli Task
                        stream << a->name() <<endl;
                        stream << a->isCompleted() <<endl;
                        stream << a->isImportant() <<endl;
                    }
                }



            }

            file.flush(); //svuota il buffer
            file.close();
        }
        else {
            QMessageBox::critical(this, tr("Errore"), tr("Non posso salvare il file"));
            return 0;
        }
    }

   // if (found==0){
   //     QMessageBox::critical(0, tr("Alert"), tr("List not found.\n"), QMessageBox::Ok);
        //qDebug() << "NOT FOUND";

   // }

    delAllList(); // XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXx cancella tutte le liste

    //XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX ricarica da disco il file ordinato
    if (nomeFile != "")
    {
        QFile file(nomeFile);
        if (!file.open(QIODevice::ReadOnly))
        {
            QMessageBox::critical(this, tr("Error"),
                                  tr("Could not open file"));
            return 0;
        }
        QTextStream stream(&file);
        int nl= stream.readLine().toInt(); // nl=numero listodo
        for (int n=0; n<nl; n++)
        {
            QString name = stream.readLine();

            ListToDo *listToDo = new ListToDo(name);
            connect(listToDo, &ListToDo::removed, this, &MainWindow::removeListToDo);
            connect(listToDo, &ListToDo::statusChanged, this, &MainWindow::listToDoStatusChanged);
            connect(listToDo, &ListToDo::cambioImp, this, &MainWindow::listToDoStatusChanged);
            mListToDos.append(listToDo);

            ui->listToDosLayout->addWidget(listToDo);
            updateStatus();

            int nt= stream.readLine().toInt(); // numero task

            for (int m=0; m<nt; m++) //inserisce task
            {
                QString nameTask = stream.readLine();
                Task *task = new Task(nameTask);

                QString Tfatto = stream.readLine();

                if (Tfatto=="1")
                {
                    task->setCompleted();
                }

                QString Timp = stream.readLine();

                if (Timp=="1")
                {
                   task->setImportant();
                }

                listToDo->addTask(task);
            }



        }

        file.close();
    }

    ContaImp();
    updateStatus();
    return found;
}

void MainWindow::delAllList() {
    int size = mListToDos.size();
    if (size != 0) {
        for (int n = 0; n < size;n++)
        {
            removeListToDo(mListToDos[0]);
        }
    }
}




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
        //qDebug()<< nl<< endl;
        for (int n=0; n<nl; n++)
        {
            QString name = stream.readLine();

            //qDebug()<< name << " nome listtodo";

            ListToDo *listToDo = new ListToDo(name);
            connect(listToDo, &ListToDo::removed, this, &MainWindow::removeListToDo);
            connect(listToDo, &ListToDo::statusChanged, this, &MainWindow::listToDoStatusChanged);
            connect(listToDo, &ListToDo::cambioImp, this, &MainWindow::listToDoStatusChanged);
            mListToDos.append(listToDo);

            ui->listToDosLayout->addWidget(listToDo);
            updateStatus();



            int nt= stream.readLine().toInt(); // numero task



            for (int m=0; m<nt; m++) //inserisce task
            {
                QString nameTask = stream.readLine();
                //qDebug()<< nameTask << " nome task";
                //qDebug() << "Adding new task";

                Task *task = new Task(nameTask);
                // connect(task, &Task::removed, this, &Board::removeTask);
                // connect(task, &Task::statusChanged, this, &Board::taskstatusChanged);connect(task, &Task::removed, this, &Board::removeTask);
                // connect(task, &Task::statusChanged, this, &Board::taskstatusChanged);

                // listToDo->addTask(task); // da spostare dopo caricati gli attributi

                QString Tfatto = stream.readLine();
                //qDebug()<< Tfatto << " fatto";

                if (Tfatto=="1"){
                  // qDebug() << "XXXXXXXXXXXXXXXXXXXXXXXXXXXX";
                    task->setCompleted();
                }

                QString Timp = stream.readLine();
                //qDebug()<< Timp << " importante";
                if (Timp=="1"){
                   // qDebug() << "IIIIIIIIIIIIIIIIIIIIIIIIII";
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

ContaImp();

}

void MainWindow::caricaTest(QString nometest)
{

    QString fileName = nometest;

    if (fileName != "") {
        QFile file(fileName);
        if (!file.open(QIODevice::ReadOnly)) {
            QMessageBox::critical(this, tr("Error"),
                                  tr("Could not open file"));
            return;
        }
        QTextStream stream(&file);
        int nl= stream.readLine().toInt(); // nl=numero listodo
        //qDebug()<< nl<< endl;
        for (int n=0; n<nl; n++)
        {
            QString name = stream.readLine();

            //qDebug()<< name << " nome listtodo";

            ListToDo *listToDo = new ListToDo(name);
            connect(listToDo, &ListToDo::removed, this, &MainWindow::removeListToDo);
            connect(listToDo, &ListToDo::statusChanged, this, &MainWindow::listToDoStatusChanged);
            connect(listToDo, &ListToDo::cambioImp, this, &MainWindow::listToDoStatusChanged);
            mListToDos.append(listToDo);

            ui->listToDosLayout->addWidget(listToDo);
            updateStatus();



            int nt= stream.readLine().toInt(); // numero task



            for (int m=0; m<nt; m++) //inserisce task
            {
                QString nameTask = stream.readLine();
                //qDebug()<< nameTask << " nome task";
                //qDebug() << "Adding new task";

                Task *task = new Task(nameTask);
                // connect(task, &Task::removed, this, &Board::removeTask);
                // connect(task, &Task::statusChanged, this, &Board::taskstatusChanged);connect(task, &Task::removed, this, &Board::removeTask);
                // connect(task, &Task::statusChanged, this, &Board::taskstatusChanged);

                // listToDo->addTask(task); // da spostare dopo caricati gli attributi

                QString Tfatto = stream.readLine();
                //qDebug()<< Tfatto << " fatto";

                if (Tfatto=="1"){
                    //qDebug() << "XXXXXXXXXXXXXXXXXXXXXXXXXXXX";
                    task->setCompleted();
                }

                QString Timp = stream.readLine();
                //qDebug()<< Timp << " importante";
                if (Timp=="1"){
                    //qDebug() << "IIIIIIIIIIIIIIIIIIIIIIIIII";
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

    ContaImp();

}