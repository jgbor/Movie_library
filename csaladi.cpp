//
// Created by Gabo on 2021.04.19..
//

#include "csaladi.h"
#include "memtrace.h"

///Csaladi oszt�ly
//korhatar el�r�s�re f�ggv�ny
int Csaladi::getKorhatar() const{
    return korhatar;
}

//adatokat ki�r� f�ggv�ny
void Csaladi::kiir() const{
    std::cout << getCim() << std::endl << getKategoria() << " film, " << getEv() << ", " << getHossz() << " perc"
              << std::endl << "Korhatar: " << korhatar << std::endl << "Rendezte: " << getRendezo() << std::endl;
}

//destruktor
Csaladi::~Csaladi(){}


//a film adatainak ki�r�sa egy f�jlba
void Csaladi::fajlba(std::ofstream &out) const{
    out << getKategoria() << std::endl << getCim() << std::endl << getRendezo() << std::endl << getEv()
        << std::endl << getHossz() << std::endl << korhatar << std::endl;
}