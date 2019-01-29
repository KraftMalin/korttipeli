/********************************************************************
 * TIE-02200 Ohjelmoinnin peruskurssi, K2018                        *
 * Projekti 4: Korttipeli, pasianssi                                *
 * Nimi: Malin Kraft, opiskelijanumero: 232063                      *
 *                                                                  *
 * Tiedosto: mainwindow.cc                                          *
 * Kuvaus: Tämä tiedosto sisältää korttipelin käyttöikkunan         *
 *         komponenttien toiminnallisuudet                          *
 * Kommentit: Ylä ja alarivin CardSlotit on asetettu vectoriin,     *
 *         vaikka loppujenlopuksi niitä ei tarvittu sen kummemmin   *
 *         käsitellä.                                               *
 *                                                                  *
 ********************************************************************
 */


#include <iostream>
#include <QFrame>
#include <QGridLayout>
#include <QGroupBox>
#include <QHBoxLayout>

#include "mainwindow.hh"
#include "cardslot.hh"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
    endGameButton_("Quit", this)
{
    setSizePolicy(QSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed));
    setupLayout();
    connect(deck_, &Deck::cardPicked, pickedCards_, &OpenDeck::addCard);
    connect(deck_, &Deck::deckEmpty, this,
            &MainWindow::openDeckToClosedDeck);
    // Kun painetaan "Quit" buttonia niin suljetaan ikkuna.
    connect(&endGameButton_, SIGNAL(clicked(bool)), this, SLOT(close()));
}


MainWindow::~MainWindow() {
}


// Kun pakka on tyhjentynyt, niin opendeckistä siirretään kortit takaisin
// deck:iin jos tyhjää deckiä klikataan.
void MainWindow::openDeckToClosedDeck() {
    while (true) {
        Card* card = pickedCards_->pickTopCard();

        // Lopetusehto, eli kun opendeck_ on tyhjä, niin kortit on siirretty.
        if (card == nullptr) {
            break;
        }
        deck_->addCard(card);
        card->turn();
    }
}


void MainWindow::setupLayout() {
    // Pääikkunan isoimpana rakenteena on frame, joka sisältää...
    QFrame* frame = new QFrame;
    QVBoxLayout* frameLayout = new QVBoxLayout(frame);

    // ... alarivin ja ylärivin.
    QHBoxLayout* bottomRowLayout = new QHBoxLayout();
    QHBoxLayout* topRowLayout = new QHBoxLayout();
    frameLayout->addLayout(topRowLayout);
    frameLayout->addLayout(bottomRowLayout);

    // Luodaan pakkaoliot.
    deck_ = new Deck(this);
    pickedCards_ = new OpenDeck(this);

    // Luodaan myös GroupBox johon laitetaan nappuloita
    QGroupBox* pushButtons = new QGroupBox(this);
    QGridLayout* buttonLayout = new QGridLayout(pushButtons);
    // Lisätään pushButtoniin luotu Quit -button (Ajatus oli lisätä
    // useampi button tähän, kuten new game. Mutta en saanut new game
    // nappia toimimaan joten poistin sen. Mutta tästä syystä tein tällaisen
    // layoutin
    buttonLayout->addWidget(&endGameButton_,1,0,1,1);

    // Lisätään yläriville suljettu ja avoin pakka, sekä pushButtons
    topRowLayout->addWidget(deck_);
    topRowLayout->addWidget(pickedCards_);
    topRowLayout->addWidget(pushButtons);


    // Tehdään vecktori jossa on kaikki neljän maan tarkastusfunktiot sekä
    // funktio joka tarkistaa että onko samaa maata.
    std::vector<CheckFunction> checkers = { &GameRules::checkIfClub,
                                            &GameRules::checkIfDiamond,
                                            &GameRules::checkIfHeart,
                                            &GameRules::checkIfSpade,
                                            &GameRules::checkIfLegalMove };

    // Lisätään yläriville myös neljä cardslottia joihin voi laittaa vaan
    // tiettyä maata.
    for (std::vector<CheckFunction>::size_type i = 0; i < 4; ++i){
        CardSlot* slotNew = new CardSlot(checkers.at(i), this);

        topRowLayout->addWidget(slotNew);
        slotNew->setHiding();  // Alla olevat kortit ei jää näkyviin.
        topCardSlots_.push_back(slotNew);
    }

    // Tehdään alariville 7 korttipaikkaa
    for (unsigned int i = 0; i < 7; ++i) {
        CardSlot* slotBottom = new CardSlot(checkers.back(), this);

        bottomRowLayout->addWidget(slotBottom);
        bottomCardSlots_.push_back(slotBottom);
    }

    // Lisätään alaslotteihin oikeat määrät kortteja
    initBottomCardSlots();

    setCentralWidget(frame);
}


// Alustetaan kortit alaCardSloteihin pasianssiin soveltuvat määrät.
void MainWindow::initBottomCardSlots() {
    // Lisätään alarivin slotteihin kortteja pasianssiin soveltuvat määrät
    // sekä päällimmäiseksi yksi avoin kortti.
    for ( unsigned int i = 0; i < bottomCardSlots_.size(); ++i){
        for ( unsigned int j = 0; j < i; ++j) {
            Card* dealCard = deck_->pickCard();
            bottomCardSlots_.at(i)->addCard(dealCard);
        }
        Card* firstCard = deck_->pickCard();
        firstCard->turn();
        bottomCardSlots_.at(i)->addCard(firstCard);
    }
    std::cout << std::endl;
}






