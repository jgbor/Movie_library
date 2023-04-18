//
// Created by Gabo on 2021.04.16..
//

#ifndef HAZIFELADAT_LISTA_H
#define HAZIFELADAT_LISTA_H

#include "memtrace.h"
#include "film.h"
#include "csaladi.h"
#include "akcio.h"
#include "dokumentum.h"
#include "string5.h"

struct Listaelem{
    Film* adat;
    Listaelem* kov;
};

class Lista {
    Listaelem* elso;
    static int fajtadb;
    String fajtak[3]={"Csaladi","Akcio","Dokumentum"};


    //megmondja, hogy egy konkrét film benne van-e a listában
    bool bennevan(Film* f) const;

    //megmondja egy filmrõl hányas kategóriába tartozik
    int milyenfajta(String& kat) const;

    //bekéri egy film adatait
    Film* filmbeker() const;

    //egy filmet a listába helyez
    void belerak(Film*& f);

public:
    //konstruktor
    Lista():elso(nullptr){}

    //fájlból megalkotja a a listát
    void fajlbeolvas();

    //a listát fájlba kiíró függvény
    void fajlkiir();

    //teljes listát képernyõre kiíró függvény
    void kiir() const;

    //elsõ elemre mutató pointert visszaadó függvény
    Listaelem* getElso() const;

    //a felhasználó új elemet adhat a listához
    void hozzaad();

    //a felhasználó törölhet elemet a listából
    void torol();

    //a felhasználó szûrheti az adatbázisban lévõ filmeket
    void szures(bool* opciok);

    //egy karaktersorozatot megadva keres a filmek String adatai között
    void keresbarmiben();

    //destruktor
    ~Lista();
};

#endif //HAZIFELADAT_LISTA_H
