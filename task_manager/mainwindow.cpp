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
#include "./widget/breadcrumb.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    m_root = new Task("root");
    m_root->name = "root";
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
    TaskCanvas* m_canvas = new TaskCanvas;
    m_canvas->setRoot(t11);

    TaskNavigator* task_navigator = new TaskNavigator(this);
    task_navigator->setRoot(t11);
    connect(m_canvas, &TaskCanvas::navigateRequested, task_navigator, &TaskNavigator::navigateTo);//canvas to navigator
    connect(task_navigator, &TaskNavigator::rootChanged, m_canvas, &TaskCanvas::setRoot);//navigator to canvas

    QScreen* screen = QGuiApplication::primaryScreen();
    QRect screenGeometry = screen->availableGeometry();   // excludes taskbar
    m_canvas->resize(screenGeometry.size());

    QScrollArea* scroll = new QScrollArea(this);
    scroll->setWidget(m_canvas);
    scroll->setWidgetResizable(false);

    BreadCrumb* m_breadCrumb = new BreadCrumb(this, t11);
    connect(m_breadCrumb, &BreadCrumb::navigateTo, task_navigator,&TaskNavigator::navigateTo);//breadcrumb to navigator
    connect(task_navigator,&TaskNavigator::rootChanged,m_breadCrumb, &BreadCrumb::setTask);//navigatorto breadcrumb
    QWidget* main_widget = new QWidget(this);
    QVBoxLayout* main_layout = new QVBoxLayout(this);
    main_widget->setLayout(main_layout);
    main_layout->addWidget(m_breadCrumb);
    main_layout->addWidget(scroll);
    setCentralWidget(main_widget);

}

MainWindow::~MainWindow()
{
    delete ui;
}
