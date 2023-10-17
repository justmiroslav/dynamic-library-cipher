#include <iostream>
#include <windows.h>
using namespace std;

typedef char* (*encrypt_ptr_t)(const char*, int);
typedef char* (*decrypt_ptr_t)(const char*, int);

int main() {
    HMODULE handle = LoadLibrary(TEXT("caesar.dll"));

    if (handle == nullptr || handle == INVALID_HANDLE_VALUE) {
        cout << "Lib not found" << endl;
        return 1;
    }
    encrypt_ptr_t encrypt_ptr = (encrypt_ptr_t)GetProcAddress(handle, "encrypt");
    decrypt_ptr_t decrypt_ptr = (decrypt_ptr_t)GetProcAddress(handle, "decrypt");

    if (encrypt_ptr == nullptr || decrypt_ptr == nullptr) {
        cout << "Functions not found in DLL" << endl;
        return 1;
    }

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
            char* encryptedText = encrypt_ptr(base_text, key);
            cout << "Encrypted text: " << encryptedText << endl;
            delete[] encryptedText;
        } else if (command == 2) {
            cout << "Enter text to decrypt: " << endl;
            cin.getline(base_text, sizeof(base_text));
            cout << "Enter decryption key: " << endl;
            cin >> key;
            cin.ignore();
            char* decryptedText = decrypt_ptr(base_text, key);
            cout << "Decrypted text: " << decryptedText << endl;
            delete[] decryptedText;
        } else if (command == 3) {
            cout << "Program stopped" << endl;
            break;
        } else {
            cout << "Enter a valid command" << endl;
        }
    }

    FreeLibrary(handle);

    return 0;
}