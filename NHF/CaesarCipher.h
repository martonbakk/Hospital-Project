#ifndef CAESARCIPHER_H
#define CAESARCIPHER_H

#include "myString.h"
#include "memtrace.h"

///@CaesarCipher///
/*
* Ez az osztaly felel a jelszavak titkositasaert. A titkositas kizarolag angol kisbetus szavakra mukodik. Az encode az ami at alakitja a bekapott stringet es a shift alapjan
* eltolja a betuket. A decode visszaalakitja a mar atalakitott stringet.
*/
class CaesarCipher {
    int shift;  //Ennyivel toljuk el a karaktereket
public:
    CaesarCipher(int shift) :shift(shift) {}
public:
    String encode(const String& message);    //atalakitja a megkapott stringet
    String decode(const String& ciphertext); //visszaalkakítja a megkapott stringet
};

#endif // CAESARCIPHER_H