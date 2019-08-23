#include "task.h"
#include "ui_task.h"
#include <QInputDialog>
#include <QFont>
#include <Board.h>
#include <stdio.h>
#include <QtWidgets/QLabel>
#include <QtWidgets/QColorDialog>
#include <QPixmap>
#include <QFont>
#include <QMouseEvent>


Task::Task(const QString &name, QWidget *parent) :
        QWidget(parent),
        tui(new Ui::Task)
{


    tui->setupUi(this);
    setName(name);
    Important=false;
    connect(tui->editButton, &QPushButton::clicked,
            this, &Task::rename);


    connect(tui->removeButton, &QPushButton::clicked,
            [this] {
                emit removed(this);
            });

    connect(tui->checkbox, &QCheckBox::toggled, this, &Task::checked);


}

Task::~Task()
{
    delete tui;
}


void Task::setName(const QString &name)
{
    tui->checkbox->setText(name);
}

QString Task::name() const
{
    return tui->checkbox->text();
}

bool Task::isCompleted() const
{
    return tui->checkbox->isChecked();
}

void Task::rename()
{
    bool ok;
    QString value = QInputDialog::getText(this, tr("Edit task"),
                                          tr("Task name"),
                                          QLineEdit::Normal,
                                          this->name(), &ok);
    if (ok && !value.isEmpty()) {
        setName(value);
    }
}

void Task::checked(bool checked)
{
    QFont font(tui->checkbox->font());

    font.setStrikeOut(checked);

    tui->checkbox->setFont(font);

    emit statusChanged(this);
}

void Task::setCompleted()
{
    Task::checked(true);
    tui->checkbox->setChecked(1);
    // emit statusChanged(this);
}


void Task::setImportant()
{
    //Task::Important=true;
    Task::on_Important_clicked();
}


void Task::on_Important_clicked()
{
    Task::Important=true;
    QPixmap pix("/home/valeria/Scrivania/ProgettoListaToDo-master(6)/ProgettoListaToDo-master/stella.png");
    tui->label_pic-> setPixmap(pix.scaled(15,15,Qt::KeepAspectRatio));

    QPalette palette = tui->checkbox->palette();
    palette.setColor(tui->checkbox->foregroundRole(), Qt::red);
    tui->checkbox->setPalette(palette);

    }

void Task::on_NotImportant_clicked()
{
    Task::Important=false;
    QPixmap pix("");
    tui->label_pic-> setPixmap(pix.scaled(15,15,Qt::KeepAspectRatio));
    QPalette palette = tui->checkbox->palette();
    palette.setColor(tui->checkbox->foregroundRole(), Qt::black);
    tui->checkbox->setPalette(palette);

}

bool Task::isImportant() const
{

   return (this->Important);
    //return tui->checkbox->palette();
}

