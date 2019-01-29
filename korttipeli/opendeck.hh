/********************************************************************
 * TIE-02200 Ohjelmoinnin peruskurssi, K2018                        *
 * Projekti 4: Korttipeli, pasianssi                                *
 * Nimi: Malin Kraft, opiskelijanumero: 232063                      *
 *                                                                  *
 * Tiedosto: opendeck.hh                                            *
 * Kuvaus: Avoimen pakan luokkaesittely. Sisältää avoimen pakan     *
 *         kaikki toiminnallisuudet                                 *
 * Kommentit:                                                       *
 *                                                                  *
 *                                                                  *
 ********************************************************************
 */


#ifndef OPENDECK_HH
#define OPENDECK_HH
#include <QFrame>

QT_BEGIN_NAMESPACE
class QDragEnterEvent;
class QDropEvent;
QT_END_NAMESPACE

#include <QStackedLayout>

#include "card.hh"

class OpenDeck : public QFrame {

public:
    // Rakentaja ja metodi jolla voidaan poimia ylin kortti
    OpenDeck(QWidget* parent = 0);
    Card* pickTopCard();

    // Metodi jolla tyhjennetään opendeck_
    void emptyOpenDeck();

public slots:
    // Slot kortin lisäämistä opendeckiin varten.
    void addCard(Card* card);

protected:
    // ITse toteutetut Qt:n widgetin klikkaamiseen ja raahaamiseen liittyviä
    // metodeja
    void dragEnterEvent(QDragEnterEvent *event);
    void dragMoveEvent(QDragMoveEvent *event);
    void dropEvent(QDropEvent* event);
    void mousePressEvent(QMouseEvent *event);

private:
    // Layout joka sisältää avopakassa olevat korttiwidgetit.
    QStackedLayout* layout_;
};

#endif // OPENDECK_HH
