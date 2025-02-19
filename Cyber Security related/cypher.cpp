



#include <iostream>
#include <string>
#include <sstream>
//Objects of this class use a string buffer that contains a sequence of characters.
//This sequence of characters can be accessed directly as a string object, using member str
#include <iomanip>
#include <vector> // For using vector data structure
#include <algorithm> // For algorithms like transform and find
#include <cctype> // For character handling functions

using namespace std;

// Function to perform XOR encryption/decryption
string xor_operation(const string& input, const string& key) {
    string output = input;
    for (int i = 0; i < input.size(); ++i) {
        output[i] = input[i] ^ key[i % key.size()];
        // XOR operation (the (%) part is to avoid issues if the plaintext is larger than the key it goes from 0 to the key.size and then gets to 0 again)
    }
    return output;
}
// Function to convert hexadecimal to string
string hex_string(const string& hexInput) {
    string result;
    for (unsigned int i = 0; i < hexInput.length(); i += 2) { // processing two characters at a time
        string byte = hexInput.substr(i, 2); //extracting two characters starting from index (i) to form a byte-sized substring
        char chr = (char)strtol(byte.c_str(), nullptr, 16);
        //converting the byte-sized substring from hexadecimal representation to its corresponding integer value using (strtol)
        //then it casts the integer to a character, obtaining the ASCII character represented by the hexadecimal byte
        result.push_back(chr); // appending it to the result
    }
    return result;
}
// Function to convert string to hexadecimal
string string_hex(const string& input) {
    stringstream ss;
    for (char c : input) {
        //formating each character as a two-digit hexadecimal number
        ss << setw(2) << setfill('0') << hex << (int)(unsigned char)c;//Converts the character (c) to an integer value to ensure it's treated as a numeric value, and then casts it to an integer
        //(setw(2)): Sets the width of the output field to 2 characters
        //(setfill('0')): Sets the fill character for the output field
    }
    return ss.str(); //return as a string
}


int main() {

    //some variables
    string plaintext;
    string key;
    string encrypted;
    string decrypted;
    int choice;
    int cipher_choice;

    // loop for thw whole program
    while(true) {

        // All Cipher main menu
        cout<<"Welcome to main menu\n";
        cout<<"Please choose which type of cipher you want to use (1/2/3)\n";
        cout<<"1) Afinne Cipher\n2) Baconian Cipher\n3) XOR Cipher\n";
        cout<<"Note: type any other number to exit:  ";
        cin>> cipher_choice;


        // Afinne Cipher program
        if(cipher_choice==1) {
            // Initialize the alphabet vector
            vector<string> alphabet = {"a", "b", "c", "d", "e", "f", "g", "h", "i", "j", "k", "l", "m", "n", "o", "p", "q", "r", "s", "t", "u", "v", "w", "x", "y", "z"};
            string sentence; // Declare a string variable to store user input
            int choice; // Declare an integer variable to store the user choice
            int a = 5, b = 8, c = 21; // Constants for default encryption and decryption equations

            cout << "           ---->Welcome in Affine cipher<----\n";
            cout << "Do you want to use default values for constants or set your values?\n (1 for default , 0 for enter values): "<<endl;
            int useDefault;
            cin >> useDefault;

            if (!useDefault) {
                // Prompt the user to enter values for constants
                do {
                    cout << "Enter the value for constant (a): "<<endl;
                    cin >> a;
                    cout << "Enter the value for constant (b): "<<endl;
                    cin >> b;
                    cout << "Enter the value for constant (c): "<<endl;
                    cin >> c;

                    // Check if entered values satisfy the equation
                    if ((a * c) % 26 != 1) {
                        cout << "The equation 'a*c mod 26 = 1' must be satisfied. Please try again.\n";
                    }
                } while ((a * c) % 26 != 1);
            }

            do {
                // Display menu
                cout << "==>Affine cipher<==\n";
                cout << "1) Encrypt the message \n";
                cout << "2) Decrypt the message \n";
                cout << "3) Exit the program\n";
                cout << "Enter your choice: \n";
                cin >> choice; // Read user choice from input
                cin.ignore(); // Ignore newline character left in the input buffer

                switch(choice) {
                    case 1: { // Encryption case
                        cout << "Please enter the sentence to encrypt: ";
                        getline(cin, sentence); // Read the entire line of input (including spaces)

                        // Convert the sentence to lowercase
                        transform(sentence.begin(), sentence.end(), sentence.begin(), ::tolower);

                        // Iterate over each character in the sentence
                        for (char c : sentence) {
                            if (isalpha(c)) { // Check if it's an alphabet character
                                string target(1, c); // Convert the character to a string
                                auto it = find(alphabet.begin(), alphabet.end(), target); // Find the character in the alphabet vector
                                if (it != alphabet.end()) { // If the character is found
                                    int x = distance(alphabet.begin(), it); // Calculate the position of the character in the alphabet
                                    int eq = ((a * x) + b) % 26; // encryption equation: (ax + b) mod 26
                                    cout << alphabet[eq]; // Print the encrypted character
                                }
                            }
                        }
                        cout << endl; // End of encryption
                        break;
                    }
                    case 2: { // Decryption case
                        cout << "Please enter the sentence to decrypt: ";
                        getline(cin, sentence); // Read the entire line of input including spaces

                        // Convert the sentence to lowercase
                        transform(sentence.begin(), sentence.end(), sentence.begin(), ::tolower);

                        // Iterate over each character in the sentence
                        for (char chr : sentence) {
                            if (isalpha(chr)) { // Check if it's an alphabet character
                                string target(1, chr); // Convert the character to a string
                                auto it = find(alphabet.begin(), alphabet.end(), target); // Find the character in the alphabet vector
                                if (it != alphabet.end()) { // If the character is found
                                    int y = distance(alphabet.begin(), it); // Calculate the position of the character in the alphabet
                                    int eq = ((c * (y - b)) % 26 +26) % 26;
                                    // decryption equation: c(y - b) mod 26
                                    cout << alphabet[eq]; // Print the decrypted character
                                }
                            }
                        }
                        cout << endl; // End of decryption
                        break;
                    }
                    case 3: // Exit case
                        cout << "Exiting the program :)\n";
                        break;
                    default: // Invalid choice case
                        cout << "Invalid choice. Please enter a number from 1 to 3\n";
                }
            } while(choice != 3); // Continue the loop until the user chooses to exit


            // Baconian Cipher program
        }else if (cipher_choice == 2){
            char choose;                                                     //intializing variables
            string str1, str2, decodedstr =" ";
            cout << "Welcome user to Baconian Cipher" << endl;
            // print welcome message
            cout << "Please choose: (a/b)\n a) if you want to cypher\n b) if you want to decypher\n";
            cin >> choose;
            cin.ignore();
            //a menu is opened to let user choose to cypher or decypher
            if (choose == 'a')  // a for cypher
            {
                cout << " Enter word to cypher : \n";
                getline(cin,str1); // let the user enter a message he wants with spaces to encrypt
                for (int i = 0; i < str1.length(); i++) {   // a loop is done to see every character in the message
                    if (str1[i] == 'A' || str1[i] == 'a')
                        str2 += "aaaaa";
                    else if (str1[i] == 'B' || str1[i] == 'b')
                        str2 += "aaaab";
                    else if (str1[i] == 'C' || str1[i] == 'c')
                        str2 += "aaaba";
                    else if (str1[i] == 'D' || str1[i] == 'd')// see every character in the message and add its equivlant to another variable and the loop stops when the message is done
                        str2 += "aaabb";
                    else if (str1[i] == 'E' || str1[i] == 'e')
                        str2 += "aabaa";
                    else if (str1[i] == 'F' || str1[i] == 'f')
                        str2 += "aabab";
                    else if (str1[i] == 'G' || str1[i] == 'g')
                        str2 += "aabba";
                    else if (str1[i] == 'H' || str1[i] == 'h')
                        str2 += "aabbb";
                    else if (str1[i] == 'I' || str1[i] == 'i')
                        str2 += "abaaa";
                    else if (str1[i] == 'J' || str1[i] == 'j')
                        str2 += "abaab";
                    else if (str1[i] == 'K' || str1[i] == 'k')
                        str2 += "ababa";
                    else if (str1[i] == 'L' || str1[i] == 'l')
                        str2 += "ababb";
                    else if (str1[i] == 'M' || str1[i] == 'm')
                        str2 += "abbaa";
                    else if (str1[i] == 'N' || str1[i] == 'n')
                        str2 += "abbab";
                    else if (str1[i] == 'O' || str1[i] == 'o')
                        str2 += "abbba";
                    else if (str1[i] == 'P' || str1[i] == 'p')
                        str2 += "abbbb";
                    else if (str1[i] == 'Q' || str1[i] == 'q')
                        str2 += "baaaa";
                    else if (str1[i] == 'R' || str1[i] == 'r')
                        str2 += "baaab";
                    else if (str1[i] == 'S' || str1[i] == 's')
                        str2 += "baaba";
                    else if (str1[i] == 'T' || str1[i] == 't')
                        str2 += "baabb";
                    else if (str1[i] == 'U' || str1[i] == 'u')
                        str2 += "babaa";
                    else if (str1[i] == 'V' || str1[i] == 'v')
                        str2 += "babab";
                    else if (str1[i] == 'W' || str1[i] == 'w')
                        str2 += "babba";
                    else if (str1[i] == 'X' || str1[i] == 'x')
                        str2 += "babbb";
                    else if (str1[i] == 'Y' || str1[i] == 'y')
                        str2 += "bbaaa";
                    else if (str1[i] == 'Z' || str1[i] == 'z')
                        str2 += "bbaab";
                    else if (str1[i] == ' ')
                        str2 += " ";

                }
                cout << str2<<endl;  // print out the variable after encryption
            }
            else if (choose == 'b') // b for decypher
            {
                cout << "enter the code u want to decypher: \n";
                getline(cin,str1);
                int j = 0;
                while ( j < str1.length())
                {
                    if (str1.substr(j,5) == "aaaaa"){
                        str2 += "a";
                        j += 5;}
                    else if (str1.substr(j,5) == "aaaab") {
                        str2 += "b";
                        j += 5;
                    }
                    else if (str1.substr(j,5) == "aaaba"){
                        str2 += "c";
                        j += 5;
                    }
                    else if (str1.substr(j,5) == "aaabb"){
                        str2 += "d";
                        j += 5;
                    }
                    else if (str1.substr(j,5) == "aabaa"){  // see every 5 characters in the message and add its equivlant to another variable and the loop stops when the message is done
                        str2 += "e";
                        j += 5;}
                    else if (str1.substr(j,5) == "aabab"){
                        str2 += "f";
                        j += 5;}
                    else if (str1.substr(j,5) == "aabba"){
                        str2 += "g";
                        j += 5;}
                    else if (str1.substr(j,5) == "aabbb"){
                        str2 += "h";
                        j += 5;}
                    else if (str1.substr(j,5) == "abaaa"){
                        str2 += "i";
                        j += 5;}
                    else if (str1.substr(j,5) == "abaab"){
                        str2 += "j";
                        j += 5;}
                    else if (str1.substr(j,5) == "ababa"){
                        str2 += "k";
                        j += 5;}
                    else if (str1.substr(j,5) == "ababb"){
                        str2 += "l";
                        j += 5;}
                    else if (str1.substr(j,5) == "abbaa"){
                        str2 += "m";
                        j += 5;}
                    else if (str1.substr(j,5) == "abbab"){
                        str2 += "n";
                        j += 5;}
                    else if (str1.substr(j,5) == "abbba"){
                        str2 += "o";
                        j += 5;}
                    else if (str1.substr(j,5) == "abbbb"){
                        str2 += "p";
                        j += 5;}
                    else if (str1.substr(j,5) == "baaaa"){
                        str2 += "q";
                        j += 5;}
                    else if (str1.substr(j,5) == "baaab"){
                        str2 += "r";
                        j += 5;}
                    else if (str1.substr(j,5) == "baaba"){
                        str2 += "s";
                        j += 5;}
                    else if (str1.substr(j,5) == "baabb"){
                        str2 += "t";
                        j += 5;}
                    else if (str1.substr(j,5) == "babaa"){
                        str2 += "u";
                        j += 5;}
                    else if (str1.substr(j,5) == "babab"){
                        str2 += "v";
                        j += 5;}
                    else if (str1.substr(j,5) == "babba"){
                        str2 += "w";
                        j += 5;}
                    else if (str1.substr(j,5) == "babbb"){
                        str2 += "x";
                        j += 5;}
                    else if (str1.substr(j,5) == "bbaaa"){
                        str2 += "y";
                        j += 5;}
                    else if (str1.substr(j,5) == "bbaab"){
                        str2 += "z";
                        j += 5;}
                    else if (str1[j] == ' '){
                        str2 += " ";
                        j += 1;}
                    else
                        cout<<"please enter the right form of decypher ";
                }
                cout<<str2<<endl;
            }
            else
                cout << "choose a/b";


            // XOR Cipher program
        }else if(cipher_choice == 3){

            //menu loop
            while (true) {
                cout << "Choose what you want to do (1/2)\n";
                cout << "1) Cipher\n";
                cout << "2) Decipher\n";
                cin >> choice;

                // cipher choice
                if (choice == 1) {
                    cout << "Please enter a message to encrypt: ";
                    cin >> plaintext; //taking the plaintext
                    cout << "Please enter the secret key: ";
                    cin >> key; //taking the key
                    encrypted = xor_operation(plaintext, key); //calling the xor function
                    cout << "Encrypted text: " << encrypted << endl << "In Hexadecimal: " << string_hex(encrypted)<< endl;
                    // printing the result and calling the string to hexadecimal function to the result
                    break;

                }// decipher choice
                else if (choice == 2) {
                    cout << "Please enter a message to decrypt: ";
                    cin >> decrypted; //taking the message to decrypt
                    cout << "Please enter the secret key: ";
                    cin >> key; //taking the key
                    decrypted = xor_operation(hex_string(decrypted), key);
                    //calling the xor function to the converted message (from hexadecimal to string)
                    cout << "Decrypted text: " << decrypted << endl;
                    break;
                } else {     //if the input is invalid
                    cout << "Invalid input, please enter a number (1/2)\n";
                }
                cout << endl;
            }


        }else{   // Exiting the program
            cout<<"Thanks for using our program, come again later.\n";
            break;
        }


    }
    return 0;
}