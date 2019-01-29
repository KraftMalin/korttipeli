/********************************************************************
 * TIE-02200 Ohjelmoinnin peruskurssi, K2018                        *
 * Projekti 4: Korttipeli, pasianssi                                *
 * Nimi: Malin Kraft, opiskelijanumero: 232063                      *
 *                                                                  *
 * Tiedosto: mainwindow.hh                                          *
 * Kuvaus: Käyttöikkunaluokka, sisältää käyttöikkunan kaikki        *
 *         tarvittavat toiminnallisuudet                            *
 * Kommentteja:                                                     *
 *                                                                  *
 *                                                                  *
 ********************************************************************
 */


#ifndef MAINWINDOW_HH
#define MAINWINDOW_HH

#include <QMainWindow>
#include <QPushButton>
#include <vector>
#include "cardslot.hh"
#include "deck.hh"
#include "opendeck.hh"
#include "gamerules.hh"


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    // Kun pakka on tyhjentynyt niin siirretään opendeckissä olevat kortit
    // takaisin pakkaan.
    void openDeckToClosedDeck();

private:
    void setupLayout();

    // alustetaan alaCardSlotteihin kortit
    void initBottomCardSlots();

    // Talletetaan attribuuteiksi ne widgetit, joita saattaa tarvita käsitellä
    // pelin aikana.
    Deck* deck_;
    OpenDeck* pickedCards_;
    std::vector<CardSlot*> topCardSlots_;
    std::vector<CardSlot*> bottomCardSlots_;

    // Button for ending the game
    QPushButton endGameButton_;
};

#endif // MAINWINDOW_HH
