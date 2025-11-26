// Vigenere Cipher, by Al Sweigart 
// The Vigenere cipher is a polyalphabetic substitution cipher that was
// powerful enough to remain unbroken for centuries.
// This code is available at https ://nostarch.com/big-book-small-python-programming
// #80 VIGENERE CIPHER

#include <iostream>
#include <string>
#include <algorithm>
#include <stdexcept>

class VigenereCipher {
private:
    // Every possible symbol that can be encrypted / decrypted:
    std::string LETTERS = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

    char upper(char symbol) {
        if (symbol >= 'A' && symbol <= 'Z') {
            return symbol;
        }

        if (symbol >= 'a' && symbol <= 'z') {
            return (symbol - 'a') + 'A';
        }

        return symbol;
    }

    char lower(char symbol) {
        if (symbol >= 'a' && symbol <= 'z') {
            return symbol;
        }

        if (symbol >= 'A' && symbol <= 'Z') {
            return (symbol - 'A') + 'a';
        }

        return symbol;
    }

    std::string translateMessage(std::string message, std::string key, std::string mode) {
        // Encrypt or decrypt the message using the key.
        std::string translated = ""; // Stores the encrypted/decrypted message string.
        int keyIndex = 0;
        transform(key.begin(), key.end(), key.begin(), ::toupper);

        for (char symbol : message) { // Loop through each character in message.
            int num = LETTERS.find(upper(symbol));
            if (num != std::string::npos) { // -1 means symbol.upper() was not in LETTERS.
                if (mode == "encrypt") {
                    // Add if encrypting:
                    num += LETTERS.find(key[keyIndex]);
                }
                else if (mode == "decrypt") {
                    // Subtract if decrypti
                    num -= LETTERS.find(key[keyIndex]);

                }
                while (num < 0) {
                    num = num + 26;
                }

                num %= LETTERS.size();
                // Add the encrypted/decrypted symbol to translated.
                if (symbol >= 'A' && symbol <= 'Z') {
                    translated.push_back(LETTERS[num]);
                }
                else if (symbol >= 'a' && symbol <= 'z') {
                    translated.push_back(lower(LETTERS[num]));
                }

                ++keyIndex; // Move to the next letter in the key.
                if (keyIndex == key.size()) {
                    keyIndex = 0;
                }
            }
            else {
                // Just add the symbol without encrypting/decrypting:
                translated.push_back(symbol);
            }
        }

        return translated;
    }

public:
    VigenereCipher() = default;

    // Validate if key contains only letters and spaces
    bool isValidKey(const std::string& key) {
        for (char c : key) {
            if (!((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || c == ' ')) {
                return false;
            }
        }
        return !key.empty();
    }

    // Encrypt a message using the key
    std::string encrypt(const std::string& message, const std::string& key) {
        if (!isValidKey(key)) {
            throw std::invalid_argument("Key must contain only letters and spaces");
        }
        return translateMessage(message, key, "encrypt");
    }

    // Decrypt a message using the key
    std::string decrypt(const std::string& message, const std::string& key) {
        if (!isValidKey(key)) {
            throw std::invalid_argument("Key must contain only letters and spaces");
        }
        return translateMessage(message, key, "decrypt");
    }
};