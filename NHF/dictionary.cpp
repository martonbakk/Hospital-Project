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
        file << size << '\n';
        for (size_t i = 0; i < size; i++)
        {
            if(array[i].key!=0)
                file << array[i].value << " " << array[i].key<<'\n';
        }
    }
    else {
        std::cerr << "DICTIONARY: CAN NOT OPEN THE FILE!\n";
        return;
    }
}

DictionaryEntry& Dictionary::operator[](size_t i) const {
    if (i >= size)
        throw "DICTIONARY: THE INDEX VALUE IS BIGER THAN THE ARRAY LENGTH";
    return array[i];
}


Dictionary& Dictionary::operator=(const Dictionary& rhs) {
    DictionaryEntry* newArray = new DictionaryEntry[rhs.size];
    for (size_t i = 0; i < rhs.size; i++){
        newArray[i].key=rhs.array[i].key;
        newArray[i].value = rhs.array[i].value;
    }
    size = rhs.size;
    delete[] array;
    array = newArray;
    return *this;
}

std::ostream& operator<<(std::ostream& os, const Dictionary& rhs) {
    for (size_t i = 0; i < rhs.getSize(); i++)
    {
        if(rhs[i].key>0)
            os<<"[" << rhs[i].key << "] - [" << rhs[i].value << "]"<< '\n';
    }
    if(rhs.getSize()==0)
        os<<"NONE";
    return os;
}

void Dictionary::push_back(const DictionaryEntry& newEntry) {
    DictionaryEntry* newArray = new DictionaryEntry[size + 1];
    newArray[size].key = newEntry.key;
    newArray[size].value = newEntry.value;
    for (size_t i = 0; i < size; i++){
        newArray[i].key = array[i].key;
        newArray[i].value = array[i].value;
    }
    size++;
    delete[] array;
    array = newArray;
}