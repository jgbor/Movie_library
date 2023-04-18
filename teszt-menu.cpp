//
// Created by Gabo on 2021.04.25..
//
#include "teszt-menu.h"
#include "lista.h"
#include "memtrace.h"
#include <iostream>
#include "gtest_lite.h"


//a jportás tesztek függvénye
void teszteles(){
    //Egy Csaladi objektum létrehozásának és adattaglekérõ függvényeinek tesztelése
    TEST(Film,Csaladi){
        Csaladi cs("A hihetetlen csalad","Brad Bird",116,2004,0);
        EXPECT_STREQ("A hihetetlen csalad",cs.getCim());
        EXPECT_STREQ("Brad Bird",cs.getRendezo());
        EXPECT_STREQ("Csaladi",cs.getKategoria());
        EXPECT_EQ(116,cs.getHossz());
        EXPECT_EQ(2004,cs.getEv());
        EXPECT_EQ(0,cs.getKorhatar());
    }ENDM

    //Egy Akcio objektum létrehozásának és adattaglekérõ függvényeinek tesztelése
    TEST(Film,Akcio){
        Akcio ak("Rambo","Ted Kotcheff",97,1982,18);
        EXPECT_STREQ("Rambo",ak.getCim());
        EXPECT_STREQ("Ted Kotcheff",ak.getRendezo());
        EXPECT_STREQ("Akcio",ak.getKategoria());
        EXPECT_EQ(97,ak.getHossz());
        EXPECT_EQ(1982,ak.getEv());
        EXPECT_EQ(18,ak.getKorhatar());
    }ENDM

    //Egy Dokumentum objektum létrehozásának és adattaglekérõ függvényeinek tesztelése
    TEST(Film,Dokumentum){
        Dokumentum dok("A Life on Our Planet","Alastair Fothergill, Jonathan Hughes, Keith Scholey",
                       83,2020,"One man has seen more of the natural world than any other."
                                            " This unique feature documentary is his witness statement."
                                            " In his 93 years, David Attenborough has visited every continent on the globe, exploring the"
                                            " wild places of our planet and documenting the living world in all its variety and wonder. "
                                            "Now, for the first time he reflects upon both the defining moments of his lifetime as a"
                                            " naturalist and the devastating changes he has seen. Honest, revealing and urgent,"
                                            " DAVID ATTENBOROUGH: A LIFE ON OUR PLANET is a powerful first-hand account of humanity's "
                                            "impact on nature and a message of hope for future generations.");
        EXPECT_STREQ("A Life on Our Planet",dok.getCim());
        EXPECT_STREQ("Alastair Fothergill, Jonathan Hughes, Keith Scholey",dok.getRendezo());
        EXPECT_STREQ("Dokumentum",dok.getKategoria());
        EXPECT_EQ(83,dok.getHossz());
        EXPECT_EQ(2020,dok.getEv());
        EXPECT_STREQ("One man has seen more of the natural world than any other."
                     " This unique feature documentary is his witness statement. "
                     "In his 93 years, David Attenborough has visited every continent on the globe, exploring the wild"
                     " places of our planet and documenting the living world in all its variety and wonder."
                     " Now, for the first time he reflects upon both the defining moments of his lifetime as a naturalist"
                     " and the devastating changes he has seen. Honest, revealing and urgent, DAVID ATTENBOROUGH:"
                     " A LIFE ON OUR PLANET is a powerful first-hand account of humanity's impact on nature and a message"
                     " of hope for future generations.",dok.getLeiras());
    }ENDM

    //Film == oprátor tesztelése, ha az egyik egyik operandus egy listaelem része
    TEST(Film,==operator){
            Listaelem* l=new Listaelem;
            Akcio* ak1= new Akcio("Rambo","Ted Kotcheff",97,1982,18);
            l->kov= nullptr;
            l->adat=ak1;
            Akcio* ak2= new Akcio("Rambo","Ted Kotcheff",97,1982,18);
            EXPECT_TRUE(*(l->adat)==*ak1);
            delete ak1;
            delete ak2;
            delete l;
    }ENDM

    //Üres lista tesztelése
    TEST(Lista,Ures){
        Lista l;
        EXPECT_TRUE(l.getElso()== nullptr);
    }ENDM

    //Lista  beolvasásának tesztelése
    TEST(Lista,Beolvas){
        Lista l;
        l.fajlbeolvas();
        EXPECT_FALSE(l.getElso()== nullptr);
    }ENDM

    //Lista kiírása képernyõre és fájlba
    TEST(Lista,Kiirasok){
        Lista l;
        l.fajlbeolvas();
        EXPECT_FALSE(l.getElso()== nullptr);
        l.kiir();
        l.fajlkiir();
    }ENDM

    //Filmhozzáadás és -törlés tesztje
    TEST(Lista,Hozzaad-torol){
        Lista l;
        l.hozzaad();
        EXPECT_FALSE(l.getElso()== nullptr);
        l.torol();
        EXPECT_TRUE(l.getElso()== nullptr);
    }ENDM

    //Szures listában
    TEST(Lista,Szures){
        Lista l;
        l.fajlbeolvas();
        EXPECT_FALSE(l.getElso()== nullptr);
        bool opciok[6]={true,true,true,true,true,true};
        l.szures(opciok);
    }ENDM

    //Kereses listában
    TEST(Lista,Kereses){
        Lista l;
        l.fajlbeolvas();
        EXPECT_FALSE(l.getElso()== nullptr);
        l.keresbarmiben();
    }ENDM
}

//a felhasználó számára megjelenõ menü normál esetben
void felhasznalo(){
    Lista filmek;
    filmek.fajlbeolvas();
    int parancs=-1;
    while (parancs!=0){
        std::cout << std::endl << "FILMTAR-FOMENU" << std::endl << "0: Kilepes" << std::endl << "1: Film hozzaadasa" <<
        std::endl << "2: Film torlese" << std::endl << "3: Osszes film kiirasa" << std::endl << "4: Szures az adatok kozt" <<
        std::endl << "5: Kereses a filmtarban" << std::endl << std::endl <<
        "Add meg mit szeretnel csinalni a megfelelo szam beirasaval!" << std::endl;
        std::cin >> parancs;
        if (std::cin.fail()){ //ha nem számot ad meg
            std::cin.clear();
            std::cout << "Nem szamot adsz meg!" << std::endl;
            parancs=-1;
        }
        switch (parancs) {
            case 0:  //kilépés
                filmek.fajlkiir(); //adatok elmentése bezárás elõtt
                return;
            case 1: {  //hozzáadás
                filmek.hozzaad();
                break;
            }
            case 2: {  //törlés
                filmek.torol();
                break;
            }
            case 3: { //filmek kiírása
                filmek.kiir();
                break;
            }
            case 4: {  //szûrés a filmek adatai közt
                bool opciok[6] = {true, true, true, true, true, true};
                filmek.szures(opciok);
                break;
            }
            case 5: {  //keresés bármiben
                filmek.keresbarmiben();
                break;
            }
            default: //nem érvényes számot ad meg a felhasználó
                std::cout << "Ervenytelen opcio!" << std::endl;
                break;
        }
        char c='1';
        std::cout << "0: visszateres a menube" << std::endl;
        while (c!='0'){
            std::cin >> c;
        }
    }
}
