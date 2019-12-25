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

Important::Important(QVector<ListToDo *> mListToDosI, QWidget *parent) :
        QDialog(parent),
        iui(new Ui::Important),
        mListToDosI() {
    qDebug() << "Important Window";
    iui->setupUi(this);
    qDebug() << mListToDosI.size();
    Important::updateStatus(mListToDosI);
    iui->statusLabel->setText(
            QString("Status: %1 Importants Tasks to do")
                    .arg(Important::updateStatus(mListToDosI)));

}

Important::~Important() {
    delete iui;
}

int Important::updateStatus(QVector<ListToDo *> mListToDosI) {
    int importantCount = 0;
    QString Ilist = "";
    QString Itask = "";
    QString IImpo = "";

    for (auto t : mListToDosI) {
        Ilist = t->name();


        for (auto a : t->retTask()) {
            Itask = a->name();

            if (a->isImportant() && !a->isCompleted()) {
                importantCount++;
                IImpo = IImpo + Ilist + " " + Itask + "\n";
            }
        }

    }

    iui->label->setText(IImpo);
    return importantCount;

}