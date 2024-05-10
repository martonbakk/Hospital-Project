#include "myString.h"
#include <iostream>
#include <fstream>
#include <cstring>
#include "memtrace.h"
#include <iomanip>


String::String():_len(1), _content(nullptr){}

String::String(const String& str) {
    _content = new char[(_len = str._len) + 1];
    strncpy(_content, str._content, _len);
    _content[_len] = '\0';
}

String::String(const char* CONTENT) {
    _content = new char[_len = strlen(CONTENT) + 1];
    strcpy(_content, CONTENT);
}

String::~String() {
    delete[] _content;
}

//Getterek
size_t String::getLen() const {
    return _len;
}

char* String::getText() const {
    return _content;
}


//Operatorok
String& String::operator=(const char* content) {
    _len = strlen(content) + 1;
    delete[] _content;

    _content = new char[_len];
    strcpy(_content, content);
    return *this;
}

String& String::operator+=(const String& str) {
    if (_content!=nullptr)
    {
        char* temp;
        _len += str._len;
        temp = new char[_len];
        strcpy(temp, _content);
        strcat(temp, " ");
        strcat(temp, str._content);
        delete[] _content;
        _content = temp;
    }
    else
    {
        _len = str._len;
        _content = new char[str._len];
        strcpy(_content, str._content);
    }
    
    return *this;
}

String String::operator+(const char* str) const {
    String result;
    result._len = strlen(str)+_len;
    result._content = new char[result._len];
    strcpy(result._content, _content);
    strcat(result._content, str);
    return result;
}



String String::operator+(const String& str) const {
    String result;
    result._len = _len + str._len;
    result._content = new char[result._len];

    strcpy(result._content, _content);
    strcat(result._content, " ");
    strcat(result._content, str._content);

    return result;
}



String& String::operator=(const String& str) {
    if (this != &str)
    {
        delete[] _content;
        if (str._content != nullptr) {
            _content = new char[(_len = str._len) + 1];
            strncpy(_content, str._content, _len);
            _content[_len] = 0;
        }
    }
    return *this;
}



char& String::operator[](size_t i) {
    if (i >= _len) throw "Tul indexelt";
    return *(_content + i);
}

bool String::operator==(const String& s1) {
    return strcmp(_content, s1._content) == 0;
}

std::ostream& operator<<(std::ostream& os, const String& str) {
    if (str._content != NULL)
        os << str._content;
    return os;
}



String& String::operator+=(const char& car) {
    char* ret = new char[_len + 1];
    _len += 1;

    if (_content != NULL) {
        strcpy(ret, _content);
        delete[] _content;
    }

    ret[_len - 2] = car;
    ret[_len - 1] = '\0';
    _content = ret;
    return *this;
}


std::ifstream& operator>>(std::ifstream& is, String& str) {
    char buffer[150] = "";
    is >> buffer;
    str = buffer;
    return is;
}

std::istream& operator>>(std::istream& is, String& str) {
    char buffer[150] = "";
    is >> buffer;
    str = buffer;
    return is;
}