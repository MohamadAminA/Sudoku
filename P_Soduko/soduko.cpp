#include "soduko.h"
#include "time.h"
#include "stdlib.h"
#include "ui_soduko.h"
#include "QString"
#include "QDebug"
#include "QTableWidget"
#include <QFile>
#include <QTextStream>
#include "QTimer"
#include "QTime"

void Soduko::Show_time()
{
	ui->labe_time->setText(QTime::currentTime().toString("hh:mm:ss"));
}

Soduko::Soduko(QWidget *parent ,QString Level,QString name,QString point) :
	QMainWindow(parent),
	ui(new Ui::Soduko)
{
	ui->setupUi(this);
	srand( (unsigned)time(NULL));
	Name_Player = name;
	Point_player = point;
	int tedad_add = 0;

	if(Level=="Easy")
		tedad_add=30;
	else
		tedad_add=20;
	int tool,arz,value;
	int index[9][9],tekrar = 0;
	for(int h=0 ; h<9; h++)
		for(int l=0 ; l<9; l++)
			index[h][l] = 0;

	for(int i=0;i<tedad_add;++i)
	{
		tekrar = 0;
		tool=random_number(0,8);
		arz=random_number(0,8);
		value=random_number(1,9);
		for(int j=0 ; j<9 ; j++)
			if(index[tool][j]==value)
				++tekrar;
		for(int k=0 ; k<9 ; k++)
			if(index[k][arz]==value)
				++tekrar;
		for(int h=(tool/3)*3 ; h<((tool/3)*3)+3 ; h++)
			for(int l=(arz/3)*3 ; l<((arz/3)*3)+3; l++)
				if(index[h][l]==value)
					++tekrar;
		if(tekrar == 0){
			index[tool][arz]=value;
			row_changed = tool;
			column_changed = arz;
			QTableWidgetItem* new_item = new QTableWidgetItem(QString::number(value));
			ui->tableWidget_soduko->setItem(tool,arz,new_item);
			ui->tableWidget_soduko->item(tool,arz)->setBackground(Qt::gray);
			new_item->setFlags(new_item->flags() ^ Qt::ItemIsEditable);
			}
		else
			++tedad_add;
	}
	timer = new QTimer(this);
	connect(timer,SIGNAL(timeout()) , this, SLOT(Show_time()))	;
	timer->start(1000);
}


Soduko::~Soduko()
{
	delete ui;
}

int Soduko::random_number(int min, int max)
{
	int randNum = rand()%(max-min + 1) + min;
	return randNum;
}

bool Soduko::Check_value(int tool,int arz,QString data){
	QTableWidgetItem* current_item ;
	int tekrar_add=0;
	for(int i=0;i<9;++i){
		current_item = ui->tableWidget_soduko->item(i,arz);
		if(current_item == nullptr)
			continue;
		if(QString::compare( current_item->text() , data) == 0)
			tekrar_add++;
	}
	for(int i=0;i<9;++i){
		current_item = ui->tableWidget_soduko->item(tool,i);
		if(current_item == nullptr)
			continue;
		if(	QString::compare( current_item->text() , data) == 0)
			tekrar_add++;
	}
	int limit_tool = (tool/3)*3,limit_arz= (arz/3)*3;
	for(int i=limit_tool;i<limit_tool+3;i++)
		for(int j=limit_arz;j<limit_arz+3;++j){
			current_item = ui->tableWidget_soduko->item(i,j);
			if(current_item == nullptr)
				continue;
			if(QString::compare( current_item->text() , data) == 0)
				++tekrar_add;
		}

	if(tekrar_add>3)
		return false;
	return true;
}


void Soduko::on_tableWidget_soduko_cellChanged(int row, int column)
{
	if(row == row_changed && column == column_changed)
		return;
	QTableWidgetItem* Current = ui->tableWidget_soduko->item(row,column);
	if(Current == nullptr){
		ui->tableWidget_soduko->item(row,column)->setBackground(Qt::white);
		return;
	}
	if(Current->text().isEmpty()){
		if(ui->tableWidget_soduko->item(row,column)->background() == Qt::red);
			--Ghalat;
		ui->tableWidget_soduko->item(row,column)->setBackground(Qt::white);
		return;
	}
	bool empty_number = true;
	Current->text().toInt(&empty_number);
	if(Current->text().toInt()>9||Current->text().toInt()< 1||empty_number == false)
	{
		Current->setText("");
	}

	if(!Check_value(row,column,Current->text()))
	{
		//ui->tableWidget_soduko->setItem(row,column, new QTableWidgetItem(Current->text()));
		if(!(ui->tableWidget_soduko->item(row,column)->background() == Qt::red));
			++Ghalat;
		ui->tableWidget_soduko->item(row,column)->setBackground(Qt::red);
	}
	else
	{
		if(ui->tableWidget_soduko->item(row,column)->background() == Qt::red);
			--Ghalat;
		ui->tableWidget_soduko->item(row,column)->setBackground(Qt::white);
	}
}

void Soduko::on_pushButton_clicked()
{
	QTableWidgetItem* item;
	for(int i=0;i<9;++i){
		for(int j=0;j<9;++j){
			item = ui->tableWidget_soduko->item(i,j);
			if(item == nullptr || !Check_value(i,j,item->text()))
			{
				QMessageBox::critical(this,"Sudoku","Sudoku still not finished ! ");
				return;
			}
		}
	}
	QMessageBox::information(this,"Sudoku","congratulations you Finished the Sudoku","Exit");
	int point = Point_player.toInt();
	++point;
	QFile file ("Points.txt");
	if(!file.open(QFile::Append | QFile::Text)){
		QMessageBox::warning(this,"ERROR","404\n\tFile not created");
		return;
}
	QTextStream out (&file);
	out << Name_Player+" : "+QString::number(point) + " | ";
	file.flush();
	file.close();
	QApplication::quit();
}

//تنظیم بکگراند به صورت تغییر پذیر
void Soduko::resizeEvent(QResizeEvent* evt)
{
	QPixmap bkgnd("C:/Projects/ProjectC++/P_Soduko/mini-project-2-sudoku-MohamadAminA/P_Soduko/img/Background/Background.png");
	bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);

	QPalette palette;

	palette.setBrush(QPalette::Background, bkgnd);
	this->setPalette(palette);

	QMainWindow::resizeEvent(evt); // call inherited implementation
}
