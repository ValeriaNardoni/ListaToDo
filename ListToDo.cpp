#include "ListToDo.h"
#include "ui_ListToDo.h"
#include <QInputDialog>
#include <QFont>
#include <Board.h>
#include <QApplication>
#include <QtWidgets/QFileDialog>


ListToDo::ListToDo(const QString &name, QWidget *parent) :
        QWidget(parent),
        cui(new Ui::ListToDo) {
    cui->setupUi(this);
    setName(name);
    connect(cui->editButton, &QPushButton::clicked,
            this, &ListToDo::rename);


    connect(cui->removeButton, &QPushButton::clicked,
            [this] {
                emit removed(this);
            });


}

ListToDo::~ListToDo() {
    delete cui;
}

void ListToDo::saveTask(QVector<Task *> lTask) //salva lTask su mtask
{

    mTask = lTask;
    emit cambioImp(this);

}


void ListToDo::setName(const QString &name) {
    cui->checkbox->setText(name);
}

QString ListToDo::name() const {
    return cui->checkbox->text();
}

QVector<Task *> ListToDo::retTask() const {
    return mTask;
}

bool ListToDo::isCompleted() const {
    return cui->checkbox->isChecked();
}

void ListToDo::rename() {
    bool ok;
    QString value = QInputDialog::getText(this, tr("Edit listToDo"),
                                          tr("ListToDo name"),
                                          QLineEdit::Normal,
                                          this->name(), &ok);
    if (ok && !value.isEmpty()) {
        setName(value);
    }
}

void ListToDo::updatestat(const QString &textstat) {
    cui->statlist->setText(textstat);
}


void ListToDo::on_checkbox_clicked() {

    Board *board = new Board(mTask, cui->checkbox->text());

    board->setModal(true);

    connect(board, &Board::TaskSaved, this, &ListToDo::saveTask);

    board->exec();
}

void ListToDo::aprifinestra(ListToDo *t) {

    t->on_checkbox_clicked();
}

void ListToDo::addTask(Task *task) {
    ListToDo::mTask.append(task);
}