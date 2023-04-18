//
// Created by Gabo on 2021.04.16..
//

#include "lista.h"
#include "memtrace.h"
#include <iostream>
#include <stdexcept>
#include <cstring>

#ifdef CPORTA //Jport�ra kell, mert az strlwr f�ggv�ny csak Windowson m�k�dik
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

///Lista oszt�ly f�ggv�nyei
///priv�t f�ggv�nyek
//megmondja, hogy egy konkr�t film benne van-e a list�ban
bool Lista::bennevan(Film* f) const{
    if (f == nullptr){
        return false;
    }else {
        for (Listaelem* mozgo=elso;mozgo!= nullptr;mozgo=mozgo->kov){
            //ha megtal�ltuk a filmet, azonnal visszat�r�nk igazzal
            if (*(mozgo->adat)==*f){
                return true;
            }
        }
        //ha v�gig�r a list�n a ciklus, az azt jelenti, hogy nem volt benne
        return false;
    }
}

//megmondja a kapott Stringr�l a fajtak t�mbben  tartozik
int Lista::milyenfajta(String& kat) const{
    for (int i=0;i<fajtadb;i++){
        //ha megtal�ljuk visszat�r�nk az indexszel
        if (kat==fajtak[i]){
            return i;
        }
    }
    //ha nincs benne error-t dobunk
    throw std::invalid_argument("Nincs ilyen kategoria");
}

//bek�ri egy film adatait
Film* Lista::filmbeker() const{
    //bek�rj�k a k�z�s adatokat
    std::cout << "Add meg a film cimet!" << std::endl;
    String Cim;
    std::cin >> Cim;
    std::cout << "Add meg a film rendezojet!" << std::endl;
    String Ren;
    std::cin >> Ren;
    std::cout << "Add meg a film kiadasanak evet!" << std::endl;
    int Ev=0;
    std::cin >> Ev;
    if (std::cin.fail()){ //ha hiba lenne sz�m beolvas�s�n�l
        std::cin.clear();
        throw std::invalid_argument("Nem szamot adsz meg!");
    }
    std::cout << "Add meg a film hosszat percben!" << std::endl;
    int Hossz=0;
    std::cin >> Hossz;
    if (std::cin.fail()){ //ha hiba lenne sz�m beolvas�s�n�l
        std::cin.clear();
        throw std::invalid_argument("Nem szamot adsz meg!");
    }
    std::cout << "Add meg a film kategoriajat!" << std::endl;
    String Kat;
    std::cin >> Kat;
    int fajta;
    try {
        fajta = milyenfajta(Kat);
    }catch (std::invalid_argument& error){ //ha rossz lenne a fajta, tov�bbdobjuk a kapott kiv�telt
        throw error;
    }
    //a fajta alapj�n tov�bbi dolgokat k�r�nk be
    switch (fajta) {
        case 0: { //csal�di film
            std::cout << "Add meg a film korhatarat!" << std::endl;
            int Kh=0;
            std::cin >> Kh;
            if (std::cin.fail()){ //ha hiba lenne sz�m beolvas�s�n�l
                std::cin.clear();
                throw std::invalid_argument("Nem szamot adsz meg!");
            }
            Csaladi* f= new Csaladi(Cim,Ren,Hossz,Ev,Kh);
            return f;
        }
        case 1: { //akci�film
            std::cout << "Add meg a film korhatarat!" << std::endl;
            int Kh=0;
            std::cin >> Kh;
            if (std::cin.fail()){ //ha hiba lenne sz�m beolvas�s�n�l
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

//egy filmet a list�ba helyez
void Lista::belerak(Film*& f){
    Listaelem* uj = new Listaelem;
    uj->adat=f;
    uj->kov= nullptr;
    if (!bennevan(f)){
        uj->kov=elso;
        elso=uj;
    }else{
        //ha benne lenne, t�r�lj�k az �j elemet �s kiv�telt dobunk
        delete uj->adat;
        delete uj;
        throw std::logic_error("Mar benne volt ez a film az adatbazisban.");
    }
}

///publikus f�ggv�nyek

//f�jlb�l megalkotja a a list�t
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
        //egy film beolvas�sa a f�jlb�l
        int fajta;
        try {
           fajta = milyenfajta(Kat);
        }
        //ha nem megfelel� befejezz�k a beolvas�st
        catch (std::invalid_argument& str){
            std::cout << "Nem sikerult minden adatot beolvasni" << std::endl;
            return;
        }
        fajl >> Cim;
        fajl >> Ren;
        fajl >> Ev;
        fajl >> Hossz;
        switch (fajta) {
            case 0: {  //csal�di film
                int Kh = 0;
                fajl >> Kh;
                Csaladi *cs = new Csaladi(Cim, Ren, Hossz, Ev, Kh);
                film = cs;
                break;
            }
            case 1: { //akci�film
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
        //Film beolvas�s�nak a v�ge, list�ba helyez�s
        try {
            belerak(film);
        }catch(std::logic_error&){} //ha t�bbsz�r lenne a f�jlban akkor szimpl�n nem rakjuk bele a list�ba
    }
    fajl.close();
}

//a list�t f�jlba ki�r� f�ggv�ny
void Lista::fajlkiir(){
    std::ofstream fajl("filmek.txt");
    if (!fajl.is_open()){
        std::cout << "Nem lehet menteni az adatokat";
        return;
    }
    //minden elemre megh�vjuk a f�jlba ki�r� f�ggv�nyt
    for(Listaelem* mozgo=elso;mozgo!= nullptr;mozgo=mozgo->kov){
        mozgo->adat->fajlba(fajl);
    }
    fajl.close();
}

//teljes list�t ki�r� f�ggv�ny
void Lista::kiir() const{
    if (elso== nullptr){ //ha nincs adat jelezz�k a felhaszn�l�nak
        std::cout << "NINCS ADAT" << std::endl;
    }else {
        std::cout << "OSSZES FILM:" << std::endl << std::endl;
        //minden elemre megh�vjuk a k�perny�re �r� f�ggv�ny�t
        for (Listaelem *mozgo = elso; mozgo != nullptr; mozgo = mozgo->kov) {
            mozgo->adat->kiir();
            std::cout << std::endl;
        }
    }
}

//els� elemre mutat� pointert visszaad� f�ggv�ny
Listaelem* Lista::getElso() const{
    return elso;
}

//a felhaszn�l� �j elemet adhat a list�hoz
void Lista::hozzaad(){
    std::cout << "FILM FELVETELE" << std::endl << std::endl;
    Film* f;
    try {
        f = filmbeker();
    }catch (std::invalid_argument& error){ //ha rossz t�pust adott meg a felhaszn�l�, akkor nem tessz�k a list�ba
        std::cout << error.what() << std::endl;
        return;
    }
    try {
        belerak(f);
        std::cout << "Film hozzaadva az adatbazishoz" << std::endl;
    }catch(std::logic_error& error){ //ha m�r benne lett volna, jelezz�k a felhaszn�l�nak
        std::cout << error.what() << std::endl;
    }
}

//a felhaszn�l� t�r�lhet elemet a list�b�l
void Lista::torol(){
    std::cout << "FILM TORLESE" << std::endl << std::endl;
    Film* f;
    try {
        f = filmbeker();
    }catch (std::invalid_argument& error){ //hib�s kateg�ria eset�n jelezz�k a felhaszn�l�nak ezt
        std::cout << error.what() << std::endl;
        return;
    }
    if (!bennevan(f)){
        std::cout << "Nem volt ilyen film az adatbazisban." << std::endl;
    }else{
        Listaelem** elozo=&elso;
        for (Listaelem* ezt=elso;ezt!= nullptr;ezt=ezt->kov){ //befutjuk a list�t az elem megtal�l�s�hoz
            if (*(ezt->adat)==*f){                            //ha megtal�ljuk a filmet, t�r�lj�k, �s le�ll�tjuk a ciklust
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

//a felhaszn�l� sz�rheti az adatb�zisban l�v� filmeket
void Lista::szures(bool* opciok){
    int parancs;
    bool jo=false;
    Lista szukitett;
    while (!jo) { //am�g nem �rv�nyes adatot ad meg a felhaszn�l�
        std::cout << "SZURES" << std::endl << "0: Vissza (eredmeny kiirasa)" << std::endl << "1: Kategoria" << std::endl <<
                  "2: Ev" << std::endl << "3: Hossz" << std::endl << "4: Rendezo" << std::endl << "5: Korhatar" << std::endl <<
                  "6: Cim" << std::endl << "Hogy szeretnel keresni?" << std::endl;
        std::cin >> parancs;
        if (std::cin.fail()){ //ha hiba lenne sz�m beolvas�s�n�l
            std::cin.clear();
            std::cin.ignore(10000,'\n');
            std::cout << "Nem szamot adsz meg!" << std::endl;
            parancs=-1;
        }
        jo = parancs >= 0 && parancs <= 6;
        if (jo && parancs!=0 && !opciok[parancs-1]){ //ha m�r ez alapj�n sz�rve volt a lista, nem engedj�k �jra
            std::cout << "Mar szurve van a lista ez alapjan. ";
            parancs=-1;
            jo=false;
        }
        switch (parancs) {
            case 0: //vissza �s ki�r
                kiir();
                return;
            case 1: {  //kateg�ria szerint
                std::cout << std::endl << "Milyen kategoriat szeretnel?" << std::endl;
                String keres;
                std::cin >> keres;
                opciok[parancs-1]=false;
                for (Listaelem* mozgo=elso;mozgo!= nullptr;mozgo=mozgo->kov){
                    if (strstr(strlwr(mozgo->adat->getKategoria()),strlwr(keres))!= nullptr){
                        try {
                            Film* f=mozgo->adat->clone(); //az �j list�ba m�soljuk, ha megfelel a felt�telnek
                            szukitett.belerak(f);
                        }catch(std::logic_error& error){}
                    }
                }
                break;
            }
            case 2: { //�v szerint
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
                            Film* f=mozgo->adat->clone(); //az �j list�ba m�soljuk, ha megfelel a felt�telnek
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
                            Film* f=mozgo->adat->clone(); //az �j list�ba m�soljuk, ha megfelel a felt�telnek
                            szukitett.belerak(f);
                        }catch(std::logic_error& error){}
                    }
                }
                break;
            }
            case 4: { //rendez� szerint
                std::cout << std::endl << "Ki legyen a rendezo?" << std::endl;
                String nev;
                std::cin >> nev;
                opciok[parancs-1]=false;
                for (Listaelem* mozgo=elso;mozgo!= nullptr;mozgo=mozgo->kov){
                    if (strstr(strlwr(mozgo->adat->getRendezo()),strlwr(nev))!= nullptr){
                        try {
                            Film* f=mozgo->adat->clone(); //az �j list�ba m�soljuk, ha megfelel a felt�telnek
                            szukitett.belerak(f);
                        }catch(std::logic_error& error){}
                    }
                }
                break;
            }
            case 5: { //korhat�r szerint
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
                            Film* f=mozgo->adat->clone(); //az �j list�ba m�soljuk, ha megfelel a felt�telnek
                            szukitett.belerak(f);
                        }catch(std::logic_error& error){}
                    }
                }
                break;
            }
            case 6: { //c�m szerint
                std::cout << std::endl << "Mi legyen a cimben?" << std::endl;
                String cim;
                std::cin >> cim;
                opciok[parancs-1]=false;
                for (Listaelem* mozgo=elso;mozgo!= nullptr;mozgo=mozgo->kov){
                    if (strstr(strlwr(mozgo->adat->getCim()),strlwr(cim))!= nullptr){
                        try {
                            Film* f=mozgo->adat->clone(); //az �j list�ba m�soljuk, ha megfelel a felt�telnek
                            szukitett.belerak(f);
                        }catch(std::logic_error& error){}
                    }
                }
                break;
            }
            default: //rossz �rt�k eset�n jelezz�k
                std::cout << "Ervenytelen opcio!" << std::endl;
                break;
        }
    }
    szukitett.szures(opciok);
}

//egy karaktersorozatot megadva keres a filmek String adatai k�z�tt
void Lista::keresbarmiben(){
    //String bek�r�se
    std::cout << "Add meg a keresendo kifejezest!" << std::endl;
    String ezt;
    std::cin >> ezt;
    bool volt=false;
    for (Listaelem* mozgo=elso;mozgo!= nullptr;mozgo=mozgo->kov){
        //ha b�rmilyen sz�veges adat�ban megtal�lhat� az adott r�szlet, akkor azt ki�rja
        if (strstr(strlwr(mozgo->adat->getKategoria()),strlwr(ezt))!= nullptr ||
            strstr(strlwr(mozgo->adat->getCim()),strlwr(ezt))!= nullptr ||
            strstr(strlwr(mozgo->adat->getRendezo()),strlwr(ezt))!= nullptr ||
           (mozgo->adat->getKategoria()==String("Dokumentum") && strstr(strlwr(mozgo->adat->getLeiras()),strlwr(ezt))!= nullptr)){
                mozgo->adat->kiir();
                std::cout << std::endl;
                volt=true;
        }
    }
    //ha nem tal�l semmit, jelzi a felhaszn�l�nak
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
        //mem�ria felszabad�t�sa
        delete torlendo->adat;
        delete torlendo;
    }
}
