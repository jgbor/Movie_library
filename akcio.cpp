//
// Created by Gabo on 2021.04.19..
//

#include "akcio.h"
#include "memtrace.h"

///Akcio oszt�ly
//korhatar el�r�s�re f�ggv�ny
int Akcio::getKorhatar() const {
    return korhatar;
}

//adatokat ki�r� f�ggv�ny
void Akcio::kiir() const{
    std::cout << getCim() << std::endl << getKategoria() << "film, " << getEv() << ", " << getHossz() << " perc"
              << std::endl << "Korhatar: " << korhatar << std::endl << "Rendezte: " << getRendezo() << std::endl;
}

//destruktor
Akcio::~Akcio(){}

//a film adatainak ki�r�sa egy f�jlba
void Akcio::fajlba(std::ofstream& out) const {
    out << getKategoria() << std::endl << getCim() << std::endl << getRendezo() << std::endl << getEv()
        << std::endl << getHossz() << std::endl << korhatar << std::endl;
}