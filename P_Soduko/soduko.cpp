#include "soduko.h"
#include "ui_soduko.h"
#include "QString"
Soduko::Soduko(QWidget *parent ,QString Level) :
	QMainWindow(parent),
	ui(new Ui::Soduko)
{
	ui->setupUi(this);
	srand( (unsigned)time(NULL));
	this->setCentralWidget(ui->tableWidget_soduko);
	int tedad_add = 0;
	if(Level=="Easy")
		tedad_add=27;
	else
		tedad_add=17;
	int tool,arz,value;
	for(int i=0;i<tedad_add;++i)
	{
		tool=random_number(1,9);
		arz=random_number(1,9);
		value=random_number(1,9);

	}
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

bool Check_value(int tool,int arz,int data){
	for(int i=0;i<9;++i){
	}
}
