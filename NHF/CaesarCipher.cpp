#include "CaesarCipher.h"

void charShift(char& ch, const int& shift) {
    if (ch < 97 || ch>122)
        throw "PASSWORD: INVALIDE PASSWORD TYPE";
    int new_shift = shift % 26;
    if (97 <= ch + new_shift && ch + new_shift <= 122)
        ch += new_shift;
    else if (ch + new_shift > 122) {
        int correct = 'z' - ch;
        ch = 96;
        ch += new_shift - correct;
    }
    else {
        int correct = ch - 'a';
        ch = 123;
        ch += new_shift + correct;
    }
}

String CaesarCipher::encode(const String& message) {
    String encoded_text;
    for (size_t i = 0; i < message.getLen()-1; i++)
    {
        char ch = message.getText()[i];
        if (ch != ' ')
        {
            charShift(ch, shift);
            encoded_text += ch;
        }
        else {
            encoded_text += ' ';
        }
    }
    return encoded_text;
}

String CaesarCipher::decode(const String& ciphertext) {
    String decoded_text;
    char ch;
    for (size_t i = 0; i < ciphertext.getLen()-1; i++)
    {
        ch = ciphertext.getText()[i];
        if (ch != ' ') {
            charShift(ch, -shift);
            decoded_text += ch;
        }
        else {
            decoded_text += ' ';
        }
    }
    return decoded_text;
}