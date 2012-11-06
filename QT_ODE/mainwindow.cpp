#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->showMaximized();

    connect(ui->actionCamera_FPS, SIGNAL(triggered()), this, SLOT(checkMouseFPS()));
    connect(ui->actionCamera_Orbit, SIGNAL(triggered()), this, SLOT(checkMouseOrbit()));
    connect(ui->actionForce, SIGNAL(triggered()), this, SLOT(checkMouseForce()));
    connect(ui->actionTorque, SIGNAL(triggered()), this, SLOT(checkMouseTorque()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::checkMouseFPS()
{
//    ui->actionCamera_FPS->setChecked(true);
    ui->actionCamera_Orbit->setChecked(false);
    ui->actionForce->setChecked(false);
    ui->actionTorque->setChecked(false);

    ui->glframe->glwidget->setMouseFunction( MOUSE_FPS );
}

void MainWindow::checkMouseOrbit()
{
    ui->actionCamera_FPS->setChecked(false);
    //ui->actionCamera_Orbit->setChecked(true);
    ui->actionForce->setChecked(false);
    ui->actionTorque->setChecked(false);

    ui->glframe->glwidget->setMouseFunction( MOUSE_ORBIT );
}

void MainWindow::checkMouseForce()
{
    ui->actionCamera_FPS->setChecked(false);
    ui->actionCamera_Orbit->setChecked(false);
//    ui->actionForce->setChecked(true);
    ui->actionTorque->setChecked(false);

    ui->glframe->glwidget->setMouseFunction( MOUSE_FORCE );
}

void MainWindow::checkMouseTorque()
{
    ui->actionCamera_FPS->setChecked(false);
    ui->actionCamera_Orbit->setChecked(false);
    ui->actionForce->setChecked(false);
//    ui->actionTorque->setChecked(true);

    ui->glframe->glwidget->setMouseFunction( MOUSE_TORQUE );
}
