#include "myString.h"
#include <iostream>
#include <fstream>
#include <cstring>
#include "memtrace.h"
#include <iomanip>


String::String():len(1), content(nullptr){}

String::String(const String& str) {
    content = new char[(len = str.len) + 1];
    strncpy(content, str.content, len);
    content[len] = '\0';
}

String::String(const char* CONTENT) {
    content = new char[len = strlen(CONTENT) + 1];
    strcpy(content, CONTENT);
}

String::~String() {
    delete[] content;
}

//Getterek
size_t String::getLen() const {
    return len;
}

char* String::getText() const {
    return content;
}


//Operatorok
String& String::operator=(const char* newcontent) {
    len = strlen(newcontent) + 1;
    delete[] content;

    content = new char[len];
    strcpy(content, newcontent);
    return *this;
}

String& String::operator+=(const String& str) {
    if (content!=nullptr)
    {
        char* temp;
        len += str.len;
        temp = new char[len];
        strcpy(temp, content);
        strcat(temp, " ");
        strcat(temp, str.content);
        delete[] content;
        content = temp;
    }
    else
    {
        len = str.len;
        content = new char[str.len];
        strcpy(content, str.content);
    }
    
    return *this;
}

String String::operator+(const char* str) const {
    String result;
    result.len = strlen(str)+len;
    result.content = new char[result.len];
    strcpy(result.content, content);
    strcat(result.content, str);
    return result;
}



String String::operator+(const String& str) const {
    String result;
    result.len = len + str.len;
    result.content = new char[result.len];

    strcpy(result.content, content);
    strcat(result.content, " ");
    strcat(result.content, str.content);

    return result;
}



String& String::operator=(const String& str) {
    if (this != &str)
    {
        delete[] content;
        if (str.content != nullptr) {
            content = new char[(len = str.len) + 1];
            strncpy(content, str.content, len);
            content[len] = 0;
        }
    }
    return *this;
}



char& String::operator[](size_t i) {
    if (i >= len) throw "Tul indexelt";
    return *(content + i);
}

bool String::operator==(const String& s1) {
    return strcmp(content, s1.content) == 0;
}

std::ostream& operator<<(std::ostream& os, const String& str) {
    if (str.content != NULL)
        os << str.content;
    return os;
}



String& String::operator+=(const char& car) {
    char* ret = new char[len + 1];
    len += 1;

    if (content != NULL) {
        strcpy(ret, content);
        delete[] content;
    }

    ret[len - 2] = car;
    ret[len - 1] = '\0';
    content = ret;
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