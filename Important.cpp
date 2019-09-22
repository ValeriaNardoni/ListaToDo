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
}

Important::~Important()
{
    delete iui;
}