#include <iostream>
#include <cstring>
using namespace std;

extern "C" {
    __declspec(dllexport) char* encrypt(const char* rawText, int key) {
        if (key < 1 || key > 26) {
            cout << "Key must be between 1 and 26 for encryption." << endl;
            return nullptr;
        }

        int textLen = strlen(rawText);
        char* encryptedText = new char[textLen + 1];
        const char* lowerAlphabet = "abcdefghijklmnopqrstuvwxyz";
        const char* upperAlphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
        int alpLen = strlen(upperAlphabet);

        for (int i = 0; i < textLen; i++) {
            if (isalpha(rawText[i])) {
                if (islower(rawText[i])) {
                    encryptedText[i] = lowerAlphabet[(rawText[i] - 'a' + key + alpLen) % alpLen];
                } else {
                    encryptedText[i] = upperAlphabet[(rawText[i] - 'A' + key + alpLen) % alpLen];
                }
            } else {
                encryptedText[i] = rawText[i];
            }
        }
        encryptedText[textLen] = '\0';
        return encryptedText;
    }
    __declspec(dllexport) char* decrypt(const char* encryptedText, int key) {
        if (key < 1 || key > 26) {
            cout << "Key must be between 1 and 26 for encryption." << endl;
            return nullptr;
        }

        int textLen = strlen(encryptedText);
        char* decryptedText = new char[textLen + 1];
        const char* lowerAlphabet = "abcdefghijklmnopqrstuvwxyz";
        const char* upperAlphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
        int alpLen = strlen(upperAlphabet);

        for (int i = 0; i < textLen; i++) {
            if (isalpha(encryptedText[i])) {
                if (islower(encryptedText[i])) {
                    decryptedText[i] = lowerAlphabet[(encryptedText[i] - 'a' - key + alpLen) % alpLen];
                } else {
                    decryptedText[i] = upperAlphabet[(encryptedText[i] - 'A' - key + alpLen) % alpLen];
                }
            } else {
                decryptedText[i] = encryptedText[i];
            }
        }
        decryptedText[textLen] = '\0';
        return decryptedText;
    }
}
