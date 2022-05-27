#ifndef SODUKO_H
#define SODUKO_H
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


private slots:
		void on_tableWidget_soduko_cellChanged(int row, int column);

		void on_pushButton_clicked();

private:
	int random_number(int min , int max);
	bool Check_value(int tool,int arz,int data);
	Ui::Soduko *ui;
	QTimer* timer;
	int ch_row,ch_column;
};

#endif // SODUKO_H
