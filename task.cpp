#include "task.h"
#include "ui_task.h"
#include <QInputDialog>
#include <QDate>
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
        tui(new Ui::Task) {


    tui->setupUi(this);
    setName(name);
    Important = false;
    connect(tui->editButton, &QPushButton::clicked,
            this, &Task::rename);


    connect(tui->removeButton, &QPushButton::clicked,
            [this] {
                emit removed(this);
            });

    connect(tui->checkbox, &QCheckBox::toggled, this, &Task::checked);


}

Task::~Task() {
    delete tui;
}


void Task::setName(const QString &name) {
    tui->checkbox->setText(name);
}

QString Task::name() const {
    return tui->checkbox->text();
}

bool Task::isCompleted() const {
    return tui->checkbox->isChecked();
}

QString Task::controlladata(QString data1, QString data2) // data da controllare. data in caso di errore
{
    QDate datacont = QDate::fromString(data1, "dd/MM/yyyy"); // trasforma la stringa ingresso in QDate
    if (datacont.isValid(datacont.year(), datacont.month(), datacont.day())) return data1;
    return data2;
}


void Task::rename() {
    bool ok;
    QString name = this->name();

    QString name1o = name.left(name.length() - 11);

    QString name2o = name.right(10);

    QString name1 = QInputDialog::getText(this, tr("Edit task"),
                                          tr("Task name"),
                                          QLineEdit::Normal,
                                          name1o, &ok);
    if (ok && !name1.isEmpty()) {
        QString name2 = QInputDialog::getText(this,
                                              tr("Add task date"),
                                              tr("Date dd/mm/yyyy"),
                                              QLineEdit::Normal,
                                              name2o,
                                              &ok);


        setName(name1 + " " + controlladata(name2, name2o));
    }
}

void Task::checked(bool checked) {
    QFont font(tui->checkbox->font());

    font.setStrikeOut(checked);

    tui->checkbox->setFont(font);

    emit statusChanged(this);
}

void Task::setCompleted() {
    Task::checked(true);
    tui->checkbox->setChecked(1);

}


void Task::setImportant() {
    Task::on_Important_clicked();
}


void Task::on_Important_clicked() {
    Task::Important = true;
    QPixmap pix("/home/valeria/Scrivania/03.11.19.b/ListaToDo-master/stella.png");
    tui->label_pic->setPixmap(pix.scaled(15, 15, Qt::KeepAspectRatio));

    QPalette palette = tui->checkbox->palette();
    palette.setColor(tui->checkbox->foregroundRole(), Qt::red);
    tui->checkbox->setPalette(palette);

}

void Task::on_NotImportant_clicked() {
    Task::Important = false;
    QPixmap pix("");
    tui->label_pic->setPixmap(pix.scaled(15, 15, Qt::KeepAspectRatio));
    QPalette palette = tui->checkbox->palette();
    palette.setColor(tui->checkbox->foregroundRole(), Qt::black);
    tui->checkbox->setPalette(palette);

}

bool Task::isImportant() const {

    return (this->Important);

}

