#ifndef MAINWINDOW_HH
#define MAINWINDOW_HH

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
	Q_OBJECT
	
public:
	MainWindow(QWidget *parent = nullptr);
	~MainWindow();
	
private:
	void neuesRaetsel();
	int zufallszahl(int min, int max);
	int neuesRechenzeichen();
	
private slots:

	
	void on_pruefen_clicked();
	
	void on_aufloesen_clicked();
	
	void on_eingabe_returnPressed();
	
	void on_action0_bis_10_triggered();
	
	void on_action0_bis_20_triggered();
	
	void on_action0_bis_30_triggered();
	
	void on_actionPlus_triggered();
	
	void on_actionMinus_triggered();
	
	void on_actionMal_triggered();
	
	void on_actionDurch_triggered();
	
	void on_action_m10_bis_p10_triggered();
	
	void on_action_m20_bis_p20_triggered();
	
	void on_action_m30_bis_p30_triggered();
	
	void on_action_m100_bis_p100_triggered();
	
	void on_actionAufloesen_triggered();
	
private:
	Ui::MainWindow *ui;
	int kleinsteZahl = 0;
	int groessteZahl = 10;
	int z1;
	int z2;
	int ergebnis;
};
#endif // MAINWINDOW_HH
