#ifndef CAESARCIPHER_H
#define CAESARCIPHER_H

#include "myString.h"
#include "memtrace.h"


class CaesarCipher {
    int shift;
public:
    CaesarCipher(int shift) :shift(shift) {}
public:
    String encode(const String& message);
    String decode(const String& ciphertext);
};

#endif // CAESARCIPHER_H