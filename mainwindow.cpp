#include "mainwindow.hh"
#include "ui_mainwindow.h"

#include <QButtonGroup>
#include <QDateTime>
#include <stdlib.h>
#include <QtDebug>

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
	, ui(new Ui::MainWindow)
{
	ui->setupUi(this);
	srand(uint32_t(QDateTime::currentMSecsSinceEpoch()));
	neuesRaetsel();
	
	setWindowTitle("Rechentrainer für Kinder - V0.0.1");
	QActionGroup* ag_zahlenraum =  new QActionGroup(this);
	ag_zahlenraum->addAction(ui->action0_bis_10);
	ag_zahlenraum->addAction(ui->action0_bis_20);
	ag_zahlenraum->addAction(ui->action0_bis_30);
	ag_zahlenraum->addAction(ui->action0_bis_100);
	ag_zahlenraum->addAction(ui->action_m10_bis_p10);
	ag_zahlenraum->addAction(ui->action_m20_bis_p20);
	ag_zahlenraum->addAction(ui->action_m30_bis_p30);
	ag_zahlenraum->addAction(ui->action_m100_bis_p100);
	
	QActionGroup* ag_operation =  new QActionGroup(this);
	ag_operation->addAction(ui->actionPlus);
	ag_operation->addAction(ui->actionMinus);
	ag_operation->addAction(ui->actionMal);
	ag_operation->addAction(ui->actionDurch);
	ag_operation->setExclusive(false);
}

MainWindow::~MainWindow()
{
	delete ui;
}

void MainWindow::neuesRaetsel()
{
	int op;
	
	// temporäre zahlen, die auf eine tatsächlich neue Rechenaufgabe überprüft werden
	int z1 = 0;
	int z2 = 1;
	int ergebnis = 1;
	
	bool aufgabeNeu = false;
	
	while(!aufgabeNeu){
		do{
			op = zufallszahl(1,4);
			if(op == 1 && !ui->actionPlus->isChecked()){
				op = 0;
			}
			else if(op == 2 && !ui->actionMinus->isChecked()){
				op = 0;
			}
			else if(op == 3 && !ui->actionMal->isChecked()){
				op = 0;
			}
			else if(op == 4 && !ui->actionDurch->isChecked()){
				op = 0;
			}
		}while(op == 0);
		
		
		if(op == 1){
			do{
				ergebnis = zufallszahl(kleinsteZahl, groessteZahl);
				z1 = zufallszahl(kleinsteZahl, ergebnis);
				z2 = ergebnis-z1;
			} while (z2 < kleinsteZahl || z2 > groessteZahl);
			ui->rechenzeichen->setText("+");
		}
		else if(op == 2){
			do{
				ergebnis = zufallszahl(kleinsteZahl, groessteZahl);
				z1 = zufallszahl(ergebnis, groessteZahl);
				z2 = z1-ergebnis;
			} while (z2 < kleinsteZahl || z2 > groessteZahl);
			ui->rechenzeichen->setText("-");
		}
		else if(op == 3){
			do {
				if(kleinsteZahl >= -10){
					z1 = zufallszahl(kleinsteZahl, 10);
					z2 = zufallszahl(kleinsteZahl, 10);
				}else{
					z1 = zufallszahl(-10, 10);
					z2 = zufallszahl(-10, 10);
				}
				ergebnis = z1*z2;
			} while (ergebnis > groessteZahl || ergebnis < kleinsteZahl);
			ui->rechenzeichen->setText("×");
		}
		else if(op == 4){
			do {
				if(kleinsteZahl >= -10){
					ergebnis = zufallszahl(kleinsteZahl, 10);
					z2 = zufallszahl(kleinsteZahl, 10);
				}else{
					ergebnis = zufallszahl(-10, 10);
					z2 = zufallszahl(-10, 10);
				}
			} while (ergebnis*z2 > groessteZahl || ergebnis*z2 < kleinsteZahl || z2 == 0);
			z1 = ergebnis*z2;
			ui->rechenzeichen->setText(":");
		}else{
			qDebug() << "Fehler: keine Operation ausgewählt!";
		}
		
		if(z1 != this->z1 ||
				z2 != this->z2 ||
				ergebnis != this->ergebnis){
			aufgabeNeu = true;
			this->z1 = z1;
			this->z2 = z2;
			this->ergebnis = ergebnis;
		}
	}
	
	ui->zahl1->setText(QString().number(z1));
	ui->zahl2->setText(QString().number(z2));
	ui->eingabe->clear();
	ui->eingabe->setFocus();
}

int MainWindow::zufallszahl(int min, int max)
{
	int span = max - min + 1;
	if(span > 0){
		return rand()%span + min;
	}else{
		return min;
	}
}

void MainWindow::neuesRechenzeichen()
{
	neuesRaetsel();
}



void MainWindow::on_pruefen_clicked()
{
	if(ui->eingabe->text().toInt() == ergebnis){
		neuesRaetsel();
	}
	ui->eingabe->clear();
	ui->eingabe->setFocus();
}

void MainWindow::on_aufloesen_clicked()
{
    ui->eingabe->setText(QString().number(ergebnis));
	ui->eingabe->setFocus();
}

void MainWindow::on_eingabe_returnPressed()
{
	ui->pruefen->animateClick(200);
    on_pruefen_clicked();
}

void MainWindow::on_action0_bis_10_triggered()
{
    kleinsteZahl = 0;
	groessteZahl = 10;
	neuesRaetsel();
}

void MainWindow::on_action0_bis_20_triggered()
{
	kleinsteZahl = 0;
	groessteZahl = 20;
	neuesRaetsel();
}

void MainWindow::on_action0_bis_30_triggered()
{
	kleinsteZahl = 0;
	groessteZahl = 30;
	neuesRaetsel();
}

void MainWindow::on_actionPlus_triggered()
{
	if(ui->actionPlus->isChecked() == false &&
			ui->actionMinus->isChecked() == false &&
			ui->actionMal->isChecked() == false &&
			ui->actionDurch->isChecked() == false){
		ui->actionPlus->setChecked(true);
	}
    neuesRechenzeichen();
}

void MainWindow::on_actionMinus_triggered()
{
	if(ui->actionPlus->isChecked() == false &&
			ui->actionMinus->isChecked() == false &&
			ui->actionMal->isChecked() == false &&
			ui->actionDurch->isChecked() == false){
		ui->actionMinus->setChecked(true);
	}
    neuesRechenzeichen();
}

void MainWindow::on_actionMal_triggered()
{
	if(ui->actionPlus->isChecked() == false &&
			ui->actionMinus->isChecked() == false &&
			ui->actionMal->isChecked() == false &&
			ui->actionDurch->isChecked() == false){
		ui->actionMal->setChecked(true);
	}
    neuesRechenzeichen();
}

void MainWindow::on_actionDurch_triggered()
{
	if(ui->actionPlus->isChecked() == false &&
			ui->actionMinus->isChecked() == false &&
			ui->actionMal->isChecked() == false &&
			ui->actionDurch->isChecked() == false){
		ui->actionDurch->setChecked(true);
	}
    neuesRechenzeichen();
}

void MainWindow::on_action_m10_bis_p10_triggered()
{
    kleinsteZahl = -10;
	groessteZahl = 10;
	neuesRaetsel();
}

void MainWindow::on_action_m20_bis_p20_triggered()
{
	kleinsteZahl = -20;
	groessteZahl = 20;
	neuesRaetsel();
}

void MainWindow::on_action_m30_bis_p30_triggered()
{
    kleinsteZahl = -30;
	groessteZahl = 30;
	neuesRaetsel();
}

void MainWindow::on_action_m100_bis_p100_triggered()
{
    kleinsteZahl = -100;
	groessteZahl = 100;
	neuesRaetsel();
}

void MainWindow::on_actionAufloesen_triggered()
{
	ui->aufloesen->animateClick(200);
    on_aufloesen_clicked();
}

void MainWindow::on_action0_bis_100_triggered()
{
	kleinsteZahl = 0;
	groessteZahl = 100;
	neuesRaetsel();
}
