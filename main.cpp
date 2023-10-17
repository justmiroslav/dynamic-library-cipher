#include <iostream>
#include <cstring>
using namespace std;

char* encrypt(const char* rawText, int key) {
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

int main() {
    char base_text[1000];
    int key, command;
    while (true) {
        cout << "Enter 1 to encrypt the text/2 to decrypt the text/3 to stop the program: " << endl;
        cin >> command;
        cin.ignore();
        if (command == 1) {
            cout << "Enter text to encrypt: " << endl;
            cin.getline(base_text, sizeof(base_text));
            cout << "Enter encryption key: " << endl;
            cin >> key;
            cin.ignore();
            char* encryptedText = encrypt(base_text, key);
            cout << "Encrypted text: " << encryptedText << endl;
            delete[] encryptedText;
        } else if (command == 2) {
            cout << "Program stopped" << endl;
            break;
        } else {
            cout << "Enter a valid command" << endl;
        }
    }
    return 0;
}