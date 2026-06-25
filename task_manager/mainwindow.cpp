#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "./task/task.h"
#include <QLabel>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    Task* root = new Task("A");

    Task* t1 = new Task("b");
    Task* t11 = new Task("c");

    root->addChild(t1);
    t1->addChild(t11);

    QLabel* label = new QLabel(this);

    label->setText(t11->path());

    setCentralWidget(label);
}

MainWindow::~MainWindow()
{
    delete ui;
}
