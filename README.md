# Vigenere Cipher
For several centuries, the Vigenère cipher remained unbreakable. Essentially, it is a Caesar cipher but with a multi-part key. The so-called Vigenère key is a word or even a random sequence of letters. Each letter corresponds to a number indicating how many positions a letter in the message should be shifted: A corresponds to a shift of 0, B to a shift of 1, C to a shift of 2, and so on.

For example, if the Vigenère key is the word CAT, C means a shift of 2 letters, A means 0, and T means 19. The first letter of the message is shifted by 2, the second is not shifted, and the third is shifted by 19. For the fourth letter, the key for the first letter (2) is used again.

The use of multiple Caesar cipher keys is what provides the cryptographic strength of the Vigenère cipher. The number of possible combinations is too large for a brute-force attack. At the same time, the Vigenère cipher is resistant to frequency analysis—a weakness of simple substitution ciphers. For many centuries, the Vigenère cipher was the state of the art in cryptography.

You will see that the programs for the Vigenère cipher and the Caesar cipher are quite similar. You can read more about the Vigenère cipher in the Wikipedia article: https://en.wikipedia.org/wiki/Vigenère_cipher

## Usage example
```cpp
#include <iostream>
#include <algorithm>
#include <string>
#include "vigenerecipher.cpp"

using namespace std;

int main() {
    VigenereCipher cipher;
    string response;
    string mode;

    while (1) {
        cout << "Do you want to (e)ncrypt or (d)ecrypt?\n";
        cout << "> ";
        getline(cin, response);
        transform(response.begin(), response.end(), response.begin(), ::tolower);
        if (response[0] == 'e') {
            mode = "encrypt";
            break;
        }
        else if (response[0] == 'd') {
            mode = "decrypt";
            break;
        }
        cout << "Please enter the letter e or d.\n";
    }

    string key;
    while (1) {
        cout << "Please specify the key to use.\n";
        cout << "It can be a word or any combination of letters:\n";
        cout << "> ";
        getline(cin, response);
        if (cipher.isValidKey(response)) {
            key = response;
            break;
        }
        cout << "Key must contain only letters and spaces. Please try again.\n";
    }

    cout << "Enter the message to " << mode << ".\n";
    string message;
    cout << "> ";
    getline(cin, message);

    try {
        string result;
        if (mode == "encrypt") {
            result = cipher.encrypt(message, key);
        }
        else {
            result = cipher.decrypt(message, key);
        }

        cout << mode << "ed message:\n";
        cout << result << '\n';
    }
    catch (const exception& e) {
        cerr << "Error: " << e.what() << '\n';
        return 1;
    }

    return 0;
}
```
