#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow)
{
	ui->setupUi(this);
}

MainWindow::~MainWindow()
{
	delete ui;
}

void MainWindow::resizeEvent(QResizeEvent* evt)
{
	QPixmap bkgnd("C:/Projects/ProjectC++/P_Soduko/mini-project-2-sudoku-MohamadAminA/P_Soduko/img/Background/Background.png");
	bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);

	QPalette palette;

	palette.setBrush(QPalette::Background, bkgnd);
	this->setPalette(palette);

	QMainWindow::resizeEvent(evt); // call inherited implementation
}
