#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QMessageBox"
#include "user.h"

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow)
{
	ui->setupUi(this);
	ui->label_2->hide();
	ui->lineEdit_name->hide();
}

MainWindow::~MainWindow()
{
	delete ui;
}

//آرایه نگه داری اطلاعات کاربرها
//User AllUsers [50];
QString Allusers[50];
int users_size = 0;
//تنظیم بکگراند به صورت تغییر پذیر
void MainWindow::resizeEvent(QResizeEvent* evt)
{
	QPixmap bkgnd("C:/Projects/ProjectC++/P_Soduko/mini-project-2-sudoku-MohamadAminA/P_Soduko/img/Background/Background.png");
	bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);

	QPalette palette;

	palette.setBrush(QPalette::Background, bkgnd);
	this->setPalette(palette);

	QMainWindow::resizeEvent(evt); // call inherited implementation
}

void MainWindow::on_pushButton_signIn_clicked()
{
	for(int i=0; Allusers[i] != "";i++)
		if(ui->listWidget_showAccount->currentItem()->text() == Allusers[i]){
			QMessageBox::information(this,"Login","Wellcome "+Allusers[i],QMessageBox::Ok);
			//----------------------ورود به قسمت بازی سودوکو
		}
}


void MainWindow::on_pushButton_newAccount_clicked()
{
	for(int i=0 ; i<users_size ; ++i)
		if(Allusers[i] == ui->lineEdit_name->text())
		{
			QMessageBox::warning(this,"Sign Up","This name is already taken !");
			ui->lineEdit_name->setText("");
			return;
		}
	if(ui->listWidget_showAccount->isHidden())
	{
		if(ui->lineEdit_name->text() != ""){
			ui->listWidget_showAccount->show();
			ui->pushButton_signIn->show();
			ui->label->show();
			ui->pushButton_signIn->setEnabled(true);
			ui->label_2->hide();
			ui->lineEdit_name->hide();
			ui->listWidget_showAccount->addItem(ui->lineEdit_name->text());
			ui->lineEdit_name->clear();
			++users_size;
		}
		else{
			QMessageBox::warning(this,"Sign Up","Name is Empty!");
			return;
		}
	}
	else{
		ui->listWidget_showAccount->hide();
		ui->pushButton_signIn->hide();
		ui->label->hide();
		ui->label_2->show();
		ui->lineEdit_name->show();
	}
}
