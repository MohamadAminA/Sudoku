#ifndef SODUKO_H
#define SODUKO_H
#include <stdlib.h>
#include <time.h>
#include <QMainWindow>
#include "QMessageBox"
#include "QString"
namespace Ui {
class Soduko;
}

class Soduko : public QMainWindow
{
	Q_OBJECT

public:
	explicit Soduko(QWidget *parent = nullptr,QString Level = "Easy");
	~Soduko();
	int random_number(int min , int max);
private:
	Ui::Soduko *ui;
};

#endif // SODUKO_H
