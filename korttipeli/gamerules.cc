/********************************************************************
 * TIE-02200 Ohjelmoinnin peruskurssi, K2018                        *
 * Projekti 4: Korttipeli, pasianssi                                *
 * Nimi: Malin Kraft, opiskelijanumero: 232063                      *
 *                                                                  *
 * Tieodsto: gamerules.cc                                           *
 * Kuvaus: Tämä tieosto sisältää pelisääntöjen määrittelyt.         *
 *                                                                  *
 * Kommentit:                                                       *
 *                                                                  *
 *                                                                  *
 ********************************************************************
 */



#include "gamerules.hh"
#include "card.hh"

#include <iostream>

// Apufunktio kaikille checkIfXXX funktioille. Tarkistaa onko kortit tiettyä
// maata, sekä että järjestys on 1 -> 13
bool GameRules::checkIfSuit(std::string bottom, std::string top,
                            CardSuit suit) {
    // Otetaan selville bottom ja top korttien arvot.
    std::string bottomValue = bottom.substr(0, bottom.find_first_of(","));
    std::string topValue = top.substr(0, top.find_first_of(","));
    // Sekä päälle tulevan kortin maan.
    std::string suitString = top.substr(top.find_first_of(",")+1,1);

    // Tarkistetaan sallitut siirrot:
    // False jos maa on joku muu kuin sallittu
    // False jos korttia ei ole ja laitettavan kortin arvo on muu kuin 1
    // False jos laitettavan kortin arvo ei ole yhtä kuin alla olevan kortin
    // arvo plus 1.
    if (stoi(suitString) != suit) {
        return false;
    } else if (bottomValue == "" && topValue == "1") {
        return true;
    } else if (bottomValue != "" && stoi(topValue) == stoi(bottomValue) + 1) {
        return true;
    } else {
        return false;
    }

}


// Funktio saa parametrinaan alla olevan kortin ja päälle tulevan kortin
// tiedot merkkijonomuodossa.
bool GameRules::checkIfHeart(std::string bottom, std::string top) {
    if (checkIfSuit(bottom, top, HEART)) {
        return true;
    } else {
        return false;
    }

}

bool GameRules::checkIfSpade(std::string bottom, std::string top) {
    if (checkIfSuit(bottom, top, SPADE)) {
        return true;
    } else {
        return false;
    }
}


bool GameRules::checkIfClub(std::string bottom, std::string top) {
    if (checkIfSuit(bottom, top, CLUB)) {
        return true;
    } else {
        return false;
    }
}


bool GameRules::checkIfDiamond(std::string bottom, std::string top) {
    if (checkIfSuit(bottom, top, DIAMOND)) {
        return true;
    } else {
        return false;
    }
}


bool GameRules::checkIfLegalMove(std::string bottom, std::string top) {
    // Otetaan selville bottom ja top korttien arvot
    std::string bottomValue = bottom.substr(0, bottom.find_first_of(","));
    std::string topValue = top.substr(0, top.find_first_of(","));
    // sekä niiden maat
    std::string bottomSuit = bottom.substr(bottom.find_first_of(",")+1, 1);
    std::string topSuit = top.substr(top.find_first_of(",")+1, 1);

    // Tyhjään ruutuun saa laittaa minkä maan nr 13 tahansa
    if (bottomValue == "") {
        if (topValue != "13") {
            return false;
        }
        return true;
    // sitten tarkistetaan että onko muut siirrot sallittu vai ei.
    } else if (stoi(bottomValue) == stoi(topValue)+1) {
        if (stoi(topSuit) == HEART) {
            if (stoi(bottomSuit) == CLUB or stoi(bottomSuit) == SPADE) {
                return true;
            }
        } else if (stoi(topSuit) == SPADE) {
            if (stoi(bottomSuit) == HEART or stoi(bottomSuit) == DIAMOND) {
                return true;
            }
        } else if (stoi(topSuit) == CLUB) {
            if (stoi(bottomSuit) == HEART or stoi(bottomSuit) == DIAMOND) {
                return true;
            }
        } else if (stoi(topSuit) == DIAMOND) {
            if (stoi(bottomSuit) == SPADE or stoi(bottomSuit) == CLUB) {
                return true;
            }
        }
        return false;
    } else {
        return false;
    }
}


