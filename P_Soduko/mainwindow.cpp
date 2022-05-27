#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QMessageBox"
#include "soduko.h"
MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow)
{
	ui->setupUi(this);
	ui->label_2->hide();
	ui->lineEdit_name->hide();
	ui->comboBox->hide();
	ui->label_3->hide();
	ui->pushButton_start->hide();
}

MainWindow::~MainWindow()
{
	delete ui;
}

class User
{
public:
	QString Nameget(){
		return this->Name;
	}
	void Nameset(QString new_name){
		Name = new_name;
	}
private:
	QString Name;

};
//آرایه نگه داری اطلاعات کاربرها
User Allusers [50];
User* empty_User = &Allusers[0];
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
	for(int i=0; Allusers[i].Nameget() != "";++i)
		if(QString::compare(ui->listWidget_showAccount->currentItem()->text(),Allusers[i].Nameget()) == 0){
			QMessageBox::information(this,"Login","Wellcome to Soduko\n"+Allusers[i].Nameget(),QMessageBox::Ok);
			//----------------------ورود به قسمت بازی سودوکو
			ui->label->hide();
			ui->label_2->hide();
			ui->listWidget_showAccount->hide();
			ui->pushButton_signIn->hide();
			ui->pushButton_newAccount->hide();
			ui->comboBox->show();
			ui->label_3->show();
			ui->pushButton_start->show();
		}
}


void MainWindow::on_pushButton_newAccount_clicked()
{
	if(!ui->listWidget_showAccount->isHidden()){
		ui->listWidget_showAccount->hide();
		ui->pushButton_signIn->hide();
		ui->label->hide();
		ui->label_2->show();
		ui->lineEdit_name->show();
		return;
	}
	if(ui->listWidget_showAccount->isHidden())
	{
		if(ui->lineEdit_name->text() == ""){
			QMessageBox::warning(this,"Sign Up","Name is Empty!");
			return;
		}
		if(ui->lineEdit_name->text() != ""){
			for(int i=0 ;Allusers[i].Nameget()!=""; ++i)
				if(ui->lineEdit_name->text() == Allusers[i].Nameget())
				{
					QMessageBox::warning(this,"Sign Up","This name is already taken !");
					ui->lineEdit_name->clear();
					return;
				}
			ui->listWidget_showAccount->show();
			ui->pushButton_signIn->show();
			ui->label->show();
			ui->pushButton_signIn->setEnabled(true);
			empty_User->Nameset(ui->lineEdit_name->text());
			QListWidgetItem* Item = new QListWidgetItem(ui->lineEdit_name->text());
			ui->listWidget_showAccount->addItem(Item);
			ui->listWidget_showAccount->setItemSelected(Item,true);

			ui->lineEdit_name->clear();
			++users_size;
			empty_User++;
			ui->label_2->hide();
			ui->lineEdit_name->hide();

		}

	}

}



//for(int last = 0;Allusers[last].Nameget() != "";++last)
//	QMessageBox::about(this,"",Allusers[last].Nameget());

void MainWindow::on_pushButton_start_clicked()
{
	this->hide();
	Soduko* w = new Soduko(this , ui->comboBox->currentText() );
	w->show();
}
