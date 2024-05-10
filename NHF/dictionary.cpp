#include "dictionary.h"
#include <fstream>

void Dictionary::readFile(std::istream& is, const char* FILENAME) {
    if(strcmp(FILENAME, "-")==0){
        int key;
        String value;
        int size;
        is >> size;
        for (int i = 0; i < size; i++){
            is >> value >> key;
            push_back(DictionaryEntry(key, value.getText()));
        }
    }
    else {
        std::ifstream file(FILENAME); 
        if (file.is_open()) {
            int key;
            String value; 
            int size;
            file >> size;
            for (int i = 0; i < size; i++)
            {
                file >> value >>key;
                push_back(DictionaryEntry(key, value.getText()));
            }
            file.close();
        }
        else {
            throw "DICTIONARY: CAN NOT OPEN THE FILE!\n";
        }
    }
}

void Dictionary::writeFile(const char* FILENAME) {
    std::ofstream file(FILENAME);
    if (file.is_open()) {
        file << _size << '\n';
        for (size_t i = 0; i < _size; i++)
        {
            if(_array[i]._key!=0)
                file << _array[i]._value << " " << _array[i]._key<<'\n';
        }
    }
    else {
        std::cerr << "DICTIONARY: CAN NOT OPEN THE FILE!\n";
        return;
    }
}

DictionaryEntry& Dictionary::operator[](size_t i) const {
    if (i >= _size)
        throw "DICTIONARY: THE INDEX VALUE IS BIGER THAN THE ARRAY LENGTH";
    return _array[i];
}


Dictionary& Dictionary::operator=(const Dictionary& rhs) {
    DictionaryEntry* newArray = new DictionaryEntry[rhs._size];
    for (size_t i = 0; i < rhs._size; i++){
        newArray[i]._key=rhs._array[i]._key;
        newArray[i]._value = rhs._array[i]._value;
    }
    _size = rhs._size;
    delete[] _array;
    _array = newArray;
    return *this;
}

std::ostream& operator<<(std::ostream& os, const Dictionary& rhs) {
    for (size_t i = 0; i < rhs.getSize(); i++)
    {
        if(rhs[i]._key>0)
            os<<"[" << rhs[i]._key << "] - [" << rhs[i]._value << "]"<< '\n';
    }
    if(rhs.getSize()==0)
        os<<"NONE";
    return os;
}

void Dictionary::push_back(const DictionaryEntry& newEntry) {
    DictionaryEntry* newArray = new DictionaryEntry[_size + 1];
    newArray[_size]._key = newEntry._key;
    newArray[_size]._value = newEntry._value;
    for (size_t i = 0; i < _size; i++){
        newArray[i]._key = _array[i]._key;
        newArray[i]._value = _array[i]._value;
    }
    _size++;
    delete[] _array;
    _array = newArray;
}