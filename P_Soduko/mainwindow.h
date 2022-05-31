#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
	Q_OBJECT

protected:
	void resizeEvent(QResizeEvent* evt) override;

public:
	explicit MainWindow(QWidget *parent = nullptr);
	~MainWindow();

	class User;

public slots:

private slots:
	void on_pushButton_signIn_clicked();

	void on_pushButton_newAccount_clicked();

	void on_pushButton_start_clicked();

private:
	Ui::MainWindow *ui;
	QString Name_Player,Point_Player = 0;
	int Users_count = 0;
};

#endif // MAINWINDOW_H
