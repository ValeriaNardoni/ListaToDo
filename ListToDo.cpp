#include "ListToDo.h"
#include "ui_ListToDo.h"
#include <QInputDialog>
#include <QFont>
#include <Board.h>
#include <QApplication>
#include <QtWidgets/QFileDialog>


ListToDo::ListToDo(const QString &name, QWidget *parent) :
        QWidget(parent),
        cui(new Ui::ListToDo)
{
    cui->setupUi(this);
    setName(name);
    connect(cui->editButton, &QPushButton::clicked,
            this, &ListToDo::rename);


    connect(cui->removeButton, &QPushButton::clicked,
            [this] {
                emit removed(this);
            });


    //  qDebug() << this;
    //  qDebug() << this->name();

    //  qDebug() << ListToDo::name();

   //connect(Board(mTask), &Board::TaskSaved, this, ListToDo::saveTask(mTask)  ); //////////////////

}

ListToDo::~ListToDo()
{
    delete cui;
}

void ListToDo::saveTask(QVector<Task*> lTask) //salva lTask su mtask
{
    //qDebug() << "Salvataggio task - segnale ricevuto";
   //
    mTask=lTask;
    emit cambioImp(this);
    //qDebug() << "EMESSO cambioImp";
    //qDebug() << "nuovo valore mTask" << mTask;
    //connect(cui, &ListToDo::cambioImp, ui ,&MainWindow::ContaImp);
}


void ListToDo::setName(const QString &name)
{
    cui->checkbox->setText(name);
}

QString ListToDo::name() const //restituisce il nome della lista

{
    return cui->checkbox->text();
}

QVector<Task*> ListToDo::retTask() const
{
   return mTask;
}

bool ListToDo::isCompleted() const
{
    return cui->checkbox->isChecked();
}

void ListToDo::rename()
{
    bool ok;
    QString value = QInputDialog::getText(this, tr("Edit listToDo"),
                                          tr("ListToDo name"),
                                          QLineEdit::Normal,
                                          this->name(), &ok);
    if (ok && !value.isEmpty()) {
        setName(value);
    }
}

void ListToDo::updatestat(const QString &textstat)
{
    cui->statlist->setText(textstat);
}


void ListToDo::on_checkbox_clicked()
{

    Board *board = new Board(mTask, cui->checkbox->text());
    //Board Board(mTask); //mTask
    //qDebug() << cui->checkbox->text();
    board->setModal(true);

   connect(board, &Board::TaskSaved, this, &ListToDo::saveTask  );

    board->exec();
}

void ListToDo::aprifinestra(ListToDo* t)
{
    //t->cui->checkbox->setFocus();
    t->on_checkbox_clicked();
}

void ListToDo::addTask( Task *task)
{
    ListToDo::mTask.append(task);
}