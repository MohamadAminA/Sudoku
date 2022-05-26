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

public slots:

private slots:
	void on_pushButton_signIn_clicked();

	void on_pushButton_newAccount_clicked();

private:
	Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
