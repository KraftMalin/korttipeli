/********************************************************************
 * TIE-02200 Ohjelmoinnin peruskurssi, K2018                        *
 * Projekti 4: Korttipeli, pasianssi                                *
 * Nimi: Malin Kraft, opiskelijanumero: 232063                      *
 *                                                                  *
 * Tieodsto: main.cc                                                *
 * Kuvaus: Ohjelman main tiedosto                                   *
 *                                                                  *
 * Kommentit:                                                       *
 *                                                                  *
 *                                                                  *
 ********************************************************************
 */


#include "mainwindow.hh"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
