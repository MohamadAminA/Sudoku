#include "soduko.h"
#include "time.h"
#include "stdlib.h"
#include "ui_soduko.h"
#include "QString"
#include "QDebug"
#include "QTableWidget"
Soduko::Soduko(QWidget *parent ,QString Level) :
	QMainWindow(parent),
	ui(new Ui::Soduko)
{
	ui->setupUi(this);
	srand( (unsigned)time(NULL));
	int tedad_add = 0;

	if(Level=="Easy")
		tedad_add=30;
	else
		tedad_add=20;
	int tool,arz,value;

	for(int i=0;i<tedad_add;++i)
	{
		tool=random_number(0,8);
		arz=random_number(0,8);
		value=random_number(1,9);
		ch_column = arz;
		ch_row = tool;
		QTableWidgetItem* new_item = new QTableWidgetItem(QString::number(value));
		if(Check_value(tool,arz,value)&&ui->tableWidget_soduko->item(tool,arz) == nullptr){
			ui->tableWidget_soduko->setItem(tool,arz,new_item);
			new_item->setFlags(new_item->flags() ^ Qt::ItemIsEditable);
		}
		else
			++tedad_add;
	}
	ch_column = -1;
	ch_row = -1;

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

bool Soduko::Check_value(int tool,int arz,int data){
	QTableWidgetItem* current_item ;
	int tekrar_add=0;
	for(int i=0;i<9;++i){
		current_item = ui->tableWidget_soduko->item(i,arz);
		if(current_item == nullptr)
			continue;
		if(current_item->text().toInt() == data)
			tekrar_add++;
	}
	for(int i=0;i<9;++i){
		current_item = ui->tableWidget_soduko->item(tool,i);
		if(current_item == nullptr)
			continue;
		if(	current_item->text().toInt()==data)
			tekrar_add++;
	}
	int limit_tool = (tool%3)*3,limit_arz= (arz%3)*3;
	for(int i=limit_tool;i<limit_tool+3;i++)
		for(int j=limit_arz;j<limit_arz+3;++j){
			current_item = ui->tableWidget_soduko->item(i,j);
			if(current_item == nullptr)
				continue;
			if(current_item->text().toInt()==data)
				++tekrar_add;
		}

	if(tekrar_add>=3)
		return false;
	return true;
}


void Soduko::on_tableWidget_soduko_cellChanged(int row, int column)
{
	if(row == ch_row&&column == ch_column)
		return;
	QTableWidgetItem* Current = ui->tableWidget_soduko->item(row,column);
	if(Current == nullptr){
		ui->tableWidget_soduko->item(row,column)->setBackground(Qt::white);
		return;
	}
	//if(Current->flags() == Qt::ItemIsEditable)
	if(!(Current->text() == '1'||Current->text() == '2'||Current->text() == '3'||Current->text() == '4'||Current->text() == '5'||Current->text() == '6'||Current->text() == '7'||Current->text() == '8'||Current->text() == '9'))
	{
		Current->text().clear();
	}

	if(!Check_value(row,column,Current->text().toInt()))
	{
		//ui->tableWidget_soduko->setItem(row,column, new QTableWidgetItem(Current->text()));
		ui->tableWidget_soduko->item(row,column)->setBackground(Qt::red);
	}
	else
	{
		ui->tableWidget_soduko->item(row,column)->setBackground(Qt::white);
	}
}

void Soduko::on_pushButton_clicked()
{
	QTableWidgetItem* item;
	for(int i=0;i<9;++i){
		for(int j=0;j<9;++j){
			item = ui->tableWidget_soduko->item(i,j);
			if(item == nullptr || !Check_value(i,j,item->text().toInt()))
			{
				QMessageBox::critical(this,"Sudoku","Sudoku still not finished ! ");
				return;
			}
		}
	}
	QMessageBox::information(this,"Sudoku","congratulations you Finished the Sudoku","Exit");
	QApplication::quit();
}
