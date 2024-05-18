#ifndef DICTIONARY_H
#define DICTIONARY_H

#include "myString.h"
#include "memtrace.h"

/// @Dictionary bejegyzese ///
struct DictionaryEntry {
    int key;       //Kulcs
    String value;  //Ertek
    DictionaryEntry(int key = 0, const char* value = "NONE") : key(key), value(value) {}
};

/// @Dictionary ///
class Dictionary {
    DictionaryEntry* array;     //Dictionary bejegyzesek tomb
    size_t size;                //Hossz
public:
    Dictionary(size_t len = 0) : array(new DictionaryEntry[len]), size(len) {}
    ~Dictionary() { delete[] array; }
public:
    size_t getSize()const { return size; }              //A dictionary hosszat adja vissza
    DictionaryEntry& operator[](size_t i) const;        //Visszaadja a Dictionary egyik bejegyzeset
    Dictionary& operator=(const Dictionary& rhs);       //Masolo operator
    void push_back(const DictionaryEntry& newEntry);    //Hatra berakja a bejegyzest
    void readFile(std::istream& is, const char* FILENAME="-");          //Fajlbol beolvasas
    void writeFile(const char* FILENAME);                               //Fajlba iras
    void sizeDecrement() { if (size == 0)throw "Size Error"; size--; }//A dictionari meretet csokkenti
};

std::ostream& operator<<(std::ostream& os, const Dictionary& rhs);

#endif