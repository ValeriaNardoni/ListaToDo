//
// Created by Valeria on 22/09/19.
//


#include <QtWidgets/QInputDialog>
#include "Important.h"
#include "ui_Important.h"
#include "Board.h"
#include <mainWindow.h>
#include <ListToDo.h>
#include <task.h>
#include <QDebug>
#include <QScrollArea>
#include <QtWidgets/QtWidgets>

Important::Important(QVector<ListToDo*> mListToDosI, QWidget *parent) :
        QDialog(parent),
        iui(new Ui::Important),
        mListToDosI()
{
        qDebug() << "Important Window";
        iui->setupUi(this);
        qDebug() << mListToDosI.size();
        Important::updateStatus(mListToDosI);
        iui->statusLabel->setText(
            QString("Status: %1 Importants Tasks to do")
                    .arg(Important::updateStatus(mListToDosI)));

}

Important::~Important()
{
    delete iui;
}

int Important::updateStatus(QVector<ListToDo*> mListToDosI)
{
    int importantCount = 0;
    QString Ilist="";
    QString Itask="";
    QString IImpo="";
    qDebug() << mListToDosI.size();
    for (auto t : mListToDosI) {
        Ilist= t->name();

        qDebug() << t->name();  //nome ListToDo


        qDebug() << t->retTask().size();  // numero di task della lista


        // qDebug()<< t->retTask(); // Puntatori ai Task
        for (auto a : t->retTask()) {
            Itask = a->name();
            qDebug() << a->name(); // nome task

            qDebug() << a->isCompleted(); // task completato

            qDebug() << a->isImportant();
            if (a->isImportant() && !a->isCompleted()){
                importantCount ++;
                IImpo= IImpo + Ilist + " " + Itask + "\n";
            }
        }

    }
    qDebug() << IImpo;
    iui->label->setText(IImpo);
    return importantCount;

}