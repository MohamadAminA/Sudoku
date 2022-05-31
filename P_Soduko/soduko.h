#ifndef SODUKO_H
#define SODUKO_H
#include <QMainWindow>
#include "QMessageBox"
#include "QString"
#include "QTimer"
namespace Ui {
class Soduko;
}

class Soduko : public QMainWindow
{
	Q_OBJECT
public:
	explicit Soduko(QWidget *parent = nullptr,QString Level = "Easy",QString name = "",QString point = "");
	~Soduko();


private slots:
		void on_tableWidget_soduko_cellChanged(int row, int column);

		void on_pushButton_clicked();

		void Show_time();

private:
	int random_number(int min , int max);
	bool Check_value(int tool,int arz,QString data);
	Ui::Soduko *ui;
	QTimer* timer;
	QString Name_Player,Point_player;
	uint Ghalat = 0;
	int row_changed=-1,column_changed=-1;

protected:
	void resizeEvent(QResizeEvent* evt) override;

};

#endif // SODUKO_H
