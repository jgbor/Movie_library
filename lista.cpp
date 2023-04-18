//
// Created by Gabo on 2021.04.16..
//

#include "lista.h"
#include "memtrace.h"
#include <iostream>
#include <stdexcept>
#include <cstring>

#ifdef CPORTA //Jportára kell, mert az strlwr függvény csak Windowson mûködik
char *strlwr(char *str){
  unsigned char *p = (unsigned char *)str;
  while (*p) {
     *p = tolower((unsigned char)*p);
      p++;
  }
  return str;
}
#endif

int Lista::fajtadb=3;

///Lista osztály függvényei
///privát függvények
//megmondja, hogy egy konkrét film benne van-e a listában
bool Lista::bennevan(Film* f) const{
    if (f == nullptr){
        return false;
    }else {
        for (Listaelem* mozgo=elso;mozgo!= nullptr;mozgo=mozgo->kov){
            //ha megtaláltuk a filmet, azonnal visszatérünk igazzal
            if (*(mozgo->adat)==*f){
                return true;
            }
        }
        //ha végigér a listán a ciklus, az azt jelenti, hogy nem volt benne
        return false;
    }
}

//megmondja a kapott Stringrõl a fajtak tömbben  tartozik
int Lista::milyenfajta(String& kat) const{
    for (int i=0;i<fajtadb;i++){
        //ha megtaláljuk visszatérünk az indexszel
        if (kat==fajtak[i]){
            return i;
        }
    }
    //ha nincs benne error-t dobunk
    throw std::invalid_argument("Nincs ilyen kategoria");
}

//bekéri egy film adatait
Film* Lista::filmbeker() const{
    //bekérjük a közös adatokat
    std::cout << "Add meg a film cimet!" << std::endl;
    String Cim;
    std::cin >> Cim;
    std::cout << "Add meg a film rendezojet!" << std::endl;
    String Ren;
    std::cin >> Ren;
    std::cout << "Add meg a film kiadasanak evet!" << std::endl;
    int Ev=0;
    std::cin >> Ev;
    if (std::cin.fail()){ //ha hiba lenne szám beolvasásánál
        std::cin.clear();
        throw std::invalid_argument("Nem szamot adsz meg!");
    }
    std::cout << "Add meg a film hosszat percben!" << std::endl;
    int Hossz=0;
    std::cin >> Hossz;
    if (std::cin.fail()){ //ha hiba lenne szám beolvasásánál
        std::cin.clear();
        throw std::invalid_argument("Nem szamot adsz meg!");
    }
    std::cout << "Add meg a film kategoriajat!" << std::endl;
    String Kat;
    std::cin >> Kat;
    int fajta;
    try {
        fajta = milyenfajta(Kat);
    }catch (std::invalid_argument& error){ //ha rossz lenne a fajta, továbbdobjuk a kapott kivételt
        throw error;
    }
    //a fajta alapján további dolgokat kérünk be
    switch (fajta) {
        case 0: { //családi film
            std::cout << "Add meg a film korhatarat!" << std::endl;
            int Kh=0;
            std::cin >> Kh;
            if (std::cin.fail()){ //ha hiba lenne szám beolvasásánál
                std::cin.clear();
                throw std::invalid_argument("Nem szamot adsz meg!");
            }
            Csaladi* f= new Csaladi(Cim,Ren,Hossz,Ev,Kh);
            return f;
        }
        case 1: { //akciófilm
            std::cout << "Add meg a film korhatarat!" << std::endl;
            int Kh=0;
            std::cin >> Kh;
            if (std::cin.fail()){ //ha hiba lenne szám beolvasásánál
                std::cin.clear();
                throw std::invalid_argument("Nem szamot adsz meg!");
            }
            Akcio* f= new Akcio(Cim,Ren,Hossz,Ev,Kh);
            return f;
        }
        case 2: { //dokumentumfilm
            std::cout << "Add meg a film leirasat!" << std::endl;
            String Leir;
            std::cin >> Leir;
            Dokumentum *f= new Dokumentum(Cim,Ren,Hossz,Ev,Leir);
            return f;
        }
        default:
            return nullptr;
    }
}

//egy filmet a listába helyez
void Lista::belerak(Film*& f){
    Listaelem* uj = new Listaelem;
    uj->adat=f;
    uj->kov= nullptr;
    if (!bennevan(f)){
        uj->kov=elso;
        elso=uj;
    }else{
        //ha benne lenne, töröljük az új elemet és kivételt dobunk
        delete uj->adat;
        delete uj;
        throw std::logic_error("Mar benne volt ez a film az adatbazisban.");
    }
}

///publikus függvények

//fájlból megalkotja a a listát
void Lista::fajlbeolvas(){
    std::ifstream fajl("filmek.txt");
    if (!fajl.is_open()){
        std::cout << "Nincs adatfajl" << std::endl;
        return;
    }
    String Kat;
    while(fajl >> Kat) {
        String Cim;
        String Ren;
        int Ev;
        int Hossz;
        Film *film = nullptr;
        //egy film beolvasása a fájlból
        int fajta;
        try {
           fajta = milyenfajta(Kat);
        }
        //ha nem megfelelõ befejezzük a beolvasást
        catch (std::invalid_argument& str){
            std::cout << "Nem sikerult minden adatot beolvasni" << std::endl;
            return;
        }
        fajl >> Cim;
        fajl >> Ren;
        fajl >> Ev;
        fajl >> Hossz;
        switch (fajta) {
            case 0: {  //családi film
                int Kh = 0;
                fajl >> Kh;
                Csaladi *cs = new Csaladi(Cim, Ren, Hossz, Ev, Kh);
                film = cs;
                break;
            }
            case 1: { //akciófilm
                int Kh = 0;
                fajl >> Kh;
                Akcio *ak = new Akcio(Cim, Ren, Hossz, Ev, Kh);
                film = ak;
                break;
            }
            case 2: { //dokumentumfilm
                String Leir;
                fajl >> Leir;
                Dokumentum *dok = new Dokumentum(Cim, Ren, Hossz, Ev, Leir);
                film = dok;
                break;
            }
            default:
                break;
        }
        //Film beolvasásának a vége, listába helyezés
        try {
            belerak(film);
        }catch(std::logic_error&){} //ha többször lenne a fájlban akkor szimplán nem rakjuk bele a listába
    }
    fajl.close();
}

//a listát fájlba kiíró függvény
void Lista::fajlkiir(){
    std::ofstream fajl("filmek.txt");
    if (!fajl.is_open()){
        std::cout << "Nem lehet menteni az adatokat";
        return;
    }
    //minden elemre meghívjuk a fájlba kiíró függvényt
    for(Listaelem* mozgo=elso;mozgo!= nullptr;mozgo=mozgo->kov){
        mozgo->adat->fajlba(fajl);
    }
    fajl.close();
}

//teljes listát kiíró függvény
void Lista::kiir() const{
    if (elso== nullptr){ //ha nincs adat jelezzük a felhasználónak
        std::cout << "NINCS ADAT" << std::endl;
    }else {
        std::cout << "OSSZES FILM:" << std::endl << std::endl;
        //minden elemre meghívjuk a képernyõre író függvényét
        for (Listaelem *mozgo = elso; mozgo != nullptr; mozgo = mozgo->kov) {
            mozgo->adat->kiir();
            std::cout << std::endl;
        }
    }
}

//elsõ elemre mutató pointert visszaadó függvény
Listaelem* Lista::getElso() const{
    return elso;
}

//a felhasználó új elemet adhat a listához
void Lista::hozzaad(){
    std::cout << "FILM FELVETELE" << std::endl << std::endl;
    Film* f;
    try {
        f = filmbeker();
    }catch (std::invalid_argument& error){ //ha rossz típust adott meg a felhasználó, akkor nem tesszük a listába
        std::cout << error.what() << std::endl;
        return;
    }
    try {
        belerak(f);
        std::cout << "Film hozzaadva az adatbazishoz" << std::endl;
    }catch(std::logic_error& error){ //ha már benne lett volna, jelezzük a felhasználónak
        std::cout << error.what() << std::endl;
    }
}

//a felhasználó törölhet elemet a listából
void Lista::torol(){
    std::cout << "FILM TORLESE" << std::endl << std::endl;
    Film* f;
    try {
        f = filmbeker();
    }catch (std::invalid_argument& error){ //hibás kategória esetén jelezzük a felhasználónak ezt
        std::cout << error.what() << std::endl;
        return;
    }
    if (!bennevan(f)){
        std::cout << "Nem volt ilyen film az adatbazisban." << std::endl;
    }else{
        Listaelem** elozo=&elso;
        for (Listaelem* ezt=elso;ezt!= nullptr;ezt=ezt->kov){ //befutjuk a listát az elem megtalálásához
            if (*(ezt->adat)==*f){                            //ha megtaláljuk a filmet, töröljük, és leállítjuk a ciklust
                *elozo=ezt->kov;
                delete ezt->adat;
                delete ezt;
                std::cout << "Sikeres torles!" << std::endl;
                break;
            }
            elozo=&ezt->kov;
        }
    }
    delete f;
}

//a felhasználó szûrheti az adatbázisban lévõ filmeket
void Lista::szures(bool* opciok){
    int parancs;
    bool jo=false;
    Lista szukitett;
    while (!jo) { //amíg nem érvényes adatot ad meg a felhasználó
        std::cout << "SZURES" << std::endl << "0: Vissza (eredmeny kiirasa)" << std::endl << "1: Kategoria" << std::endl <<
                  "2: Ev" << std::endl << "3: Hossz" << std::endl << "4: Rendezo" << std::endl << "5: Korhatar" << std::endl <<
                  "6: Cim" << std::endl << "Hogy szeretnel keresni?" << std::endl;
        std::cin >> parancs;
        if (std::cin.fail()){ //ha hiba lenne szám beolvasásánál
            std::cin.clear();
            std::cin.ignore(10000,'\n');
            std::cout << "Nem szamot adsz meg!" << std::endl;
            parancs=-1;
        }
        jo = parancs >= 0 && parancs <= 6;
        if (jo && parancs!=0 && !opciok[parancs-1]){ //ha már ez alapján szûrve volt a lista, nem engedjük újra
            std::cout << "Mar szurve van a lista ez alapjan. ";
            parancs=-1;
            jo=false;
        }
        switch (parancs) {
            case 0: //vissza és kiír
                kiir();
                return;
            case 1: {  //kategória szerint
                std::cout << std::endl << "Milyen kategoriat szeretnel?" << std::endl;
                String keres;
                std::cin >> keres;
                opciok[parancs-1]=false;
                for (Listaelem* mozgo=elso;mozgo!= nullptr;mozgo=mozgo->kov){
                    if (strstr(strlwr(mozgo->adat->getKategoria()),strlwr(keres))!= nullptr){
                        try {
                            Film* f=mozgo->adat->clone(); //az új listába másoljuk, ha megfelel a feltételnek
                            szukitett.belerak(f);
                        }catch(std::logic_error& error){}
                    }
                }
                break;
            }
            case 2: { //év szerint
                std::cout << std::endl << "Melyik evbol szeretnel filmeket?" << std::endl;
                int ev;
                std::cin >> ev;
                if (std::cin.fail()){
                    std::cin.clear();
                    std::cin.ignore(10000,'\n');
                    std::cout << "Nem szamot adsz meg!" << std::endl;
                    jo=false;
                }
                opciok[parancs-1]=false;
                for (Listaelem* mozgo=elso;mozgo!= nullptr;mozgo=mozgo->kov){
                    if (mozgo->adat->getEv()==ev){
                        try {
                            Film* f=mozgo->adat->clone(); //az új listába másoljuk, ha megfelel a feltételnek
                            szukitett.belerak(f);
                        }catch(std::logic_error& error){}
                    }
                }
                break;
            }
            case 3: { //hossz szerint
                std::cout << std::endl << "Hany percnel hosszabb filmeket?" << std::endl;
                int max, min;
                std::cin >> min;
                if (std::cin.fail()){
                    std::cin.clear();
                    std::cin.ignore(10000,'\n');
                    std::cout << "Nem szamot adsz meg!" << std::endl;
                    jo=false;
                }
                std::cout << std::endl << "Hany percnel rovidebb filmeket?" << std::endl;
                std::cin >> max;
                if (std::cin.fail()){
                    std::cin.clear();
                    std::cin.ignore(10000,'\n');
                    std::cout << "Nem szamot adsz meg!" << std::endl;
                    jo=false;
                }
                opciok[parancs-1]=false;
                for (Listaelem* mozgo=elso;mozgo!= nullptr;mozgo=mozgo->kov){
                    if (mozgo->adat->getHossz()>=min && mozgo->adat->getHossz()<=max){
                        try {
                            Film* f=mozgo->adat->clone(); //az új listába másoljuk, ha megfelel a feltételnek
                            szukitett.belerak(f);
                        }catch(std::logic_error& error){}
                    }
                }
                break;
            }
            case 4: { //rendezõ szerint
                std::cout << std::endl << "Ki legyen a rendezo?" << std::endl;
                String nev;
                std::cin >> nev;
                opciok[parancs-1]=false;
                for (Listaelem* mozgo=elso;mozgo!= nullptr;mozgo=mozgo->kov){
                    if (strstr(strlwr(mozgo->adat->getRendezo()),strlwr(nev))!= nullptr){
                        try {
                            Film* f=mozgo->adat->clone(); //az új listába másoljuk, ha megfelel a feltételnek
                            szukitett.belerak(f);
                        }catch(std::logic_error& error){}
                    }
                }
                break;
            }
            case 5: { //korhatár szerint
                std::cout << std::endl << "Milyen korhataru filmek legyenek?" << std::endl;
                int kor;
                std::cin >> kor;
                if (std::cin.fail()){
                    std::cin.clear();
                    std::cin.ignore(10000,'\n');
                    std::cout << "Nem szamot adsz meg!" << std::endl;
                    jo=false;
                }
                opciok[parancs-1]=false;
                for (Listaelem* mozgo=elso;mozgo!= nullptr;mozgo=mozgo->kov){
                    if (mozgo->adat->getKorhatar()==kor && (mozgo->adat->getKategoria()==String("Akcio")
                    || mozgo->adat->getKategoria()==String("Csaladi"))){
                        try {
                            Film* f=mozgo->adat->clone(); //az új listába másoljuk, ha megfelel a feltételnek
                            szukitett.belerak(f);
                        }catch(std::logic_error& error){}
                    }
                }
                break;
            }
            case 6: { //cím szerint
                std::cout << std::endl << "Mi legyen a cimben?" << std::endl;
                String cim;
                std::cin >> cim;
                opciok[parancs-1]=false;
                for (Listaelem* mozgo=elso;mozgo!= nullptr;mozgo=mozgo->kov){
                    if (strstr(strlwr(mozgo->adat->getCim()),strlwr(cim))!= nullptr){
                        try {
                            Film* f=mozgo->adat->clone(); //az új listába másoljuk, ha megfelel a feltételnek
                            szukitett.belerak(f);
                        }catch(std::logic_error& error){}
                    }
                }
                break;
            }
            default: //rossz érték esetén jelezzük
                std::cout << "Ervenytelen opcio!" << std::endl;
                break;
        }
    }
    szukitett.szures(opciok);
}

//egy karaktersorozatot megadva keres a filmek String adatai között
void Lista::keresbarmiben(){
    //String bekérése
    std::cout << "Add meg a keresendo kifejezest!" << std::endl;
    String ezt;
    std::cin >> ezt;
    bool volt=false;
    for (Listaelem* mozgo=elso;mozgo!= nullptr;mozgo=mozgo->kov){
        //ha bármilyen szöveges adatában megtalálható az adott részlet, akkor azt kiírja
        if (strstr(strlwr(mozgo->adat->getKategoria()),strlwr(ezt))!= nullptr ||
            strstr(strlwr(mozgo->adat->getCim()),strlwr(ezt))!= nullptr ||
            strstr(strlwr(mozgo->adat->getRendezo()),strlwr(ezt))!= nullptr ||
           (mozgo->adat->getKategoria()==String("Dokumentum") && strstr(strlwr(mozgo->adat->getLeiras()),strlwr(ezt))!= nullptr)){
                mozgo->adat->kiir();
                std::cout << std::endl;
                volt=true;
        }
    }
    //ha nem talál semmit, jelzi a felhasználónak
    if (!volt){
        std::cout << "Nincs talalat." << std::endl;
    }
}

//destruktor
Lista::~Lista() {
    Listaelem *mozgo = elso;
    while (mozgo != nullptr) {
        Listaelem *torlendo = mozgo;
        mozgo = mozgo->kov;
        //memória felszabadítása
        delete torlendo->adat;
        delete torlendo;
    }
}
