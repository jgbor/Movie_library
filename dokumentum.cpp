//
// Created by Gabo on 2021.04.19..
//

#include "dokumentum.h"
#include "memtrace.h"

///Dokumentum oszt�ly
//korhatar el�r�s�re f�ggv�ny
String Dokumentum::getLeiras() const{
    return leiras;
}

//adatokat ki�r� f�ggv�ny
void Dokumentum::kiir() const{
    std::cout << getCim() << std::endl << getKategoria() << "film, " << getEv() << ", " << getHossz() << " perc"
              << std::endl << "Rendezte: " << getRendezo() << std::endl << "Leiras: " << getLeiras() << std::endl;
}

//destruktor
Dokumentum::~Dokumentum(){}


//a film adatainak ki�r�sa egy f�jlba
void Dokumentum::fajlba(std::ofstream &out) const{
    out << getKategoria() << std::endl << getCim() << std::endl << getRendezo() << std::endl << getEv()
        << std::endl << getHossz() << std::endl << leiras << std::endl;
}