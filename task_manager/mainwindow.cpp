#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "./task/task.h"
#include "./navigator/tasknavigator.h"
#include "./widget/taskcard.h"
#include "./widget/taskcanvas.h"
#include"./layout/tasklayoutengine.h"
#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>
#include <QLabel>
#include <QScrollArea>
#include <QGuiApplication>
#include <QScreen>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    m_root = new Task("root");
    m_root->name = "Task1";
    m_root->priority = "High";
    m_root->duration = "20 mins";
    m_root->status = "In Progress";
    Task* t1 = new Task("T1");
    t1->name = "Task1";
    t1->priority = "Medium";
    t1->duration = "10 mins";
    t1->status = "In Progress";
    m_root->addChild(t1);
    Task* t2 = new Task("Task2");
    t2->name = "Task2";
    t2->priority = "Medium";
    t2->duration = "1 hours";
    t2->status = "Done";
     m_root->addChild(t2);
    Task* t3 = new Task("Task3");
    t3->name = "Task3";
    t3->priority = "High";
    t3->duration = "12 hours";
    t3->status = "Pending";
    m_root->addChild(t3);
    Task* t11 = new Task("Task11");
    t11->name = "Task11";
    t11->priority = "Low";
    t11->duration = "1 hours";
    t11->status = "Done";
    t1->addChild(t11);
    Task* t12 = new Task("Task12");
    t12->name = "Task12";
    t12->priority = "Medium";
    t12->duration = "1 hours";
    t12->status = "Done";
    t1->addChild(t12);
    TaskLayoutEngine* engine = new TaskLayoutEngine();
    auto layout = engine->calculate(m_root);
    for(auto it = layout.begin(); it != layout.end(); ++it)
    {
        qDebug()
        << it.key()->name
        << it.value();
    }
    TaskCanvas* m_canvas = new TaskCanvas;
    m_canvas->setRoot(m_root);

    QScreen* screen = QGuiApplication::primaryScreen();
    QRect screenGeometry = screen->availableGeometry();   // excludes taskbar
    m_canvas->resize(screenGeometry.size());

    qDebug() << m_canvas->size();
    QScrollArea* scroll = new QScrollArea(this);
    scroll->setWidget(m_canvas);
    scroll->setWidgetResizable(false);
    setCentralWidget(scroll);
    /*TaskNavigator* task_navigator = new TaskNavigator(this);
    task_navigator->setRoot(m_root);
    QWidget *central = new QWidget(this);
    QVBoxLayout* vbox = new QVBoxLayout(central);
    QLabel *label = new QLabel;
    QPushButton* btn1 = new QPushButton("Go To T1");
    QPushButton* btn2 = new QPushButton("Go to T2");
    QPushButton* btn3 = new QPushButton("Go Up");
    vbox->addWidget(card);
    vbox->addWidget(label);
    vbox->addWidget(btn1);
    vbox->addWidget(btn2);
    vbox->addWidget(btn3);
    setCentralWidget(central);
    connect(task_navigator, &TaskNavigator::rootChanged, this, [label](Task* task){label->setText(task->path());});//connecting the label to reflect current root
    connect(btn1, &QPushButton::clicked, this, [task_navigator, t1](){task_navigator->navigateTo(t1);});
    connect(btn2, &QPushButton::clicked, task_navigator, [task_navigator, t1](){task_navigator->navigateTo(t1);});
    connect(btn3, &QPushButton::clicked, task_navigator, &TaskNavigator::goUp);
    task_navigator->setRoot(m_root);*/
}

MainWindow::~MainWindow()
{
    delete ui;
}
