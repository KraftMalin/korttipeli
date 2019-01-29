/********************************************************************
 * TIE-02200 Ohjelmoinnin peruskurssi, K2018                        *
 * Projekti 4: Korttipeli, pasianssi                                *
 * Nimi: Malin Kraft, opiskelijanumero: 232063                      *
 *                                                                  *
 * Tiedosto: gamerules.hh                                           *
 * Kuvaus: Pelisääntö moduulin esittely. Sisältää pelisääntöjä      *
 *         pasianssia varten                                        *
 * Kommentteja:                                                     *
 *                                                                  *
 *                                                                  *
 ********************************************************************
 */



#ifndef GAMERULES_HH
#define GAMERULES_HH
#include "card.hh"
#include <string>

namespace GameRules {

    const unsigned int DECK_COUNT = 5;

    // Apufunktio joka tarkistaa onko sallittu siirto. Palauttaa true/false
    bool checkIfSuit(std::string bottom, std::string top, CardSuit suit);

    // Tarkastusfunktio, joka varmistaa, että päälle laitetaan vain tiettyä
    // maata, tarkistaa myös että numerojärjestys on sallittu, eli nouseva
    bool checkIfHeart(std::string bottom, std::string top);
    bool checkIfSpade(std::string bottom, std::string top);
    bool checkIfClub(std::string bottom, std::string top);
    bool checkIfDiamond(std::string bottom, std::string top);

    // Tarkastusfunktio joka asettaa alarivien cardsloteille pelisäännöt, jotka
    // pasianssiin kuuluu
    bool checkIfLegalMove(std::string bottom, std::string top);

}

#endif // GAMERULES_HH
