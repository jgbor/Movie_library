#ifdef _MSC_VER
// MSC ne adjon figyelmeztetõ üzenetet a C sztringkezelõ függvényeire
  #define _CRT_SECURE_NO_WARNINGS
#endif

#include <iostream>             // Kiíratáshoz
#include <cstring>              // Sztringmûveletekhez

#include "memtrace.h"           // a standard headerek után kell lennie
#include "string5.h"


/// Konstruktorok: egy char karakterbõl (createString)
String::String(const char c){
    len=1;
    pData=new char[2];
    pData[0]=c;
    pData[1]='\0';
}

///                egy nullával lezárt char sorozatból (createString)
String::String(const char* s){
    len= strlen(s);
    pData=new char[len+1];
    strcpy(pData,s);
}

/// Másoló konstruktor: String-bõl készít (createString)
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

/// [] operátorok: egy megadott indexû elem REFERENCIÁJÁVAL térnek vissza (charAtString)
/// indexhiba esetén const char * kivételt dob!
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

/// + operátorok:
///                 String-hez jobbról karaktert ad (addString)
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

///== operátor
bool String::operator==(const String& s) const {
    return strcmp(pData,s.pData)==0;
}

///String-bõl C típusú sztringgé konverzió a <ctring> függvényeihez való kompatibilitás végett
String::operator char*() const{
    if (len!=0) {
        return pData;
    }else{
        return (char*)"";
    }
}

/// << operator, ami kiír az ostream-re
std::ostream& operator<<(std::ostream& out, const String& s0) {
    out << s0.c_str();
    return out;
}

/// >> operátor, ami beolvas az istream-rõl egy sort
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