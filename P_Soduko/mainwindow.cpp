#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QMessageBox"
#include "soduko.h"
#include <QTextStream>
#include <QFile>

class User
{
public:

	QString Nameget(){
		return this->Name;
	}
	void Nameset(QString new_name){
		Name = new_name;
	}
	QString point_get(){
		return this->point;
	}
	void point_set(QString new_point){
		point = new_point;
	}
private:
	QString Name;
	QString point;

};

User Allusers [50];
int Users_count = 0;
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
	QFile file ("Points.txt");
	if(file.open(QFile::ReadOnly|QFile::Text))
	{
		QTextStream in(&file);
		QString file_Text = in.readAll();
		QStringList Text_spl = file_Text.split('|');
		QStringList Text_spl_sec;
		for (int i = 0; i < Text_spl.count()-1 ; ++i) {
			QString temp = Text_spl[i];
			Users_count++;
			Text_spl_sec.append(temp.split(':'));
		}
		for(int i=0 ; i<Text_spl_sec.count();i = i+2){
			Allusers[i/2].Nameset(Text_spl_sec[i]);
			Allusers[i/2].point_set(Text_spl_sec[i+1]);
			ui->listWidget_showAccount->addItem(Text_spl_sec[i]);
			ui->listWidget_point->addItem(Text_spl_sec[i+1]);
		}
	}
}


MainWindow::~MainWindow()
{
	delete ui;
}


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

	for(int i=0; i<Users_count;++i)
		if(QString::compare(ui->listWidget_showAccount->currentItem()->text(),Allusers[i].Nameget()) == 0){
			Name_Player = Allusers[i].Nameget();

			QMessageBox::information(this,"Login","Wellcome to Soduko\n"+Allusers[i].Nameget(),QMessageBox::Ok);
			//----------------------ورود به قسمت بازی سودوکو
			ui->label->hide();
			ui->label_2->hide();
			ui->listWidget_showAccount->hide();
			ui->listWidget_point->hide();
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
		ui->listWidget_point->hide();
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
			ui->listWidget_point->show();
			ui->pushButton_signIn->show();
			ui->label->show();
			Allusers[Users_count].Nameset(ui->lineEdit_name->text());
			Allusers[Users_count].point_set("0");
			Users_count++;

			QListWidgetItem* Item = new QListWidgetItem(ui->lineEdit_name->text());
			QListWidgetItem* item_point = new QListWidgetItem("0");
			ui->listWidget_showAccount->addItem(Item);
			ui->listWidget_point->addItem(item_point);
			ui->lineEdit_name->clear();
			ui->label_2->hide();
			ui->lineEdit_name->hide();
		}
	}
}

//for(int last = 0;Allusers[last].Nameget() != "";++last)
//	QMessageBox::about(this,"",Allusers[last].Nameget());

void MainWindow::on_pushButton_start_clicked()
{
	QFile file ("Points.txt");
	if(!file.open(QFile::WriteOnly | QFile::Text)){
		QMessageBox::warning(this,"ERROR","404\n\tFile not created");
		return;
	}
	QTextStream out (&file);
	for(int i = 0;i < Users_count ;++i){
		QString temp = Allusers[i].Nameget()+" : "+ Allusers[i].point_get() + " | ";
		out << temp;
	}

	file.flush();
	file.close();
	Soduko* w = new Soduko(this , ui->comboBox->currentText(),Name_Player,Point_Player);
	w->show();
	this->hide();
}
