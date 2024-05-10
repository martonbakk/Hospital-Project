#ifndef DICTIONARY_H
#define DICTIONARY_H

#include "myString.h"
#include "memtrace.h"

/// @Dictionary bejegyz�se ///
struct DictionaryEntry {
    int _key;       //Kulcs
    String _value;     //�rt�k
    DictionaryEntry(int key = 0, const char* value = "NONE") : _key(key), _value(value) {}
};

/// @Dictionary ///
class Dictionary {
    DictionaryEntry* _array;     //Dictionary bejegyz�sek t�mb
    size_t _size;                //Hossz
public:
    Dictionary(size_t len = 0) : _array(new DictionaryEntry[len]), _size(len) {}
    ~Dictionary() { delete[] _array; }
public:
    size_t getSize()const { return _size; }             //A dictionary hossz�t adja vissza
    DictionaryEntry& operator[](size_t i) const;        //Visszaadja a Dictionary egyik bejegyz�s�t
    Dictionary& operator=(const Dictionary& rhs);       //Masol
    void push_back(const DictionaryEntry& newEntry);    //Hatra berakja a bejegyzest
    void readFile(std::istream& is, const char* FILENAME="-");
    void writeFile(const char* FILENAME);
};

std::ostream& operator<<(std::ostream& os, const Dictionary& rhs);

#endif