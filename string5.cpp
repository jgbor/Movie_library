#ifdef _MSC_VER
// MSC ne adjon figyelmeztet� �zenetet a C sztringkezel� f�ggv�nyeire
  #define _CRT_SECURE_NO_WARNINGS
#endif

#include <iostream>             // Ki�rat�shoz
#include <cstring>              // Sztringm�veletekhez

#include "memtrace.h"           // a standard headerek ut�n kell lennie
#include "string5.h"


/// Konstruktorok: egy char karakterb�l (createString)
String::String(const char c){
    len=1;
    pData=new char[2];
    pData[0]=c;
    pData[1]='\0';
}

///                egy null�val lez�rt char sorozatb�l (createString)
String::String(const char* s){
    len= strlen(s);
    pData=new char[len+1];
    strcpy(pData,s);
}

/// M�sol� konstruktor: String-b�l k�sz�t (createString)
String::String(const String& s){
    len=s.size();
    pData=new char[len+1];
    strcpy(pData,s.pData);
}

/// Destruktor (disposeString)
String::~String(){
    delete[] pData;
}

/// operator=
String& String::operator=(const String& s){
    if (this!=&s){
        delete[] pData;
        len=s.size();
        pData=new char[len+1];
        strcpy(pData,s.pData);
    }
    return *this;
}

/// [] oper�torok: egy megadott index� elem REFERENCI�J�VAL t�rnek vissza (charAtString)
/// indexhiba eset�n const char * kiv�telt dob!
char& String::operator[](unsigned int i){
    if (i>=len || i<0){
        throw "Rossz index";
    }
    return pData[i];
}

const char& String::operator[](unsigned int i) const{
    if (i>=len || i<0){
        throw "Rossz index";
    }
    return pData[i];
}

/// + oper�torok:
///                 String-hez jobbr�l karaktert ad (addString)
String String::operator+(const char c) const{
    return *this + String(c);
}

///                 String-hez String-et ad (addString)
String String::operator+(const String& s) const{
    String tmp;
    tmp.len= len+s.size();
    tmp.pData=new char[tmp.len+1];
    strcpy(tmp.pData,pData);
    strcat(tmp.pData,s.pData);
    return tmp;
}

String operator+(char c, const String& s){
    return String(c) + s;
}

///== oper�tor
bool String::operator==(const String& s) const {
    return strcmp(pData,s.pData)==0;
}

///String-b�l C t�pus� sztringg� konverzi� a <ctring> f�ggv�nyeihez val� kompatibilit�s v�gett
String::operator char*() const{
    if (len!=0) {
        return pData;
    }else{
        return (char*)"";
    }
}

/// << operator, ami ki�r az ostream-re
std::ostream& operator<<(std::ostream& out, const String& s0) {
    out << s0.c_str();
    return out;
}

/// >> oper�tor, ami beolvas az istream-r�l egy sort
std::istream& operator>>(std::istream& is, String& s) {
    unsigned char ch;
    s = String("");
    std::ios_base::fmtflags fl = is.flags();
    is.setf(std::ios_base::skipws);
    while (is >> ch) {
        is.unsetf(std::ios_base::skipws);
        if (ch != '\r') {
            if (ch == '\n') {
                break;
            } else {
                s = s + ch;
            }
        }
    }
    is.setf(fl);
    return is;
}