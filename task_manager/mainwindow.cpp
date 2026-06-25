#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "./task/task.h"
#include "./navigator/tasknavigator.h"

#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>
#include <QLabel>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    Task* root = new Task("root");
    Task* t1 = new Task("T1");
    Task* t11 = new Task("T11");
    root->addChild(t1);
    t1->addChild(t11);
    TaskNavigator* task_navigator = new TaskNavigator(this);
    task_navigator->setRoot(root);
    QWidget *central = new QWidget(this);
    QVBoxLayout* vbox = new QVBoxLayout(central);
    QLabel *label = new QLabel;
    QPushButton* btn1 = new QPushButton("Go To T1");
    QPushButton* btn2 = new QPushButton("Go to T2");
    QPushButton* btn3 = new QPushButton("Go Up");
    vbox->addWidget(label);
    vbox->addWidget(btn1);
    vbox->addWidget(btn2);
    vbox->addWidget(btn3);
    setCentralWidget(central);
    connect(task_navigator, &TaskNavigator::rootChanged, this, [label](Task* task){label->setText(task->path());});//connecting the label to reflect current root
    connect(btn1, &QPushButton::clicked, this, [task_navigator, t1](){task_navigator->navigateTo(t1);});
    connect(btn2, &QPushButton::clicked, task_navigator, [task_navigator, t11](){task_navigator->navigateTo(t11);});
    connect(btn3, &QPushButton::clicked, task_navigator, &TaskNavigator::goUp);
    task_navigator->setRoot(root);
}

MainWindow::~MainWindow()
{
    delete ui;
}
