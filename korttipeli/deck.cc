
/********************************************************************
 * TIE-02200 Ohjelmoinnin peruskurssi, K2018                        *
 * Projekti 4: Korttipeli, pasianssi                                *
 * Nimi: Malin Kraft, opiskelijanumero: 232063                      *
 *                                                                  *
 * Tiedosto: deck.cc                                                *
 * Kuvaus: Tämä tiedosto sisältää korttipakan public ja private     *
 *         metodien määrittelyt                                     *
 * Kommentit:                                                       *
 *                                                                  *
 *                                                                  *
 ********************************************************************
 */


#include "deck.hh"

#include <algorithm>
#include <ctime>
#include <random>
#include <QDrag>
#include <QDragEnterEvent>
#include <QMimeData>
#include <QPainter>
#include <QLabel>


Deck::Deck(QWidget *parent) : QFrame(parent) {
    setMinimumSize(180, 260);
    setMaximumSize(180, 260);
    setFrameStyle(QFrame::Sunken | QFrame::StyledPanel);

    // luodaan pakka
    newDeck();
}


// Alustetaan uusi pakka
void Deck::newDeck() {
    // Tyhjennetään ensin cards_ -vektori
    cards_.empty();

    // Sitten lisätään kortit
    for (int suit = SPADE; suit != SUIT_COUNT; ++suit){

        for (unsigned value = 1; value <= 13; ++value){
            auto card = new Card(static_cast<CardSuit>(suit), value, this);
            int xOffset = (this->width() - card->width()) / 2;
            int yOffset = (this->height() - card->height()) / 2;
            card->move(xOffset, yOffset);
            cards_.push_back(card);
        }
    }
    // Sekoitetaan pakka
    shuffleDeck();
}


// Metodi jolla otetaan kortti pakasta
Card* Deck::pickCard() {
    if (cards_.empty()) {
        return nullptr;
    } else {
        Card* card = cards_.back();
        cards_.pop_back();
        return card;
    }
}


// Metodi joka sekoittaa pakan kortit
void Deck::shuffleDeck() {
    std::shuffle(cards_.begin(), cards_.end(),
                 std::default_random_engine(time(0)));
}


// Metodi joka lisää kortteja pakkaan. Käytetään kun pakka on tyhjentynyt ja
// kortit siirretään takaisin opendeckistä tähän pakkaan.
void Deck::addCard(Card *card) {
    card->setParent(this);
    card->show();
    cards_.push_back(card);
}


// Suoritetaan, kun pakkaa klikataan.
void Deck::mousePressEvent(QMouseEvent *event) {
    // Ohjelma ei saa kaatua tyhjän pakan klikkaukseen.
    if (cards_.empty()) {
        emit deckEmpty();
        event->accept();
        return;
    }

    // Otetaan osoittimen päähän pakan päällimmäinen kortti ja poistetaan se
    // pakasta.
    Card* card = cards_.back();
    cards_.pop_back();

    // Ohjelma ei saa kaatua, jos korttia ei olekaan.
    if (!card){
        return;
    }

    // Ilmoitetaan, että pakasta otettiin kortti.
    emit cardPicked(card);

    // Hyväksytään klikkaus, koska se käsitellään aina tässä metodissa.
    event->accept();
}
