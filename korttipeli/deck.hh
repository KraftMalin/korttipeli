/********************************************************************
 * TIE-02200 Ohjelmoinnin peruskurssi, K2018                        *
 * Projekti 4: Korttipeli, pasianssi                                *
 * Nimi: Malin Kraft, opiskelijanumero: 232063                      *
 *                                                                  *
 * Tiedosto: deck.hh                                                *
 * Kuvaus: Korttipakkaluokan määrittely. Sisältää korttipakan       *
 *         metodit ja muita toiminnallisuuksia                      *
 * Kommentteja:                                                     *
 *                                                                  *
 *                                                                  *
 ********************************************************************
 */


#ifndef DECK_HH
#define DECK_HH

#include <vector>
#include <QFrame>
#include "card.hh"

class Deck : public QFrame
{
    Q_OBJECT

public:
    Deck(QWidget *parent = 0);

    // Alustetaan uusi pakka
    void newDeck();

    // Korttipakasta voi nostaa päällimmäisen kortin.
    Card* pickCard();

    // Sekoittaa korttipakan
    void shuffleDeck();

    // Lisää kortin pakkaan
    void addCard(Card* card);

signals:
    // Signaali, jonka pakka lähettää, kun kortti nostetaan.
    void cardPicked(Card* card);

    // Signaali joka huomaa että korttipakka on tyhjä
    void deckEmpty();

protected:
    // Itse toteutettu Qt:n widgetin klikkaamiseen liittyvä metodi.
    void mousePressEvent(QMouseEvent *event);

private:
    // Korttipakan sisältämät kortit.
    std::vector<Card*> cards_;
};

#endif // DECK_HH
